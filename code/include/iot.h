#pragma once
#include <Arduino.h>
#include <config.h>
#include "AdafruitIO_WiFi.h"

void setup_io();
void loop_io();

extern void writeToLog(String dataString);

extern volatile float leisureVoltage;
extern volatile float carVoltage;
extern volatile float solarVoltage;
extern volatile bool floatMode;
extern volatile float temperature;
