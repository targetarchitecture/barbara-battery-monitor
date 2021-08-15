#pragma once
#include <Arduino.h>
#include <config.h>

#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
<<<<<<< Updated upstream
=======

#include <ESP8266HTTPClient.h>

#include <WiFiClientSecureBearSSL.h>

ESP8266WiFiMulti WiFiMulti;
>>>>>>> Stashed changes

void loop_io();
void setup_io();

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