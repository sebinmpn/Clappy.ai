import serial
import time

arduino = serial.Serial(port='/dev/ttyUSB0', baudrate=9600, timeout=1)


def send_command(cmd):
    """Send a command string to Arduino."""
    arduino.write(f"{cmd}\n".encode())
    time.sleep(0.1)
    return arduino.readline().decode().strip()

# Reset Arduino
print(send_command("R"))


# Send 10x10 LED Matrix Data
def send_led_matrix(matrix):
    """Send a 10x10 LED matrix as a 100-character string to Arduino."""
    data_str = 'W' + ''.join(str(cell) for cell in matrix)  # Flatten & add 'W'
    print("Sending Matrix Data:", data_str)
    print(send_command(data_str))

# Example 10x10 Boolean Matrix (Checkerboard Pattern)
led_matrix = [
    [0, 0, 0, 0, 0, 1, 1, 1,  0, 0],
    [0, 0, 0, 0, 0, 0, 0, 0,  0, 0],
    [0, 0, 0, 0, 0, 0, 0, 0,  0, 0],
    [0, 0, 0, 0, 0, 0, 0, 0,  0, 0],
    [0, 0, 0, 0, 0, 0, 0, 0,  0, 0],
    [0, 0, 0, 0, 0, 0, 0, 0,  0, 0],
    [0, 0, 0, 0, 0, 0, 0, 0,  0, 0],
    [0, 0, 0, 0, 0, 0, 0, 0,  0, 0],
    [0, 0, 0, 0, 0, 0, 0, 0,  0, 0],
    [0, 0, 0, 0, 1, 1, 0, 0,  0, 0],
    [0, 0, 0, 0, 0, 0, 0, 0,  0, 0],
    [0, 0, 0, 0, 0, 0, 0, 0,  0, 0],
    [0, 0, 0, 0, 0, 0, 0, 0,  0, 0],
    [0, 0, 0, 0, 0, 0, 0, 0,  0, 0],
    [0, 0, 0, 0, 0, 0, 0, 0,  0, 0],
    [0, 0, 0, 0, 0, 0, 0, 0,  0, 0],
    [0, 0, 0, 0, 0, 0, 0, 0,  0, 0],
    [0, 0, 0, 0, 0, 0, 0, 0,  0, 0],
    [0, 0, 0, 0, 0, 0, 0, 0,  0, 0],
    [0, 0, 0, 0, 0, 0, 0, 0,  0, 0],
    [0, 0, 0, 0, 0, 0, 0, 0,  0, 0],
    [0, 0, 0, 0, 0, 0, 0, 0,  0, 0]
]
# Flatten the 10x10 matrix into a single row with 220 values (padded with zeros)
single_row_matrix = [cell for row in led_matrix for cell in row] + [0] * (220 - len(led_matrix) * len(led_matrix[0]))


# Create a list of 27 characters (A-Z and space)
char_data = [0, 0, 0,  0, 0, 0,  0, 0, 0, 
             0, 0, 0,  0, 0, 0,  0, 0, 0, 
             0, 0, 0,  0, 0, 0,  0, 0, 0]

for i in range(0, 216, 8):
    data = (single_row_matrix[i] * 128)  + (single_row_matrix[i+1] * 64 ) + single_row_matrix[i+2] * 32 + single_row_matrix[i+3] * 16 + single_row_matrix[i+4] * 8 + single_row_matrix[i+5] * 4 + single_row_matrix[i+6] * 2 + single_row_matrix[i+7]
    char_data[i // 8] = (data)


send_led_matrix(char_data)

print(char_data)
arduino.close()


