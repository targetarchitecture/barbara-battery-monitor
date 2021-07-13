#include <Arduino.h>
#include <epd.h>
#include <LOLIN_EPD.h>
#include <iot.h>
#include <ntp.h>
#include <sd_logging.h>
#include <colour.h>
#include <rtc.h>

// extern LOLIN_IL3897 EPD;
// extern strDateTime dateTime;
//extern Adafruit_APDS9960 apds;

void setup()
{
	Serial.begin(115200);
	Serial.println("");

	setup_epd();
	setup_sd_logging();

	setup_io();
	setup_rtc();

	setup_color();
}

void loop()
{



	// hasInternet
	// hasIoT
	// hasTime

	// Serial.println(".");
	delay(1000);

	loop_io();
	loop_ntp();
	loop_color();
	//loop_epd();

	//eprintDateTime(dateTime);
}

