#include <Arduino.h>
#include <wificonnect.h>
#include <iot.h>
#include <gpsModule.h>
#include <mqtt.h>
#include <ntp.h>
#include "OTA.h"
//#include <colour.h>
//#include <temperature.h>
//#include <voltages.h>

volatile float leisureVoltage = 0;
volatile float carVoltage = 0;
volatile float solarVoltage = 0;
volatile float temperature = 0;
volatile bool floatMode = false;

SemaphoreHandle_t wifiSemaphore;

extern TinyGPSPlus GPSModule;

void mqtt_task(void *pvParameter);
void IoT_task(void *pvParameter);
void GPS_task(void *pvParameter);

void setup()
{
	//turn off bluetooth
	btStop();

	Serial.begin(115200);
	Serial.println("");
	Serial.println("");

	setup_wifi();

	//create wifi Semaphore , and set to useable
	wifiSemaphore = xSemaphoreCreateBinary();
	xSemaphoreGive(wifiSemaphore);

	setupOTA("Barbara");

	setup_ntp();

	//setup_color();

	//setup_temperature();

	//setup_voltages();

	//start task to read an send rotary information every 500ms
	xTaskCreate(&mqtt_task, "mqtt_task", 17000, NULL, 0, NULL);
	xTaskCreate(&IoT_task, "iot_task", 17000, NULL, 0, NULL);
	xTaskCreate(&GPS_task, "gps_task", 17000, NULL, 0, NULL);
}

void loop()
{
	//	loop_color();

	//	loop_temperature();

	//loop_voltages();

	delay(1000);
}

//GPS task runs every 100
void GPS_task(void *pvParameter)
{
	// UBaseType_t uxHighWaterMark;
	// uxHighWaterMark = uxTaskGetStackHighWaterMark(NULL);
	// Serial.print("GPS_task uxTaskGetStackHighWaterMark:");
	// Serial.println(uxHighWaterMark);

	setup_gps();

	while (1)
	{
		loop_gps();

		delay(100);
	}

	vTaskDelete(NULL);
}

void IoT_task(void *pvParameter)
{
	// UBaseType_t uxHighWaterMark;
	// uxHighWaterMark = uxTaskGetStackHighWaterMark(NULL);
	// Serial.print("IoT_task uxTaskGetStackHighWaterMark:");
	// Serial.println(uxHighWaterMark);

	while (1)
	{
		loop_iot();

		delay(60 * 1000);
	}

	vTaskDelete(NULL);
}

void mqtt_task(void *pvParameter)
{
	// UBaseType_t uxHighWaterMark;
	// uxHighWaterMark = uxTaskGetStackHighWaterMark(NULL);
	// Serial.print("mqtt_task uxTaskGetStackHighWaterMark:");
	// Serial.println(uxHighWaterMark);

	setup_mqtt();

	while (1)
	{
		loop_mqtt();

		delay(5000);
	}

	vTaskDelete(NULL);
}