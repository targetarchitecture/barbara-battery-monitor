#pragma once
#include <Arduino.h>
#include <LOLIN_EPD.h>
//#include <Adafruit_GFX.h>

/*D1 mini*/
#define EPD_CS D0
#define EPD_DC D8
#define EPD_RST -1  // can set to -1 and share with microcontroller Reset!
#define EPD_BUSY -1 // can set to -1 to not use a pin (will wait a fixed delay)


//void printDirectory(File dir, int numTabs);
void setup_epd();
//void ePaperPrint(const String &s);
//void loop_epd();

