from machine import ADC, Pin
import time

# Initialize an ADC object using Pin 27 for analog input
adc = ADC(Pin(27))

while True:
    # Read the analog value from the ADC and print it as a 16-bit unsigned integer
    print(adc.read_u16())
    # Delay for 1 second to avoid overwhelming the output with too many readings
    time.sleep(1)