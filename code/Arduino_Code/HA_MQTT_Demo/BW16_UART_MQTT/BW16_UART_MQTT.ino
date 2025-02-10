#include "DHT20.h"

// Define the RX and TX pins for Serial2 communication
#define  Serial2_RX 5
#define  Serial2_TX 4

int ok_flag =  0;
// Variables to store temperature and humidity values
int  temp;
int  hum;
// Variable to store the last time the DHT20 sensor was read
unsigned long previousMillis = 0;
// Interval at which to read the DHT20 sensor (in milliseconds)
const long interval = 5000;

// Initialize the DHT20 sensor using the I2C bus
DHT20 DHT(&Wire);

// Buffers to store the temperature and humidity values as strings
char buffer_t[10];
char buffer_h[10];


#define SET_WIFI_MODE           "AT+WMODE=3,1"				//#Set wifi mode to AP STA 
#define SET_WIFI_SSID_PASSWORD  "AT+WJAP=\"yanfa_software\",\"yanfa-123456\""	//#Configure  wifi connection  Please modify to your own configuration information
#define SET_MQTT_IP             "AT+MQTT=1,192.168.50.147"			//#Configure the MQTT server.    Please modify to your own configuration information
#define SET_MQTT_PORT           "AT+MQTT=2,1883"				//#The port number for accessing the server is specified.  Please modify to your own configuration information
#define SET_MQTT_MODE           "AT+MQTT=3,1"					//#Configure the MQTT connection mode. The default 1 indicates TCP
#define SET_MQTT_ID             "AT+MQTT=4,001"				//#The MQTT user ID is configured. Please modify to your own configuration information
#define SET_MQTT_USER           "AT+MQTT=5,Carlos"				//#Set the MQTT user name.  Please modify to your own configuration information
#define SET_MQTT_PASSWORD       "AT+MQTT=6,qazwsx"			//#Set the MQTT user password.  Please modify to your own configuration information
#define CONNECT_MQTT            "AT+MQTT"						//#Connect MQTT

void setup()
{
  // Start the serial communication for debugging
  Serial.begin(115200);
  // Set the SDA and SCL pins for the I2C bus
  Wire.setSDA(20);
  Wire.setSCL(21);
  // Start the I2C bus
  Wire.begin();
  // Delay to allow the DHT20 sensor to initialize
  delay(1000);
  // Set the RX and TX pins for Serial2 communication
  Serial2.setRX(Serial2_RX);
  Serial2.setTX(Serial2_TX);
  // Start Serial2 communication
  Serial2.begin(115200);
  // Delay to allow the Serial2 module to initialize
  delay(1000);
  // Call the UART2 test function to configure the WiFi and MQTT connection
  UART2_test();
}

void loop()
{
  // Get the current time in milliseconds
  unsigned long currentMillis = millis();
  // Read the temperature and humidity from the DHT20 sensor
  int status = DHT.read();
  if (currentMillis - previousMillis >= interval)
  {
    // Update the time of the last reading
    previousMillis = currentMillis;
    // Get the humidity and temperature values
    hum = (int)DHT.getHumidity();
    temp = (int)DHT.getTemperature();
    // Print the humidity and temperature values to the serial monitor
    Serial.print("hum:");
    Serial.println( hum);
    Serial.print("temp:");
    Serial.println( temp);
    // Convert the humidity and temperature values to strings
    itoa(hum, buffer_h, 10);
    itoa(temp, buffer_t, 10);
    // Delay to allow the Serial2 buffer to clear
    delay(100);
    // Check if the sensor reading was successful
    if (isnan(temp) || isnan(hum))
    {
      Serial.println(F("Failed to read from DHT20 sensor!"));
      return;
    }
    // If the temperature is within the range of 10 to 99 degrees Celsius
    if (temp >= 10 && temp <= 99)
    {
      // Send the temperature data to the MQTT server
      Serial2.print("AT+MQTTPUBRAW=PICOTP,0,0,9");
      Serial2.write('\n');
      delay(300);
      Serial2.printf("{\"t\":%s}", String(temp).c_str());
      Serial2.write('\n');
      delay(100);
      // Send the humidity data to the MQTT server
      Serial2.print("AT+MQTTPUBRAW=PICORH,0,0,9");
      Serial2.write('\n');
      delay(300);
      Serial2.printf("{\"h\":%s}", String(hum).c_str());
      Serial2.write('\n');
      delay(100);
    }
  }
}


