from machine import UART, Pin
import time
from dht20 import DHT20

# Commands for the BW16 module
cmd_WIFI_1 = "AT+WMODE=3,1\n"                         # Set the wifi mode to AP+STA
cmd_WIFI_2 = "AT+WJAP=yanfa_software,yanfa-123456"    # Configure the wifi connection. Please modify to your own configuration information.
cmd_MQTT_1 = "AT+MQTT=1,192.168.50.177\n"             # Configure the MQTT server. Please modify to your own configuration information.
cmd_MQTT_2 = "AT+MQTT=2,1883\n"                       # Specify the port number for accessing the server. Please modify to your own configuration information.
cmd_MQTT_3 = "AT+MQTT=3,1\n"                          # Configure the MQTT user ID. Please modify to your own configuration information.
cmd_MQTT_4 = "AT+MQTT=5,sea\n"                     # Set the MQTT user name. Please modify to your own configuration information.
cmd_MQTT_5 = "AT+MQTT=6,lisihai525\n"                     # Set the MQTT user password. Please modify to your own configuration information.
cmd_MQTT_6 = "AT+MQTT\n"                              # Connect to MQTT.
cmd_MQTT_7 = "AT+MQTTSUB=TP,0\n"                    # Subscribe to a topic (e.g., 'TP') with QoS 0.
cmd_MQTT_9 = "AT+MQTTPUBRAW=TP,0,0,9\n"             # Publish raw data to the topic 'TP' with QoS 0.

# Initialize UART1 with baudrate 115200, transmit on Pin(4), receive on Pin(5)
uart1 = UART(1, baudrate=115200, tx=Pin(4), rx=Pin(5))

# Set the I2C pins
sda = machine.Pin(20)  # SDA pin is set to GPIO pin 20
scl = machine.Pin(21)  # SCL pin is set to GPIO pin 21


# Function to send AT commands using UART1
def send_at_command(uart, command):
    uart1.write(command + '\n')     # Send the AT command followed by a newline for the module to process
    time.sleep(0.1)                 # Wait for the module to process the command and send a response
    
# Function to continuously receive data from UART1 until a newline character is detected   
def Uart1_receive():
    data = b''           # Initialize an empty bytes object to store incoming data
    succeed = "OK"       # Expected success response from the module
    fail = "ERROR"       # Expected error response from the module

    while True:
        if uart1.any():                    # Check if there is data available to read
            data += uart1.read()           # Read all available data into 'data'
        if data.endswith(b'\n'):           # Check if the data ends with a newline character
            if succeed in data:            # If the success response is in the data
                print(data)                # Print the received data
                break                      # Exit the loop
            if fail in data:               # If the error response is in the data
                print(data)                # Print the received data
                break                      # Exit the loop
            print(data)                    # Print the data received so far
        time.sleep(0.5)                    # Wait for 0.5 seconds before continuing
        
        
# Test the homeassist function
def test():
    """Test code."""
    # Create an I2C object, select bus 0, assign the SDA and SCL pins, and set the bus frequency to 400kHz
    i2c = machine.I2C(0, sda=sda, scl=scl, freq=400000)
    #Initialize the DHT20
    dht20 = DHT20(0x38, i2c)
    
    #Initializing WIFI via serial port, MQTT
    send_at_command(uart1, cmd_WIFI_1)
    Uart1_receive()
    send_at_command(uart1, cmd_WIFI_2)
    Uart1_receive()
    send_at_command(uart1, cmd_MQTT_1)
    Uart1_receive()
    send_at_command(uart1, cmd_MQTT_2)
    Uart1_receive()
    send_at_command(uart1, cmd_MQTT_3)
    Uart1_receive()
    send_at_command(uart1, cmd_MQTT_4)
    Uart1_receive()
    send_at_command(uart1, cmd_MQTT_5)
    Uart1_receive()
    send_at_command(uart1, cmd_MQTT_6)
    Uart1_receive()
    time.sleep(0.5)
    send_at_command(uart1, cmd_MQTT_7)
    Uart1_receive()

    while True:
         # Get temperature and humidity data and upload to Home Assistant
        measurements = dht20.measurements
        print(f"Temperature: {measurements['t']} °C, humidity: {measurements['rh']} %RH")
        temp = int (measurements['t'])
        hum  = int (measurements['rh'])

        temperature = f"{temp}C"
        humidity = f"{hum}%"
        
        # Publish temperature and humidity data to MQTT
        uart1.write(cmd_MQTT_9.encode('utf-8'))
        time.sleep(0.5)
        
        temp_s = f"{{\"t\":{temp}}}"
        print(temp_s)
        uart1.write(temp_s.encode('utf-8'))
        uart1.write('\n')
        Uart1_receive()
        
        uart1.write(cmd_MQTT_9.encode('utf-8'))
        time.sleep(0.5)

        hum_s = f"{{\"h\":{hum}}}"
        print(hum_s)
        uart1.write(hum_s.encode('utf-8'))
        uart1.write('\n')
        Uart1_receive()

 #Start Test
test()