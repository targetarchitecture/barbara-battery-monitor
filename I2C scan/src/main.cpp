#include <Arduino.h>
#include <Wire.h>

void i2cScan();

void setup()
{
  Wire.begin(SDA, SCL);   //I2C bus
  Serial.begin(115200); //ESP32 USB Port
  Serial.println("I2C Scanner");

  i2cScan();

  delay(60000);

  ESP.restart();
}

void loop()
{
}

void i2cScan()
{
  byte error, address;
  int nDevices;
  Serial.println("Scanning...");
  nDevices = 0;
  for (address = 1; address < 127; address++)
  {
    Wire.beginTransmission(address);
    error = Wire.endTransmission();
    if (error == 0)
    {
        Serial.print("I2C device found at address 0x");
        if (address < 16)
        {
          Serial.print("0");
        }
        Serial.println(address, HEX);      

      nDevices++;
    }
    else if (error == 4)
    {
      Serial.print("Unknow error at address 0x");
      if (address < 16)
      {
        Serial.print("0");
      }
      Serial.println(address, HEX);
    }
  }

  if (nDevices == 0)
  {
    Serial.println("No I2C devices found\n");
  }
  else
  {
    Serial.println("done\n");
  }
}
