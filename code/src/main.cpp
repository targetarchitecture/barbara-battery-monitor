#include <Arduino.h>
#include <epd.h>
#include <LOLIN_EPD.h>
#include <iot.h>
#include <ntp.h>
#include <sd_logging.h>
// #include <color.h>
// #include <rtc.h>

extern LOLIN_IL3897 EPD;

void eprintDateTime(strDateTime _dateTime) ;

extern strDateTime dateTime;

void setup()
{
    Serial.begin(115200);
    Serial.println(".");

    setup_epd();
    setup_sd_logging();
    // setup_rtc();
    // setup_color();
    setup_io();
}

void loop()
{
    Serial.println(".");
    delay(10000);

    loop_io();
     loop_ntp();
    // loop_color();
    //loop_epd();

    eprintDateTime(dateTime);
}

void eprintDateTime(strDateTime _dateTime) {
	if (_dateTime.valid) {
        EPD.setCursor(0,50);

		EPD.print(_dateTime.year);
		EPD.print( "-");
		EPD.print(_dateTime.month);
		EPD.print( "-");
		EPD.print(_dateTime.day);
		EPD.print( " ");
		// EPD.print(_dateTime.dayofWeek);
		// EPD.print( " ");

		EPD.print(_dateTime.hour);
		EPD.print( ":");
		EPD.print(_dateTime.minute);
		EPD.print( ":");
		EPD.print(_dateTime.second);
		EPD.println();

       // EPD.partInit();
        EPD.display();
	} else {
#ifdef DEBUG_ON
		Serial.println("Invalid time !!!");
		Serial.println("");
#endif    
	}
}
