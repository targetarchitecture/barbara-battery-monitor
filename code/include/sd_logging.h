#pragma once
#include <Arduino.h>
#include <SPI.h>
#include <SD.h>
#include <LOLIN_EPD.h>

extern LOLIN_IL3897 EPD;

//extern void ePaperPrint(const String s);

void setup_sd_logging();
void writeToLog(String logFileName, String dataString);

// change this to match your SD shield or module;
const int chipSelect = D4;
