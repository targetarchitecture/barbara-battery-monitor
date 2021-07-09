#pragma once
#include <Arduino.h>
#include <config.h>
#include "AdafruitIO_WiFi.h"

// holds the current count value for our sketch
int count2 = 0;

// holds the boolean (true/false) state of the light
bool is_on = false;

// track time of last published messages and limit feed->save events to once
// every IO_LOOP_DELAY milliseconds
#define IO_LOOP_DELAY 6000
unsigned long lastUpdate;

AdafruitIO_WiFi io(IO_USERNAME, IO_KEY, WIFI_SSID, WIFI_PASS);

// set up the 'counter' feed
AdafruitIO_Feed *counter = io.feed("leisure-voltage");

// set up the 'counter-two' feed
AdafruitIO_Feed *counter_two = io.feed("car-voltage");

// set up the 'light' feed
AdafruitIO_Feed *light = io.feed("solar-voltage");

void setup_io();
void loop_io();
