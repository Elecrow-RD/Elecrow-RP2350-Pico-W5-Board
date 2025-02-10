from machine import Pin
from utime import sleep
import utime

# Connect the onboard LED to pin 25
# LED = Pin(id, mode, pull)
# id: RP2040 pin number
# mode: Input/output mode, with Pin.IN (input) and Pin.OUT (output) two options
# pull: Pull-up/pull-down resistor configuration, with None (no pull resistor), Pin.PULL_UP (pull-up resistor), and Pin.PULL_DOWN (pull-down resistor) three options
led = Pin(25, Pin.OUT)

while True:
    # Turn on the LED
    led.value(1)
    utime.sleep_ms(1000)
    # Turn off the LED
    led.value(0)
    utime.sleep_ms(1000)




   


