#include <Arduino.h>
#include "epd.h"

LOLIN_IL3897 EPD(250, 122, EPD_DC, EPD_RST, EPD_CS, EPD_BUSY); //hardware SPI

void setup_epd()
{
    EPD.begin();
    EPD.clearBuffer();
    EPD.setCursor(0,0);
    EPD.setTextColor(EPD_BLACK);
    EPD.setTextSize(2);
    EPD.println("Barbara");
    EPD.partInit();

    EPD.display();
}



// void loop_epd()
// {
//     //   for (uint8_t i = 0; i < 4; i++)
//     //   {
//     //     EPD.setRotation(i);
//     //     EPD.clearBuffer();

//     //     EPD.setCursor(0,0);
//     //     EPD.println("hello world!");
//     //     EPD.println(EPD.getRotation());
//     //     EPD.display();
//     //     delay(2000);
//     //   }

//     //EPD.partDisplay(0, 32, gImage_num1, 32, 32);
//    // EPD.partDisplay(0, 32, gImage_num2, 32, 32);
//     //delay(2000);
// }
