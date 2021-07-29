#pragma once
#include <Arduino.h>
#include <config.h>
#include "AdafruitIO_WiFi.h"

void loop_io();

extern void writeToLog(String dataString);

extern volatile float leisureVoltage;
extern volatile float carVoltage;
extern volatile float solarVoltage;
extern volatile bool floatMode;
extern volatile float temperature;
extern volatile double latitude;
extern volatile double longitude;
extern volatile double elevation;