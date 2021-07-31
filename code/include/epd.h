#pragma once
#include <Arduino.h>
#include <TimeLib.h>
#include <DS1307RTC.h>
#include <Adafruit_GFX.h>
#include "Adafruit_EPD.h"

/*D1 mini*/
#define EPD_CS D0
#define EPD_DC D8
#define EPD_RST -1  // can set to -1 and share with microcontroller Reset!
#define EPD_BUSY -1 // can set to -1 to not use a pin (will wait a fixed delay)

extern volatile float leisureVoltage;
extern volatile float carVoltage;
extern volatile float solarVoltage;
extern volatile bool floatMode;
extern volatile float temperature;
extern volatile double latitude;
extern volatile double longitude;
extern volatile double elevation;

extern tmElements_t currentTime;

void setup_epd();
void loop_epd();
void epdPrint2digits(int number);