// Function to test UART2 communication and configure the WiFi and MQTT connection
void UART2_test()
{
  // Send the AT command to test the Serial2 module
  Serial2.println("AT");
  // Wait for the module to respond with "OK"
  while (!ok_flag) {
    if (Serial2.find("OK")) {
      delay(1000);
      ok_flag = true;
      Serial.println("AT Ok!");
    }
  }
  // Clear the Serial2 buffer and reset the ok_flag for the next command
  clear_serial();
  // Repeat the process for each configuration command
  ok_flag = 0;
  Serial2.println(SET_WIFI_MODE);
  while (!ok_flag) {
    if (Serial2.find("OK")) {
      delay(1000);
      ok_flag = true;
      Serial.println("Set WIFI Mode Ok!");
    }
  }
  clear_serial();
  ok_flag = 0;
  Serial2.println(SET_WIFI_SSID_PASSWORD);
  while (!ok_flag) {
    if (Serial2.find("OK")) {
      delay(1000);
      ok_flag = true;
      Serial.println("WIFI Connected!");
    }
  }
  clear_serial();
  ok_flag = 0;
  Serial2.println(SET_MQTT_IP);
  while (!ok_flag) {
    if (Serial2.find("OK")) {
      delay(1000);
      ok_flag = true;
      Serial.println("Set MQTT Ip Ok!");
    }
  }
  clear_serial();
  ok_flag = 0;
  Serial2.println(SET_MQTT_PORT);
  while (!ok_flag) {
    if (Serial2.find("OK")) {
      delay(1000);
      ok_flag = true;
      Serial.println("Set MQTT Port Ok!");
    }
  }
  clear_serial();
  ok_flag = 0;
  Serial2.println(SET_MQTT_MODE);
  while (!ok_flag) {
    if (Serial2.find("OK")) {
      delay(1000);
      ok_flag = true;
      Serial.println("Set MQTT Mode Ok!");
    }
  }
  clear_serial();
  ok_flag = 0;
  Serial2.println(SET_MQTT_ID);
  while (!ok_flag) {
    if (Serial2.find("OK")) {
      delay(1000);
      ok_flag = true;
      Serial.println("Set MQTT Id Ok!");
    }
  }
  clear_serial();
  ok_flag = 0;
  Serial2.println(SET_MQTT_USER);
  while (!ok_flag) {
    if (Serial2.find("OK")) {
      delay(1000);
      ok_flag = true;
      Serial.println("Set MQTT User Ok!");
    }
  }
  clear_serial();
  ok_flag = 0;
  Serial2.println(SET_MQTT_PASSWORD);
  while (!ok_flag) {
    if (Serial2.find("OK")) {
      delay(1000);
      ok_flag = true;
      Serial.println("Set MQTT Password Ok!");
    }
  }
  clear_serial();
  ok_flag = 0;
  Serial2.println(CONNECT_MQTT);
  while (!ok_flag) {
    if (Serial2.find("OK")) {
      delay(1000);
      ok_flag = true;
      Serial.println("Connect MQTT Ok!");
    }
  }
  clear_serial();
  ok_flag = 0;
}

// Function to clear the Serial2 and Serial buffers
void clear_serial() {
  // Clear the Serial2 buffer
  while (Serial2.read() >= 0);
  // Clear the Serial buffer
  while (Serial.read() >= 0);
}
