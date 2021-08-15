#include <Arduino.h>
#include "sd_logging.h"

void setup_sd_logging()
{
  Serial.print("Initializing SD card...");

  if (!SD.begin(chipSelect))
  {
    Serial.println("initialization failed!");
    return;
  }
  Serial.println("initialization done.");

  // EPD.println(SD.size64());
  // EPD.display();

  Serial.println("done!");
}

void writeToLog(String logFileName, String dataString)
{
  // open the file. note that only one file can be open at a time,
  // so you have to close this one before opening another.
  File dataFile = SD.open(logFileName.c_str(), FILE_WRITE);

  // if the file is available, write to it:
  if (dataFile)
  {
    if (dataFile.size() == 0)
    {
      dataFile.println("date time,temperature,float,leisure,car,solar");
    }

    dataFile.println(dataString);
    dataFile.close();
    // print to the serial port too:
    Serial.println(dataString);
  }
  // if the file isn't open, pop up an error:
  else
  {
    Serial.print("error opening: ");
    Serial.println(logFileName);
  }
}