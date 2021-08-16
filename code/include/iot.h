#pragma once
#include <Arduino.h>
#include <WiFi.h>
#include <WiFiMulti.h>

extern WiFiMulti wifiMulti;

extern volatile float leisureVoltage;
extern volatile float carVoltage;
extern volatile float solarVoltage;
extern volatile bool floatMode;
extern volatile float temperature;
extern volatile double latitude;
extern volatile double longitude;
extern volatile double elevation;

void loop_io();
void setup_io();

extern void writeToLog(String dataString);