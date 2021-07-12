#include <Arduino.h>
#include "sd_logging.h"

//File root;

void setup_sd_logging()
{
  Serial.print("Initializing SD card...");

  if (!SD.begin(chipSelect))
  {
    Serial.println("initialization failed!");
    return;
  }
  Serial.println("initialization done.");

  // Serial.println(SD.size64());

  //   EPD.clearBuffer();
  //   EPD.setCursor(0, 0);

  //root = SD.open("/");

  EPD.println(SD.size64());
  EPD.display();

  // printDirectory(root, 0);

  Serial.println("done!");

  //  EPD.display();
  //delay(2000);
}

// void printDirectory(File dir, int numTabs)
// {
//     while (true)
//     {
//         File entry = dir.openNextFile();
//         if (!entry)
//         {
//             // no more files
//             break;
//         }
//         for (uint8_t i = 0; i < numTabs; i++)
//         {
//             Serial.print('\t');

//             EPD.println('\t');
//             //     EPD.println(EPD.getRotation());
//             //     EPD.display();
//         }
//         Serial.print(entry.name());
//         EPD.print(entry.name());
//         EPD.display();

//         if (entry.isDirectory())
//         {
//             Serial.println("/");
//             EPD.println('/');

//             EPD.display();

//             printDirectory(entry, numTabs + 1);
//         }
//         else
//         {
//             // files have sizes, directories do not
//             Serial.print("\t\t");
//             Serial.println(entry.size(), DEC);

//             EPD.println("\t\t");
//             EPD.println(entry.size(), DEC);

//             EPD.display();
//         }
//         entry.close();
//     }
// }

void writeToLog(String dataString)
{
  // open the file. note that only one file can be open at a time,
  // so you have to close this one before opening another.
  File dataFile = SD.open("datalog.txt", FILE_WRITE);

  // if the file is available, write to it:
  if (dataFile)
  {
    dataFile.println(dataString);
    dataFile.close();
    // print to the serial port too:
    Serial.println(dataString);
  }
  // if the file isn't open, pop up an error:
  else
  {
    Serial.println("error opening datalog.txt");
  }
}