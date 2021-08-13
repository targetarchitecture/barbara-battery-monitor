#pragma once
#include <Arduino.h>
#include <config.h>

#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>

void loop_io();

extern void writeToLog(String dataString);

extern ESP8266WiFiMulti wifiMulti;

extern volatile float leisureVoltage;
extern volatile float carVoltage;
extern volatile float solarVoltage;
extern volatile bool floatMode;
extern volatile float temperature;
extern volatile double latitude;
extern volatile double longitude;
extern volatile double elevation;