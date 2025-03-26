#define pin1 5
#define pin2 28

#define ROWPIN_1 40
#define ROWPIN_2 38
#define ROWPIN_3 36
#define ROWPIN_4 34
#define ROWPIN_5 32
#define ROWPIN_6 30
#define ROWPIN_7 28
#define ROWPIN_8 26
#define ROWPIN_9 24
#define ROWPIN_10 22

#define COLPIN_1 14 
#define COLPIN_2 15
#define COLPIN_3 16
#define COLPIN_4 17
#define COLPIN_5 18
#define COLPIN_6 19
#define COLPIN_7 20
#define COLPIN_8 21

#define COLPIN_9 23 
#define COLPIN_10 25
#define COLPIN_11 27
#define COLPIN_12 29

#define COLPIN_13 31
#define COLPIN_14 33
#define COLPIN_15 35
#define COLPIN_16 37

#define COLPIN_17 39
#define COLPIN_18 41
#define COLPIN_19 43
#define COLPIN_20 45
#define COLPIN_21 47
#define COLPIN_22 49




class LedMatrix 
{
public:
    LedMatrix(int row_pin1, int row_pin2, int row_pin3, int row_pin4, int row_pin5, int row_pin6, int row_pin7, int row_pin8, int row_pin9, int row_pin10, 
            int col_pin1, int col_pin2, int col_pin3, int col_pin4, int col_pin5, int col_pin6, int col_pin7, int col_pin8, int col_pin9, int col_pin10, 
            int col_pin11, int col_pin12, int col_pin13, int col_pin14, int col_pin15, int col_pin16, int col_pin17, int col_pin18, int col_pin19, int col_pin20, 
            int col_pin21, int col_pin22) {
      _rowPins[0] = row_pin1;
      _rowPins[1] = row_pin2;
      _rowPins[2] = row_pin3;
      _rowPins[3] = row_pin4;
      _rowPins[4] = row_pin5;
      _rowPins[5] = row_pin6;
      _rowPins[6] = row_pin7;
      _rowPins[7] = row_pin8;
      _rowPins[8] = row_pin9;
      _rowPins[9] = row_pin10;

      _colPins[0] = col_pin1;
      _colPins[1] = col_pin2;
      _colPins[2] = col_pin3;
      _colPins[3] = col_pin4;
      _colPins[4] = col_pin5;
      _colPins[5] = col_pin6;
      _colPins[6] = col_pin7;
      _colPins[7] = col_pin8;
      _colPins[8] = col_pin9;
      _colPins[9] = col_pin10;
      _colPins[10] = col_pin11;
      _colPins[11] = col_pin12;
      _colPins[12] = col_pin13;
      _colPins[13] = col_pin14;
      _colPins[14] = col_pin15;
      _colPins[15] = col_pin16;
      _colPins[16] = col_pin17;
      _colPins[17] = col_pin18;
      _colPins[18] = col_pin19;
      _colPins[19] = col_pin20;
      _colPins[20] = col_pin21;
      _colPins[21] = col_pin22;

      _numRows = 10;
      _numCols = 22;
    }

public:
    void setup() 
    {
      for (int i = 0; i < _numRows; i++) 
      {
        pinMode(_rowPins[i], OUTPUT);
        digitalWrite(_rowPins[i], HIGH); // Set all row pins to LOW
      } 

      for (int i = 0; i < _numCols; i++) 
      {
        pinMode(_colPins[i], OUTPUT);
        digitalWrite(_colPins[i], LOW); // Set all column pins to HIGH
      }
    }

    void reset() 
    {
        for (int i = 0; i < _numRows; i++) 
            digitalWrite(_rowPins[i], HIGH); 
        for (int i = 0; i < _numCols; i++) 
            digitalWrite(_colPins[i], LOW);    
    }
    
    void clear()
    {
        reset();
    }

    void selectRow(int row) {
        digitalWrite(_rowPins[row], LOW);
    }
  
    void selectColumn(int column) {
        digitalWrite(_colPins[column], HIGH);
    }
  
    void set( int column, int row) 
    {
        selectColumn (column);
        selectRow (row);
    }
  
    
  
    private:
      int _rowPins[10]; // Adjust size as needed
      int _colPins[22]; // Adjust size as needed
      int _numRows;
      int _numCols;
  };


  LedMatrix matrix(ROWPIN_1, ROWPIN_2, ROWPIN_3, ROWPIN_4, ROWPIN_5, ROWPIN_6, ROWPIN_7, ROWPIN_8, ROWPIN_9, ROWPIN_10, 
                      COLPIN_1, COLPIN_2, COLPIN_3, COLPIN_4, COLPIN_5, COLPIN_6, COLPIN_7, COLPIN_8, COLPIN_9, COLPIN_10, 
                      COLPIN_11, COLPIN_12, COLPIN_13, COLPIN_14, COLPIN_15, COLPIN_16, COLPIN_17, COLPIN_18, COLPIN_19, COLPIN_20, 
                      COLPIN_21, COLPIN_22);




  
  
