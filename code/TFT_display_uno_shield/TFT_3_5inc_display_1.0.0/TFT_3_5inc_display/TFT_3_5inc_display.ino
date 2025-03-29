

// #include <LCDWIKI_GUI.h> //Core graphics library
#include <LCDWIKI_KBV.h> //Hardware-specific library

LCDWIKI_KBV mylcd(ILI9486,A3,A2,A1,A0,A4);



#define COLOR_RED 0xF000

void selectLED (int x, int y)
{
  int radius = 10;

  for (int i = 0; i < radius; i++)
  for (int j = 0; j < radius; j++)
  {
      mylcd.Draw_Pixe (x * 480 / 48 + i, 
                       y * 320 / 32 + j, COLOR_RED);
  }
}
void selectLED (int x, int y, uint16_t color)
{
  int radius = 10;

  for (int i = 0; i < radius; i++)
  for (int j = 0; j < radius; j++)
  {
      mylcd.Draw_Pixe (x * 480 / 48 + i, 
                       y * 320 / 32 + j, color);
  }
}
void deselectLED (int x, int y)
{
  int radius = 10;

  for (int i = 0; i < radius; i++)
  for (int j = 0; j < radius; j++)
  {
      mylcd.Draw_Pixe(x * 480 / 10 + i, 
                      y * 320 / 10 + j, 00);
  }

}

// Matrix dimensions
#define ROWS 32
#define COLS 48
#define TOTAL_BITS (ROWS * COLS)  // 220 bits for 10x22 matrix
#define TOTAL_BYTES ((TOTAL_BITS / 8) + 2)  // Data bytes + start byte + padding

// Global variables
static int ledMatrix[COLS][ROWS] = {0};  // Store LED states
int currentRow = 0;
int currentCol = 0;
uint16_t currentColor = 0;
int displayMode = 0;  // 0: Normal, 1: Single LED, 2: Pattern


void displayPattern() {
  for (int col = 0; col < COLS; col++) 
      for (int row = 0; row < ROWS; row++)
          if (ledMatrix[col][row] == 1) 
          {
              selectLED(row, col);
          } else {
              deselectLED(row, col);
          }      
}


void processWriteCommand(const String& command) {
  int dataLength = command.length() - 1;  // Subtract 1 for command byte
  
  switch (dataLength) {
     case 4:  // Full 10x22 matrix - direct bit pattern
          for (int i = 0; i < 4; i++) {
              int row = i / 2;
              int col = i % 2;
              ledMatrix[row][col] = command[i + 1] - '0';
              Serial.println("W4");
          }
          break;
      case 220:  // Full 10x22 matrix - direct bit pattern
          for (int i = 0; i < 220; i++) {
              int row = i / 22;
              int col = i % 22;
              ledMatrix[row][col] = command[i + 1] - '0';
              Serial.println("W220");
          }
          break;
        case 1536:  // Full 10x22 matrix - direct bit pattern
          for (int i = 0; i < 1536; i++) {
              int row = i / 48;
              int col = i % 48;
              ledMatrix[row][col] = command[i + 1] - '0';
          }
          break;
      case TOTAL_BYTES - 1:  // Full matrix using packed bytes
          int bitIndex = 0;
          for (int i = 1; i < TOTAL_BYTES; i++) {
              byte data = command[i] - '0';
              for (int j = 0; j < 8 && bitIndex < TOTAL_BITS; j++, bitIndex++) {
                  int col = bitIndex / ROWS;
                  int row = bitIndex % ROWS;
                  ledMatrix[col][row] = (data >> (7 - j)) & 1;
              }
          }
          break;
          
      default:
          Serial.println("Invalid data length for Write command");
          return;
  }
  
  Serial.println("Matrix Updated!");
}

void processSetCommand(const String& command) {
  int value = command[1] - '0';
  int row, col;
  uint16_t color;
  
  if (command.length() == 4) {
      row = command[2] - '0';
      col = command[3] - '0';
  } else if (command.length() == 5) {
      row = (command[2] - '0') * 10 + (command[3] - '0');
      col = command[4] - '0';
  } else if (command.length() == 7) {
    color = (command[1] << 8) | command[2];
    row = (command[3] - '0') * 10 + (command[4] - '0');
    col = (command[5] - '0') * 10 + (command[6] - '0');
    Serial.print("row ");
    Serial.print(row);
    Serial.print("   col  ");
    Serial.print(col);
    Serial.print(" color:[] ");
    Serial.println(color);
    selectLED(row, col, color);
    }
    else if (command.length() == 9) {
        color = (command[1] << 8) | command[2];
        row = (command[3] - '0') * 100 + (command[4] - '0') * 10 + (command[5] - '0');
        col = (command[6] - '0') * 100 + (command[7] - '0') * 10 + (command[8] - '0');
        Serial.print("row ");
        Serial.print(row);
        Serial.print("   col  ");
        Serial.print(col);
        Serial.print(" color:[] ");
        Serial.println(color);
        mylcd.Draw_Pixe (row, col, color);
        }
     else {
      Serial.println("Invalid Set command format");
      return;
  }
  
  if (row >= 0 && row < ROWS && col >= 0 && col < COLS) {
      currentRow = row;
      currentCol = col;
      currentCol = color;
  //   //   displayMode = 1;
      // Serial.printf("Set Value: %d at Row: %d Column: %d\n", value, row, col);
  }
}



//**********************************************************************//
//**********************************************************************//

void setup() 
{
    Serial.begin(115200);
    mylcd.Init_LCD(); //initialize lcd
    mylcd.Fill_Screen(0,0,0);  
}



void loop() {
  if (Serial.available()) {
      String command = Serial.readStringUntil('\n');
      if (command.length() > 0) {
          char action = command[0];
          
          switch (action) {
              case 'R':  // Reset/Clearm
                  mylcd.Fill_Screen(0x0000);
                  displayMode = 0;
                  memset(ledMatrix, 0, sizeof(ledMatrix));
                  Serial.println("Matrix Cleared");
                  break;
                  
              case 'S':  // Set individual LED
                  processSetCommand(command);
                  displayMode = 1;
                  break;
                  
              case 'W':  // Write pattern
                  processWriteCommand(command);
                  displayMode = 2;
                  break;
                  
              default:
                  Serial.println("Invalid Command!");
          }
      }
  }

// mylcd.Fill_Screen(0x0000);
 switch (displayMode) {
      case 1:  // Single LED
          // selectLED(currentRow, currentCol, currentColor);
          break;
      case 2:  // Pattern
          displayPattern();
          break;
  }

  // char a = 0xf0;
  // char b = 0;
  // uint16_t color = a << 8 | b;
  // selectLED(10,10,color);

  // Serial.println(a);
}


//**********************************************************************//
//**********************************************************************//