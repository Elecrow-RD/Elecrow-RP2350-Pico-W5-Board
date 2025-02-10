import machine
import utime

# Set the I2C pins
# SDA pin is set to GPIO pin 20
sda = machine.Pin(20)
# SCL pin is set to GPIO pin 21
scl = machine.Pin(21)

# Create an I2C object, select bus 0, assign the SDA and SCL pins, and set the bus frequency to 400kHz
i2c = machine.I2C(0, sda=sda, scl=scl, freq=400000)

# Import the DHT20 library
from dht20 import DHT20
# Initialize the DHT20 sensor with its I2C address and the I2C bus
dht20 = DHT20(0x38, i2c)

while True:
    # Perform a measurement with the DHT20 sensor
    measurements = dht20.measurements
    # Extract the temperature from the measurements and convert it to an integer
    temp = int(measurements['t'])
    # Extract the relative humidity from the measurements and convert it to an integer
    hum = int(measurements['rh'])
    # Print the temperature and humidity values
    print(f"Temperature: {temp} °C, humidity: {hum} %RH")
    # Pause for 2 seconds before the next measurement
    utime.sleep(2)