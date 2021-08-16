#include <Arduino.h>
//#include <voltages.h>
#include <wificonnect.h>
//#include <config.h>
//#include <iot.h>
#include <ntp.h>
#include <gpsModule.h>
//#include <colour.h>
//#include <temperature.h>

volatile float leisureVoltage = 0;
volatile float carVoltage = 0;
volatile float solarVoltage = 0;
volatile float temperature = 0;
volatile double latitude = 0;
volatile double longitude = 0;
volatile double elevation = 0;
volatile bool floatMode = false;

void setup()
{
	Serial.begin(115200);
	Serial.println("");
	Serial.println("");

	setup_wifi();

	setup_ntp();

	setup_gps();

	//setup_epd();

	//setup_sd_logging();

	//setup_rtc();

	//setup_color();

	//setup_temperature();

	//setup_voltages();
}

void loop()
{
	delay(1000);

	loop_wifi();

	loop_ntp();

	loop_gps();

	//loop_io();

	//	loop_color();

	//	loop_temperature();

	//loop_voltages();

	//loop_epd();

	//eprintDateTime(dateTime);

	//	char dataString[1000];

	//sprintf(dataString, "%d/%d/%d %02d:%02d:%02d,%.0f,%d,%.2f,%.2f,%.2f", tmYearToCalendar(currentTime.Year), currentTime.Month, currentTime.Day, currentTime.Hour, currentTime.Minute, currentTime.Second, temperature, floatMode, leisureVoltage, carVoltage, solarVoltage);

	//writeToLog(logFileName, dataString);
}