// Driver //
int gRow = 0, gColumn = 0;

  int reset_cb ()
  {
    matrix.reset();
    matrix.clear();
    Serial.println("reset");
    gRow = 0;
    gColumn = 0;
    return -1;
  }
  

  int set_cb()
  {
    
    // matrix.set(int r, int  c);
    // gRow = r; 
    // gColumn = c;
    
    return -1;
  }
  
  int data_string[10];
  
  int read()
  {
     int cnt = 0;
    if (Serial.available() > 0) {

      char incomingByte = Serial.read();
      data_string[cnt++] = incomingByte;

      if (incomingByte == 'r') {
        reset_cb();
      }
      
      if (incomingByte == 's') {
        set_cb();
      }
      if(cnt > 10)
      {
        Serial.println(*data_string);
        cnt = 0;
      }
    }
    return -1;
  }
  

  int _matrix_value[10][10];


  // driver 


// void setup() {
  
//   matrix.setup();
//   matrix.clear();

//   Serial.begin(9600);
// }


// void loop() { 
//   matrix.reset();
//   matrix.clear();
   
//   matrix.set(0, 0);
//   matrix.clear();
//   matrix.set(3, 3);
//   matrix.clear();
//   matrix.set (gRow,gColumn);
//   matrix.clear();

//   read();

// }
int ledMatrix[22][10];  // Store LED states

int mode_selectin_state = 0;

int set_char()
{
  for (int i = 0; i < 220; i++) 
  {
    int row = i / 22;
    int col = i % 22;
   
    if(ledMatrix[row][col] == 1)
    {
      matrix.set( col, row);
      matrix.clear(); 
    }
  }
}

void setup() {
    Serial.begin(9600);
    Serial.println("Arduino Ready");
    matrix.setup();
    matrix.clear();

    for (int i = 0; i < 10; i++) {
      for (int j = 0; j < 10; j++) {
        ledMatrix[i][j] = 0;
      }
    }
}

void loop() {
    if (Serial.available()) {
        String command = Serial.readStringUntil('\n'); // Read input

        if (command.length() > 0) {
            char action = command[0]; // First character (R or S)

            if (action == 'R') {
                Serial.println("Resetting Arduino...");
                delay(100);
                // asm volatile ("jmp 0"); // Software reset

                mode_selectin_state = 0;

                for (int i = 0; i < 10; i++) {
                  for (int j = 0; j < 10; j++) {
                    ledMatrix[i][j] = 0;
      }
    }

            }
            else if (action == 'S' && command.length() == 4) {
                int value = command[1] - '0';  // Convert ASCII to integer
                int row = command[2] - '0';
                int col = command[3] - '0';

                gRow = row; 
                gColumn = col;

                Serial.print("Set Value: ");
                Serial.print(value);
                Serial.print(" at Row: ");
                Serial.print(row);
                Serial.print(" Column: ");
                Serial.println(col);

                mode_selectin_state = 1;
            }
            else if (action == 'S' && command.length() == 5) {
                int value = command[1] - '0';  // Convert ASCII to integer
                int row = int (command[2] - '0') * 10 + int (command[3] - '0');
                int col = command[4] - '0';

                gRow = row; 
                gColumn = col;

                Serial.print("Set Value: ");
                Serial.print(value);
                Serial.print(" at Row: ");
                Serial.print(row);
                Serial.print(" Column: ");
                Serial.println(col);

                mode_selectin_state = 1;
            }
            else if (action == 'W' && command.length() == 101)
            {
              for (int i = 0; i < 100; i++) {
                int row = 0 + i / 10;
                int col = 0 + i % 10;
                ledMatrix[row][col] = command[i + 1] - '0';  // Convert char to int
                
              }
              mode_selectin_state = 2;

              Serial.println("Matrix Updated!");

            }
            else if (action == 'W' && command.length() == 221)
            {
              for (int i = 0; i < 220; i++) {
                int row = 0 + i / 22;
                int col = 0 + i % 22;
                ledMatrix[row][col] = command[i + 1] - '0';  // Convert char to int
                
              }
              mode_selectin_state = 2;

              Serial.println("Matrix Updated!");

            }
            else if (action == 'W' && command.length() == 26)
            {
              for (int i = 0; i < 25; i++) {
                int row = 5 + i / 5;
                int col = 5 + i % 5;
                ledMatrix[row][col] = command[i + 1] - '0';  // Convert char to int
                
              }
              mode_selectin_state = 2;

              Serial.println("Matrix Updated!");

            }
            else if (action == 'W' && command.length() == 5)
            {
              for (int i = 0; i < 4; i++) {
                int row = 8 + i / 2;
                int col = 8 + i % 2;
                ledMatrix[row][col] = command[i + 1] - '0';  // Convert char to int
                
              }
              mode_selectin_state = 2;

              Serial.println("Matrix Updated!");

            }
            else {
                Serial.println("Invalid Command!");
            }
        }
    }

    matrix.clear();
    if (mode_selectin_state == 1)
        matrix.set(gRow, gColumn);
    if(mode_selectin_state == 2)
      set_char();
}
