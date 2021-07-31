#include <Arduino.h>
#include "epd.h"

LOLIN_IL3897 EPD(250, 122, EPD_DC, EPD_RST, EPD_CS, EPD_BUSY); //hardware SPI

void setup_epd()
{
  EPD.begin();
  EPD.clearBuffer();
  EPD.setCursor(0, 0);
  EPD.setTextColor(EPD_BLACK);
  EPD.setTextSize(2);
  EPD.println("Barbara");
  EPD.partInit();

  // EPD.drawBitmap(0, 0, epd_bitmap_display, 255, 122, 0);
  // EPD.drawBitmap(0, 50, epd_bitmap_battery, 64, 60, 0);
  // EPD.drawBitmap(0, 100, epd_bitmap_float, 64, 60, 0);
  // EPD.drawBitmap(50, 50, epd_bitmap_solar, 64, 60, 0);
  // EPD.drawBitmap(50, 100, epd_bitmap_van, 64, 60, 0);

  EPD.display();
}

void loop_epd()
{
  EPD.clearBuffer();
  EPD.clearDisplay();
  delay(100);

 EPD.clearBuffer();

  EPD.setTextSize(2);
  EPD.setTextColor(EPD_BLACK);
  EPD.setCursor(5, 0); // 10 to the right and 18 down
  EPD.println("TEMP:" + String(temperature) + "C");
  EPD.setCursor(5, 30); // 10 to the right and 58 down
  EPD.println("LEISURE:" + String(leisureVoltage) + "v");
  EPD.setCursor(5, 60); // 10 to the right and 58 down
  EPD.println("CAR:" + String(carVoltage) + "v");
  EPD.setCursor(5, 90); // 10 to the right and 58 down
  EPD.println("SOLAR:" + String(solarVoltage) + "v");
  //EPD.setCursor(10, 95); // 10 to the right and 58 down
 // EPD.print("BARBARA");
 // EPD.setTextSize(1);
 // EPD.setCursor(130, 1);

  // EPD.print("Ok, Time = ");
  // epdPrint2digits(currentTime.Hour);
  // EPD.write(':');
  // epdPrint2digits(currentTime.Minute);
  // EPD.write(':');
  // epdPrint2digits(currentTime.Second);
  // EPD.print(", Date (D/M/Y) = ");
  // EPD.print(currentTime.Day);
  // EPD.write('/');
  // EPD.print(currentTime.Month);
  // EPD.write('/');
  // EPD.print(tmYearToCalendar(currentTime.Year));
  // EPD.println();

  EPD.display();
 // EPD.partInit();
  delay(100);
}

void epdPrint2digits(int number)
{
  if (number >= 0 && number < 10)
  {
    EPD.write('0');
  }
  EPD.print(number);
}

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
