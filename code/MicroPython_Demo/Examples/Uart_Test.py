from machine import UART, Pin
import time

# Initialize UART1 with baudrate 115200, transmit on Pin(4), receive on Pin(5)
uart1 = UART(1, baudrate=115200, tx=Pin(4), rx=Pin(5))

# Function to send AT commands
def send_at_command(uart, command):
    uart1.write(command + '\n')  # Send the command followed by a newline character
    time.sleep(0.1)   # Wait for a response

# Function to read the response from the module
def read_response(uart):
    return uart1.read(1024)  # Read a certain number of bytes from the UART buffer

# Main loop
while True:
    send_at_command(uart1, 'AT')  # Send a test AT command to check the module's response
    response = read_response(uart1)
    print('Module Response0:', response)
    time.sleep(2)   # Wait for 2 seconds before sending the next command
    send_at_command(uart1, 'AT+GMR')   # Send a command to get the module's firmware version
    response = read_response(uart1)
    print('Module Response1:', response)
    time.sleep(2)  # Wait for 2 seconds before the next iteration of the loop