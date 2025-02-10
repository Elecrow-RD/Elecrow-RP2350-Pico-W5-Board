#include "DHT20.h"

DHT20 DHT(&Wire);   //  or use 2nd I2C interface &Wire


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("DHT20 LIBRARY VERSION: ");
  Serial.println(DHT20_LIB_VERSION);
  Serial.println();

  Wire.setSDA(20);  //  select your pin numbers here
  Wire.setSCL(21);  //  select your pin numbers here
  Wire.begin();

  delay(2000);

  Serial.println("Type,\tStatus,\tHumidity (%),\tTemperature (C)");
}


void loop()
{
  //  READ DATA
  Serial.print("DHT20, \t");
  int status = DHT.read();
  switch (status)
  {
  case DHT20_OK:
    Serial.print("OK,\t");
    break;
  case DHT20_ERROR_CHECKSUM:
    Serial.print("Checksum error,\t");
    break;
  case DHT20_ERROR_CONNECT:
    Serial.print("Connect error,\t");
    break;
  case DHT20_MISSING_BYTES:
    Serial.print("Missing bytes,\t");
    break;
  case DHT20_ERROR_BYTES_ALL_ZERO:
    Serial.print("All bytes read zero");
    break;
  case DHT20_ERROR_READ_TIMEOUT:
    Serial.print("Read time out");
    break;
  case DHT20_ERROR_LASTREAD:
    Serial.print("Error read too fast");
    break;
  default:
    Serial.print("Unknown error,\t");
    break;
  }

  //  DISPLAY DATA, sensor has only one decimal.
  Serial.print("Humidity: ");
  Serial.print(DHT.getHumidity(), 1);
  Serial.print(",\t");
  Serial.print("Temperature: ");
  Serial.println(DHT.getTemperature(), 1);

  delay(2000);
}


//  -- END OF FILE --
