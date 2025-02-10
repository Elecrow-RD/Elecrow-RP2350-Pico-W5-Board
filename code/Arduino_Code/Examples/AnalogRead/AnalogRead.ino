int sensorValue = 0;  // variable to store the value coming from the sensor

void setup() {
  Serial.begin(115200);

}

void loop() {
  // read the value from the sensor:
  int sensorValue =  analogRead(27);  // select the input pin 
  Serial.print("sensorValue:");
  Serial.println(sensorValue);
  delay(1000);
}
