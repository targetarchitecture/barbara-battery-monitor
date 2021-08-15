#include <Arduino.h>
#include <voltages.h>
#include <epd.h>
#include <wifi.h>
#include <config.h>
#include <iot.h>
#include <ntp.h>
#include <sd_logging.h>
#include <colour.h>
#include <rtc.h>
#include <temperature.h>

tmElements_t currentTime;
String logFileName;

volatile float leisureVoltage = 0;
volatile float carVoltage = 0;
volatile float solarVoltage = 0;
volatile float temperature = 0;
volatile double latitude = 0;
volatile double longitude = 0;
volatile double elevation = 0;
volatile bool floatMode = false;

void getCurrentTime();

void setup()
{
	Serial.begin(115200);
	Serial.println("");

	setup_wifi();

	setup_epd();

	//setup_sd_logging();

	setup_rtc();

	setup_color();

	setup_temperature();

	setup_voltages();
}

void loop()
{
	delay(10000);

	getCurrentTime();

	loop_io();

	loop_color();

	loop_temperature();

	loop_voltages();

	loop_epd();

	//eprintDateTime(dateTime);

	char dataString[1000];

	sprintf(dataString, "%d/%d/%d %02d:%02d:%02d,%.0f,%d,%.2f,%.2f,%.2f", tmYearToCalendar(currentTime.Year), currentTime.Month, currentTime.Day, currentTime.Hour, currentTime.Minute, currentTime.Second, temperature, floatMode, leisureVoltage, carVoltage, solarVoltage);

	//writeToLog(logFileName, dataString);
}

void getCurrentTime()
{
	if (RTC.read(currentTime))
	{
		Serial.print("Ok, RTC Time = ");
		print2digits(currentTime.Hour);
		Serial.write(':');
		print2digits(currentTime.Minute);
		Serial.write(':');
		print2digits(currentTime.Second);
		Serial.print(", Date (D/M/Y) = ");
		Serial.print(currentTime.Day);
		Serial.write('/');
		Serial.print(currentTime.Month);
		Serial.write('/');
		Serial.print(tmYearToCalendar(currentTime.Year));
		Serial.println();

		logFileName = "";
		logFileName += currentTime.Day;
		logFileName += "-";
		logFileName += currentTime.Month;
		logFileName += "-";
		logFileName += tmYearToCalendar(currentTime.Year);
		logFileName += ".log";

		Serial.print("log filename: ");
		Serial.println(logFileName);
	}
	else
	{
		Serial.println("Error reading the RTC,trying NTP");

		// first parameter: Time zone in floating point (for India); second parameter: 1 for European summer time; 2 for US daylight saving time; 0 for no DST adjustment; (contributed by viewwer, not tested by me)
		strDateTime NTPtime = NTPch.getNTPtime(0, 1);

		if (NTPtime.valid)
		{
			Serial.print("Ok, NTP Time = ");
			print2digits(NTPtime.hour);
			Serial.write(':');
			print2digits(NTPtime.minute);
			Serial.write(':');
			print2digits(NTPtime.second);
			Serial.print(", Date (D/M/Y) = ");
			Serial.print(NTPtime.day);
			Serial.write('/');
			Serial.print(NTPtime.month);
			Serial.write('/');
			Serial.print(NTPtime.year);
			Serial.println();

			currentTime.Day = NTPtime.day;
			currentTime.Hour = NTPtime.hour;
			currentTime.Minute = NTPtime.minute;
			currentTime.Month = NTPtime.month;
			currentTime.Second = NTPtime.second;
			currentTime.Wday = NTPtime.dayofWeek;
			currentTime.Year = CalendarYrToTm(NTPtime.year);

			Serial.println("The DS1307 writing time");

			RTC.write(currentTime);

			Serial.println("Completed DS1307 writing time");

			logFileName = currentTime.Day;
			logFileName += "-";
			logFileName += currentTime.Month;
			logFileName += "-";
			logFileName += tmYearToCalendar(currentTime.Year);
			logFileName += ".log";
		}
		else
		{
			Serial.println("Error reading both the RTC and NTP");

			//TODO: Blank EPD and display error

			delay(10000);

			ESP.restart();
		}
	}
}