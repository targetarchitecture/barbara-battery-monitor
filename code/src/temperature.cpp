#include <Arduino.h>
#include "temperature.h"

// Create the MCP9808 temperature sensor object
Adafruit_MCP9808 tempsensor = Adafruit_MCP9808();

void setup_temperature()
{
  if (!tempsensor.begin(0x18))
  {
    Serial.println("Couldn't find MCP9808! Check your connections and verify the address is correct.");
  }

  Serial.println("Found MCP9808 temperature sensor");

  tempsensor.setResolution(3); // sets the resolution mode of reading
}

void loop_temperature()
{
  tempsensor.wake();                      // wake up MCP9808 - power consumption ~200 mikro Ampere, ready to read!

  float c = tempsensor.readTempC();

  Serial.print("Temp: ");
  Serial.print(c, 4);
  Serial.println("*C");

  tempsensor.shutdown_wake(1); // shutdown MSP9808 - power consumption ~0.1 mikro Ampere, stops temperature sampling
}