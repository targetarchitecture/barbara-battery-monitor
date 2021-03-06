#include <Arduino.h>
#include <config.h>
#include <wificonnect.h>
#include <iot.h>
#include <gpsModule.h>
#include <mqtt.h>
#include <ntp.h>
#include <OTA.h>
#include <colour.h>
#include <Streaming.h>
#include <temperature.h>
#include <voltages.h>

extern PubSubClient MQTTClient;

volatile float leisureVoltage = 0;
volatile float carVoltage = 0;
volatile float solarVoltage = 0;
volatile float temperature = 0;
volatile uint16_t colour[4] = {0, 0, 0, 0}; //red,green,blue,clear

volatile ulong lastIoTSentTime = millis();

//SemaphoreHandle_t wifiSemaphore;
SemaphoreHandle_t i2cSemaphore;

extern TinyGPSPlus GPSModule;

void mqtt_task(void *pvParameter);
void IoT_task(void *pvParameter);
void GPS_task(void *pvParameter);
void temp_task(void *pvParameter);
void colour_task(void *pvParameter);
void volts_task(void *pvParameter);
void PANIC_task(void *pvParameter);

void setup()
{
	//turn off bluetooth
	btStop();

#ifdef SERIAL_OUPUT
	Serial.begin(115200);
	Serial << endl
		   << endl;
#endif

	setup_wifi();

	//create wifi Semaphore , and set to useable
	//wifiSemaphore = xSemaphoreCreateBinary();
	//xSemaphoreGive(wifiSemaphore);

	//create i2c Semaphore , and set to useable
	i2cSemaphore = xSemaphoreCreateBinary();
	xSemaphoreGive(i2cSemaphore);

	//create uart Semaphore , and set to useable
	//uartSemaphore = xSemaphoreCreateBinary();
	//xSemaphoreGive(uartSemaphore);

	setupOTA("Barbara");
	setup_ntp();
	setup_mqtt();
	setup_gps();
	setup_temperature();
	setup_colour();
	setup_voltages();

	//start task to read an send rotary information every 500ms
	xTaskCreate(&mqtt_task, "mqtt_task", 9999, NULL, 0, NULL);
	xTaskCreate(&IoT_task, "iot_task", 9999, NULL, 0, NULL);
	xTaskCreate(&GPS_task, "gps_task", 5999, NULL, 0, NULL);
	xTaskCreate(&temp_task, "temp_task", 5999, NULL, 0, NULL);
	xTaskCreate(&colour_task, "colour_task", 5999, NULL, 0, NULL);
	xTaskCreate(&volts_task, "volts_task", 5999, NULL, 0, NULL);
}

void loop()
{
	delay(10 * 1000);

	//check to see if we have had no transmission for 5 minutes
	ulong currentMillis = millis();

	//check to see if we have had no transmission for 5 minutes
	if (currentMillis - lastIoTSentTime > 1000 * 60 * 5)
	{
		xTaskCreate(&PANIC_task, "panic_task", 5999, NULL, 0, NULL);

#ifdef SERIAL_OUPUT
		Serial << "REBOOTING DUE TO INACTIVITY" << endl;
		Serial << "REBOOTING DUE TO INACTIVITY" << endl;
		Serial << "REBOOTING DUE TO INACTIVITY" << endl;
		Serial << "REBOOTING DUE TO INACTIVITY" << endl;
		Serial << "REBOOTING DUE TO INACTIVITY" << endl;
#endif

		delay(1000 * 10);
		ESP.restart();
	}
}

void PANIC_task(void *pvParameter)
{
	if (wifiMulti.run() == WL_CONNECTED)
	{
		if (MQTTClient.connect(MQTT_CLIENTID, MQTT_USERNAME, MQTT_KEY))
		{
			{
				std::stringstream payload;
				payload << "REBOOTING DUE TO IOT INACTIVITY. ";
				MQTTClient.publish(MQTT_PANIC_TOPIC, payload.str().c_str(), true);
			}

			// {
			// 	std::stringstream payload;
			// 	// payload << "REBOOTING DUE TO INACTIVITY. "
			// 	// 		<< "uart:" << uxSemaphoreGetCount(uartSemaphore) << " "
			// 	// 		<< "i2cSemaphore:" << uxSemaphoreGetCount(i2cSemaphore) << " "
			// 	// 		<< "wifiSemaphore:" << uxSemaphoreGetCount(wifiSemaphore);
			// 							payload << "REBOOTING DUE TO INACTIVITY. "
			// 			<< "i2cSemaphore:" << uxSemaphoreGetCount(i2cSemaphore) 
			// 	MQTTClient.publish(MQTT_PANIC_TOPIC, payload.str().c_str(), true);
			// }
		}
	}

	vTaskDelete(NULL);
}

//GPS task runs every 100
void GPS_task(void *pvParameter)
{
#ifdef SERIAL_OUPUT
	//xSemaphoreTake(uartSemaphore, portMAX_DELAY);
	Serial << "GPS_task uxTaskGetStackHighWaterMark:" << uxTaskGetStackHighWaterMark(NULL) << endl;
	//xSemaphoreGive(uartSemaphore);
#endif

	while (1)
	{
		loop_gps();

		delay(100);
	}

	vTaskDelete(NULL);
}

void IoT_task(void *pvParameter)
{
#ifdef SERIAL_OUPUT
	//xSemaphoreTake(uartSemaphore, portMAX_DELAY);
	Serial << "IoT_task uxTaskGetStackHighWaterMark:" << uxTaskGetStackHighWaterMark(NULL) << endl;
	//xSemaphoreGive(uartSemaphore);
#endif

	while (1)
	{
		loop_iot();

		delay(60 * 1000);
	}

	vTaskDelete(NULL);
}

void mqtt_task(void *pvParameter)
{
#ifdef SERIAL_OUPUT
	//xSemaphoreTake(uartSemaphore, portMAX_DELAY);
	Serial << "mqtt_task uxTaskGetStackHighWaterMark:" << uxTaskGetStackHighWaterMark(NULL) << endl;
	//xSemaphoreGive(uartSemaphore);
#endif

	while (1)
	{
		loop_mqtt();

		delay(5 * 1000);
	}

	vTaskDelete(NULL);
}

//temperature task
void temp_task(void *pvParameter)
{
#ifdef SERIAL_OUPUT
	//xSemaphoreTake(uartSemaphore, portMAX_DELAY);
	Serial << "temp_task uxTaskGetStackHighWaterMark:" << uxTaskGetStackHighWaterMark(NULL) << endl;
	//xSemaphoreGive(uartSemaphore);
#endif

	while (1)
	{
		loop_temperature();

		delay(5000);
	}

	vTaskDelete(NULL);
}

//colour task
void colour_task(void *pvParameter)
{
#ifdef SERIAL_OUPUT
	//xSemaphoreTake(uartSemaphore, portMAX_DELAY);
	Serial << "colour_task uxTaskGetStackHighWaterMark:" << uxTaskGetStackHighWaterMark(NULL) << endl;
	//xSemaphoreGive(uartSemaphore);
#endif

	while (1)
	{
		loop_colour();

		delay(5000);
	}

	vTaskDelete(NULL);
}

void volts_task(void *pvParameter)
{
#ifdef SERIAL_OUPUT
	//xSemaphoreTake(uartSemaphore, portMAX_DELAY);
	Serial << "volts_task uxTaskGetStackHighWaterMark:" << uxTaskGetStackHighWaterMark(NULL) << endl;
	//xSemaphoreGive(uartSemaphore);
#endif

	while (1)
	{
		loop_voltages();

		delay(5000);
	}

	vTaskDelete(NULL);
}