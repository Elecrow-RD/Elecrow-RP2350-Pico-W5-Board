#define PWM_PIN 17  //set pwn pin

void setup ()
{
   // set pwm pin as outputs:
  pinMode(PWM_PIN, OUTPUT);
}

void loop()
{
  // fade the LED on thisPin from off to brightest:
  for (int brightness = 0; brightness <= 255; brightness++)
  {
    analogWrite(PWM_PIN, brightness);
    delay(8);
  }
  // fade the LED on thisPin from brightest to off:
  for (int brightness = 255; brightness >= 0; brightness--)
  {
    analogWrite(PWM_PIN, brightness);
    delay(8);
  }
  // pause between LEDs:
  delay(800);
}
