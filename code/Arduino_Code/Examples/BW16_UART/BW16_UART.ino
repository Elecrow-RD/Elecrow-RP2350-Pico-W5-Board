// Define the RX and TX pins for the second serial port
#define Serial2_RX 5  // Set the RX pin
#define Serial2_TX 4  // Set the TX pin

// Initialize the second serial port
void UART1_Init()
{
  Serial2.setRX(Serial2_RX);  // Set the RX pin for the second serial port
  Serial2.setTX(Serial2_TX);  // Set the TX pin for the second serial port
  Serial2.begin(115200);     // Start the second serial port at a baud rate of 115200
  delay(1000);               // Delay for 1 second to allow the serial port to initialize
}

// Setup function to initialize the main serial port and the second serial port
void setup()
{
  Serial.begin(115200);      // Start the main serial port at a baud rate of 115200
  UART1_Init();               // Initialize the second serial port
}

// Main loop function that prints "loop" and then delays
void loop()
{
  UART1_test();
}

// Test function for the second serial port
void UART1_test()
{
  Serial2.println("AT");
  delay(500);
  while (Serial2.available())  // Check if there is data available to read from the second serial port
  {
    Serial.write(Serial2.read());  // Write the data from the second serial port to the main serial port
  }
  Serial2.println("AT+GMR");
  delay(500);
  while (Serial2.available())  // Check if there is data available to read from the second serial port
  {
    Serial.write(Serial2.read());  // Write the data from the second serial port to the main serial port
  }
  Serial.println("");
  delay(500);
}
