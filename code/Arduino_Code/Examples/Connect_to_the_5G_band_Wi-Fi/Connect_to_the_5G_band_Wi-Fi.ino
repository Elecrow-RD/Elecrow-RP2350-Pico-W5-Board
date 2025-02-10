// Define the RX and TX pins for Serial2 communication
#define Serial2_RX 5
#define Serial2_TX 4

// Flag to check the status of the WiFi connection
int ok_flag = 0;

// Define the command to set the WiFi mode to AP+STA
#define SET_WIFI_MODE           "AT+WMODE=3,1"
// Define the command to set the WiFi SSID and password
// Please replace "yanfa_software_5G" and "yanfa-123456" with your own SSID and password
#define SET_WIFI_SSID_PASSWORD  "AT+WJAP=\"yanfa_software_5G\",\"yanfa-123456\""

void setup() {
  // Initialize the serial communication at 115200 baud rate
  Serial.begin(115200);
  // Set the RX and TX pins for Serial2 communication
  Serial2.setRX(Serial2_RX);
  Serial2.setTX(Serial2_TX);
  // Start Serial2 communication at 115200 baud rate
  Serial2.begin(115200);
  // Delay for 5 seconds to allow the module to initialize
  delay(5000);
  // Call the UART2 test function
  UART2_test();
}

void loop() {
  // Main code to run repeatedly
  // This loop is empty as the setup function does all the work
}

// Function to test UART2 communication and set WiFi configuration
void UART2_test() {
  // Clear the serial buffer
  clear_serial();
  // Reset the OK flag
  ok_flag = 0;
  // Send the command to set the WiFi mode
  Serial2.println(SET_WIFI_MODE);
  // Wait until the OK flag is set
  while (!ok_flag) {
    if (Serial2.find("OK")) {
      // Delay for 1 second
      delay(1000);
      // Set the OK flag to true
      ok_flag = true;
      // Print a message to indicate the WiFi mode has been set
      Serial.println("Set WIFI Mode Ok!");
    }
  }
  // Clear the serial buffer again
  clear_serial();
  // Reset the OK flag
  ok_flag = 0;
  // Send the command to set the WiFi SSID and password
  Serial2.println(SET_WIFI_SSID_PASSWORD);
  // Wait until the OK flag is set
  while (!ok_flag) {
    if (Serial2.find("OK")) {
      // Delay for 1 second
      delay(1000);
      // Set the OK flag to true
      ok_flag = true;
      // Print a message to indicate the WiFi is connected
      Serial.println("WIFI Connected!");
    }
  }
}

// Function to clear the serial buffers for Serial and Serial2
void clear_serial() {
  // Clear Serial2 buffer
  while (Serial2.read() >= 0);
  // Clear Serial buffer
  while (Serial.read() >= 0);
}
