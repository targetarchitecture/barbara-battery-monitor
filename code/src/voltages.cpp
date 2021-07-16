#include <Arduino.h>
#include "voltages.h"

INA219_WE leisureVoltageSensor = INA219_WE(0x40);
INA219_WE carVoltageSensor = INA219_WE(0x44);
INA219_WE solarVoltageSensor = INA219_WE(0x41);

void setup_voltages()
{
  if (!leisureVoltageSensor.init())
  {
    Serial.println("Couldn't find leisureVoltageSensor chip");
  }
  else
  {
    Serial.println("Found leisureVoltageSensor chip");
  }

  if (!carVoltageSensor.init())
  {
    Serial.println("Couldn't find carVoltageSensor chip");
  }
  else
  {
    Serial.println("Found carVoltageSensor chip");
  }

  if (!solarVoltageSensor.init())
  {
    Serial.println("Couldn't find solarVoltageSensor chip");
  }
  else
  {
    Serial.println("Found solarVoltageSensor chip");
  }
}

void loop_voltages()
{
  leisureVoltage = leisureVoltageSensor.getBusVoltage_V();
  carVoltage = carVoltageSensor.getBusVoltage_V();
  solarVoltage = solarVoltageSensor.getBusVoltage_V();

  Serial.print("leisureVoltageSensor: ");
  Serial.print(leisureVoltageSensor.getBusVoltage_V());
  Serial.println(" V");

  Serial.print("carVoltageSensor: ");
  Serial.print(carVoltageSensor.getBusVoltage_V());
  Serial.println(" V");

  Serial.print("solarVoltageSensor: ");
  Serial.print(solarVoltageSensor.getBusVoltage_V());
  Serial.println(" V");
}