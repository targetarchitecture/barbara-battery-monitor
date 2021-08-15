#pragma once
#include <Arduino.h>
#include <SPI.h>
#include <SD.h>
#include <Adafruit_GFX.h>
#include <Adafruit_EPD.h>

extern Adafruit_SSD1675 EPD;

//extern void ePaperPrint(const String s);

void setup_sd_logging();
void writeToLog(String logFileName, String dataString);

// change this to match your SD shield or module;
const int chipSelect = D4;