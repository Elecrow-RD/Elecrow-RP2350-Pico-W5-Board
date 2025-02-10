from machine import Pin, PWM
from time import sleep

# Initialize a PWM object using Pin 16
pwm = PWM(Pin(16))

# Set the frequency of the PWM signal to 1000 Hz
pwm.freq(1000)

while True:
    # Increment the duty cycle from 0 to 65025
    for duty in range(65025):
        pwm.duty_u16(duty)  # Set the PWM duty cycle to the current value
        sleep(0.0001)  # Delay for 0.0001 seconds to allow the change to take effect

    # Decrement the duty cycle from 65025 to 0
    for duty in range(65025, 0, -1):
        pwm.duty_u16(duty)  # Set the PWM duty cycle to the current value
        sleep(0.0001)  # Delay for 0.0001 seconds to allow the change to take effect



