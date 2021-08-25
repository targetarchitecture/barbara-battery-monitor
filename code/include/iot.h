//#pragma once
#include <config.h>
#include <TinyGPS++.h>
#include <ArduinoJson.h>
#include <WiFi.h>
#include <WiFiMulti.h>
#include <WiFiClientSecure.h>
#include <Streaming.h>

extern WiFiMulti wifiMulti;

extern TinyGPSPlus GPSModule;

extern SemaphoreHandle_t wifiSemaphore;

extern volatile float leisureVoltage;
extern volatile float carVoltage;
extern volatile float solarVoltage;
extern volatile bool colour;
extern volatile float temperature;

void loop_iot();

