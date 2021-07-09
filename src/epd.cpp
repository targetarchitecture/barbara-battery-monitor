#include <Arduino.h>
#include "epd.h"

File root;

LOLIN_IL3897 EPD(250, 122, EPD_DC, EPD_RST, EPD_CS, EPD_BUSY); //hardware SPI

void printDirectory(File dir, int numTabs)
{
    while (true)
    {
        File entry = dir.openNextFile();
        if (!entry)
        {
            // no more files
            break;
        }
        for (uint8_t i = 0; i < numTabs; i++)
        {
            Serial.print('\t');

            EPD.println('\t');
            //     EPD.println(EPD.getRotation());
            //     EPD.display();
        }
        Serial.print(entry.name());
        EPD.print(entry.name());
        EPD.display();

        if (entry.isDirectory())
        {
            Serial.println("/");
            EPD.println('/');

            EPD.display();

            printDirectory(entry, numTabs + 1);
        }
        else
        {
            // files have sizes, directories do not
            Serial.print("\t\t");
            Serial.println(entry.size(), DEC);

            EPD.println("\t\t");
            EPD.println(entry.size(), DEC);

            EPD.display();
        }
        entry.close();
    }
}

void setup_epd()
{
    EPD.begin();
    EPD.clearBuffer();
    EPD.setTextColor(EPD_BLACK);
    EPD.println("hello world!");
    // EPD.display();
    // delay(2000);
    EPD.partInit();
    delay(100);

    Serial.print("Initializing SD card...");

    if (!SD.begin(chipSelect))
    {
        Serial.println("initialization failed!");
        return;
    }
    Serial.println("initialization done.");

    EPD.clearBuffer();
    EPD.setCursor(0, 0);

    root = SD.open("/");

    printDirectory(root, 0);

    Serial.println("done!");

    EPD.display();
    delay(2000);
}

void loop_epd()
{
    //   for (uint8_t i = 0; i < 4; i++)
    //   {
    //     EPD.setRotation(i);
    //     EPD.clearBuffer();

    //     EPD.setCursor(0,0);
    //     EPD.println("hello world!");
    //     EPD.println(EPD.getRotation());
    //     EPD.display();
    //     delay(2000);
    //   }

    EPD.partDisplay(0, 32, gImage_num1, 32, 32);
    EPD.partDisplay(0, 32, gImage_num2, 32, 32);
    delay(2000);
}
