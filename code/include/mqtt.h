//#pragma once
#include <config.h>
#include <PubSubClient.h>
#include <WiFi.h>
#include <WiFiMulti.h>
#include <WiFiClientSecure.h>
#include <ArduinoJson.h>
#include <TinyGPS++.h>
#include <sstream>
#include <Streaming.h>

extern WiFiMulti wifiMulti;

extern TinyGPSPlus GPSModule;

extern SemaphoreHandle_t wifiSemaphore;

extern volatile float temperature;
extern volatile uint16_t colour[4];

void setup_mqtt();
void loop_mqtt();

#define MQTT_CLIENTID "Barbara"
#define MQTT_IP_TOPIC  "barbara/ip"
#define MQTT_LAT_TOPIC "barbara/location/lat"
#define MQTT_LON_TOPIC "barbara/location/lon"
#define MQTT_AGE_TOPIC "barbara/age"
#define MQTT_SATELITE_TOPIC "barbara/satelites"
#define MQTT_TEMP_TOPIC "barbara/temp"
#define MQTT_COLOUR_TOPIC "barbara/colour"
