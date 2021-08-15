#pragma once
#include <Wire.h>
#include <TimeLib.h>
#include <DS1307RTC.h>
#include <NTPtimeESP.h>

void setup_rtc();
void print2digits(int number);
//void loop_rtc();

extern NTPtime NTPch;
//extern strDateTime dateTime;