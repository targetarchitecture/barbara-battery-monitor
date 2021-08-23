#pragma once
#include <Arduino.h>
#include <PubSubClient.h>
#include <WiFi.h>
#include <WiFiMulti.h>
#include <WiFiClientSecure.h>
#include <config.h>
#include <ArduinoJson.h>
#include <TinyGPS++.h>
#include <sstream>

extern WiFiMulti wifiMulti;

extern TinyGPSPlus GPSModule;

extern SemaphoreHandle_t wifiSemaphore;

void setup_mqtt();
void loop_mqtt();

#define MQTT_IP_TOPIC  "barbara/ip"
#define MQTT_LAT_TOPIC "barbara/location/lat"
#define MQTT_LON_TOPIC "barbara/location/lon"
#define MQTT_AGE_TOPIC "barbara/age"
#define MQTT_SATELITE_TOPIC "barbara/satelites"