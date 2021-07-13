#pragma once
#include <NTPtimeESP.h>
#include <Wire.h>
#include <TimeLib.h>
#include <DS1307RTC.h>

/*
   This sketch shows an example of sending a reading to data.sparkfun.com once per day.

   It uses the Sparkfun testing stream so the only customizing required is the WiFi SSID and password.

   The Harringay Maker Space
   License: Apache License v2
*/

#define DEBUG_ON

void loop_ntp();
