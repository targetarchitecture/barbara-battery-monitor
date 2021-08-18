#pragma once
#include <Arduino.h>
#include <WiFi.h>
#include <WiFiMulti.h>
#include <WiFiClientSecure.h>
#include <config.h>
#include <ArduinoJson.h>

extern WiFiMulti wifiMulti;

extern volatile float leisureVoltage;
extern volatile float carVoltage;
extern volatile float solarVoltage;
extern volatile bool floatMode;
extern volatile float temperature;
extern volatile double latitude;
extern volatile double longitude;
extern volatile double elevation;

void loop_iot();

extern void writeToLog(String dataString);