#include <Arduino.h>
#include "voltages.h"

INA219_WE leisureVoltageSensor = INA219_WE(0x40);
INA219_WE carVoltageSensor = INA219_WE(0x44);
INA219_WE solarVoltageSensor = INA219_WE(0x41);

void setup_voltages()
{
  //wait for the i2c semaphore flag to become available
  xSemaphoreTake(i2cSemaphore, portMAX_DELAY);

  {
    bool init = leisureVoltageSensor.init();

#ifdef SERIAL_OUPUT
    if (!init)
    {
      Serial << "Couldn't find leisureVoltageSensor chip" << endl;
    }
    else
    {
      Serial << "Found leisureVoltageSensor chip" << endl;
    }
#endif
  }

  {
    bool init = carVoltageSensor.init();

#ifdef SERIAL_OUPUT
    if (!init)
    {
      Serial << "Couldn't find carVoltageSensor chip" << endl;
    }
    else
    {
      Serial << "Found carVoltageSensor chip" << endl;
    }
#endif
  }

  {
    bool init = solarVoltageSensor.init();

#ifdef SERIAL_OUPUT
    if (!init)
    {
      Serial << "Couldn't find solarVoltageSensor chip" << endl;
    }
    else
    {
      Serial << "Found solarVoltageSensor chip" << endl;
    }
#endif
  }
  //give back the i2c flag for the next task
  xSemaphoreGive(i2cSemaphore);
}

void loop_voltages()
{
  //wait for the i2c semaphore flag to become available
  xSemaphoreTake(i2cSemaphore, portMAX_DELAY);

  leisureVoltage = leisureVoltageSensor.getBusVoltage_V();
  carVoltage = carVoltageSensor.getBusVoltage_V();
  solarVoltage = solarVoltageSensor.getBusVoltage_V();

  xSemaphoreTake(uartSemaphore, portMAX_DELAY);

#ifdef SERIAL_OUPUT
  Serial << "leisureVoltageSensor: " << leisureVoltage << " V" << endl;
  Serial << "carVoltageSensor: " << carVoltage << " V" << endl;
  Serial << "solarVoltageSensor: " << solarVoltage << " V" << endl;
#endif

  xSemaphoreGive(uartSemaphore);

  //give back the i2c flag for the next task
  xSemaphoreGive(i2cSemaphore);
}