#include <Arduino.h>
#include "colour.h"

// Global Variables
SparkFun_APDS9960 apds = SparkFun_APDS9960();

uint16_t ambient_light = 0;
uint16_t red_light = 0;
uint16_t green_light = 0;
uint16_t blue_light = 0;

void setup_color()
{
  // Initialize Serial port
  Serial.println();
  Serial.println(F("--------------------------------"));
  Serial.println(F("SparkFun APDS-9960 - ColorSensor"));
  Serial.println(F("--------------------------------"));

  // Initialize APDS-9960 (configure I2C and initial values)
  if (apds.init())
  {
    Serial.println(F("APDS-9960 initialization complete"));
  }
  else
  {
    Serial.println(F("Something went wrong during APDS-9960 init!"));
  }

  // Start running the APDS-9960 light sensor (no interrupts)
  if (apds.enableLightSensor(false))
  {
    Serial.println(F("Light sensor is now running"));
  }
  else
  {
    Serial.println(F("Something went wrong during light sensor init!"));
  }

  // Wait for initialization and calibration to finish
  delay(500);
}

void loop_color()
{
  // Read the light levels (ambient, red, green, blue)
  if (!apds.readAmbientLight(ambient_light) ||
      !apds.readRedLight(red_light) ||
      !apds.readGreenLight(green_light) ||
      !apds.readBlueLight(blue_light))
  {
    Serial.println("Error reading light values");
  }
  else
  {
    Serial.print("Ambient: ");
    Serial.print(ambient_light);
    Serial.print(" Red: ");
    Serial.print(red_light);
    Serial.print(" Green: ");
    Serial.print(green_light);
    Serial.print(" Blue: ");
    Serial.println(blue_light);

    if (blue_light > 5000)
    {
      floatMode = true;
    }
    else
    {
      floatMode = false;
    }
  }

  // Wait 1 second before next reading
  delay(1000);
}