#include <Arduino.h>
#include "epd.h"

LOLIN_IL3897 EPD(250, 122, EPD_DC, EPD_RST, EPD_CS, EPD_BUSY); //hardware SPI

void setup_epd()
{
    EPD.begin();
    EPD.clearBuffer();
    EPD.setCursor(0,0);
    EPD.setTextColor(EPD_BLACK);
    EPD.setTextSize(2);
    EPD.println("Barbara");
    EPD.partInit();

    EPD.display();
}



// void loop_epd()
// {
//     //   for (uint8_t i = 0; i < 4; i++)
//     //   {
//     //     EPD.setRotation(i);
//     //     EPD.clearBuffer();

//     //     EPD.setCursor(0,0);
//     //     EPD.println("hello world!");
//     //     EPD.println(EPD.getRotation());
//     //     EPD.display();
//     //     delay(2000);
//     //   }

//     //EPD.partDisplay(0, 32, gImage_num1, 32, 32);
//    // EPD.partDisplay(0, 32, gImage_num2, 32, 32);
//     //delay(2000);
// }


// void eprintDateTime(strDateTime _dateTime)
// {
// 	if (_dateTime.valid)
// 	{

// 		EPD.clearBuffer();

// 		EPD.setCursor(0, 50);

// 		EPD.print(_dateTime.year);
// 		EPD.print("-");
// 		EPD.print(_dateTime.month);
// 		EPD.print("-");
// 		EPD.print(_dateTime.day);
// 		EPD.print(" ");
// 		// EPD.print(_dateTime.dayofWeek);
// 		// EPD.print( " ");

// 		EPD.print(_dateTime.hour);
// 		EPD.print(":");
// 		EPD.print(_dateTime.minute);
// 		EPD.print(":");
// 		EPD.print(_dateTime.second);
// 		EPD.println();

// 		//    EPD.display();

// 		EPD.partInit();
// 		delay(100);
// 	}
// 	else
// 	{
// #ifdef DEBUG_ON
// 		Serial.println("Invalid time !!!");
// 		Serial.println("");
// #endif
// 	}
// }
