#include <Arduino.h>
#include "temperature.h"

// Create the MCP9808 temperature sensor object
Adafruit_MCP9808 tempsensor = Adafruit_MCP9808();

void setup_temperature()
{
  //wait for the i2c semaphore flag to become available
  xSemaphoreTake(i2cSemaphore, portMAX_DELAY);

  if (!tempsensor.begin(0x18))
  {
#ifdef SERIAL_OUPUT
    Serial.println("Couldn't find MCP9808! Check your connections and verify the address is correct.");
#endif
  }
  else
  {
#ifdef SERIAL_OUPUT
    Serial.println("Found MCP9808!");
#endif

    tempsensor.setResolution(0);
  }

  //give back the i2c flag for the next task
  xSemaphoreGive(i2cSemaphore);
}

void loop_temperature()
{
  //wait for the i2c semaphore flag to become available
  xSemaphoreTake(i2cSemaphore, portMAX_DELAY);

  tempsensor.wake(); // wake up, ready to read!

  temperature = tempsensor.readTempC();

  tempsensor.shutdown_wake(1); // shutdown MSP9808 - power consumption ~0.1 mikro Ampere, stops temperature sampling

  //give back the i2c flag for the next task
  xSemaphoreGive(i2cSemaphore);
}
