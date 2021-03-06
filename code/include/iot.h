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

extern volatile ulong lastIoTSentTime;

//extern SemaphoreHandle_t wifiSemaphore;
//extern SemaphoreHandle_t uartSemaphore;

extern volatile float leisureVoltage;
extern volatile float carVoltage;
extern volatile float solarVoltage;
extern volatile uint16_t colour[4];
extern volatile float temperature;

void loop_iot();
