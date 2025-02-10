from machine import Pin
import time

# Initialize the LED pin as an output pin on GPIO 16
led = Pin(16, Pin.OUT)

# Initialize the button pin as an input pin on GPIO 15 with a pull-down resistor
button = Pin(15, Pin.IN, Pin.PULL_DOWN)

while True:
    # Check the button's value
    if button.value():
        # If the button is pressed (value is high), toggle the LED state
        led.toggle()
        # Pause the program for 0.5 seconds to debounce the button
        time.sleep(0.5)


