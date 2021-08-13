#include "iot.h"

#define SEND_EVERY_MS 60000
unsigned long lastUpdate;

void loop_io()
{
  if (wifiMulti.run() == WL_CONNECTED)
  {
    Serial.println("Already connected to Adafruit IO");
  }

  if (millis() > (lastUpdate + SEND_EVERY_MS))
  {
    //save feeds to Adafruit IO

    // update timer
    lastUpdate = millis();
  }
}
