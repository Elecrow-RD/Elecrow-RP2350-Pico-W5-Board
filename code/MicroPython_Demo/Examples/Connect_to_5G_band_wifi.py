from machine import UART, Pin
import time

# Initialize UART1 with baudrate 115200, transmit on Pin(4), receive on Pin(5)
uart1 = UART(1, baudrate=115200, tx=Pin(4), rx=Pin(5))

# Function to send AT commands using UART1
def send_at_command(uart, command):
    uart1.write(command + '\n')     # Send the AT command followed by a newline for the module to process
    time.sleep(0.1)                 # Wait for the module to process the command and send a response

# Function to continuously receive data from UART1 until a newline character is detected
def Uart1_receive(): 
    data = b''          # Initialize an empty bytes object to store incoming data
    succeed = "OK"      # Expected success response from the module
    fail = "ERROR"      # Expected error response from the module

    while True:
        if uart1.any():              # Check if there is data available to read
            data += uart1.read()     # Read all available data into 'data'
        if data.endswith(b'\n'):     # Check if the data ends with a newline character
            if succeed in data:      # If the success response is in the data
                print(data)          # Print the received data
                break                # Exit the loop
            if fail in data:         # If the error response is in the data
                print(data)          # Print the received data
                break                # Exit the loop
            print(data)              # Print the data received so far
        time.sleep(0.5)              # Wait for 0.5 seconds before continuing
        
# Send an AT command to set the module's working mode
send_at_command(uart1, 'AT+WMODE=3,1') 
Uart1_receive()
# Send an AT command to connect the module to a Wi-Fi network with the SSID "yanfa_software_5G" and password "yanfa-123456"
send_at_command(uart1, 'AT+WJAP=yanfa_software_5G,yanfa-123456')   
Uart1_receive()
 
