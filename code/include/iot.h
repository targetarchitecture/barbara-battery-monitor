#pragma once
#include <Arduino.h>
#include <config.h>
#include "AdafruitIO_WiFi.h"

void setup_io();
void loop_io();

extern void writeToLog(String dataString);

extern double leisureVoltage;
extern double carVoltage;
extern double solarVoltage;
extern bool floatMode;
extern double temperature;