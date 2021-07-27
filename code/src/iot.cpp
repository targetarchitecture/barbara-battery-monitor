#include "iot.h"

#define SEND_EVERY_MS 60000
unsigned long lastUpdate;

AdafruitIO_WiFi iot(IO_USERNAME, IO_KEY, WIFI_SSID, WIFI_PASS);

// set up the feeds
AdafruitIO_Feed *leisure_voltage = iot.feed("leisure-voltage");
AdafruitIO_Feed *car_voltage = iot.feed("car-voltage");
AdafruitIO_Feed *solar_voltage = iot.feed("solar-voltage");
AdafruitIO_Feed *float_mode = iot.feed("float-mode");
AdafruitIO_Feed *cabin_temperature = iot.feed("temperature");

void setup_io()
{
  if (iot.status() == AIO_CONNECTED)
  {
    Serial.println("Already connected to Adafruit IO");

    return;
  }

  Serial.print("Connecting to Adafruit IO");

  // connect to io.adafruit.com
  iot.connect();

  // wait for a connection
  for (size_t i = 0; i < 10; i++)
  {
    if (iot.status() == AIO_CONNECTED)
    {
      break;
    }

    Serial.print(".");
    delay(1000);
  }

  // while (iot.status() < AIO_CONNECTED)
  // {
  //   Serial.print(".");
  //   delay(500);
  // }

  // we are connected
  Serial.println();
  Serial.println(iot.statusText());
}

void loop_io()
{
  // process messages and keep connection alive
  iot.run();

  if (millis() > (lastUpdate + SEND_EVERY_MS))
  {
    //save feeds to Adafruit IO
    leisure_voltage->save(leisureVoltage);
    car_voltage->save(carVoltage);
    solar_voltage->save(solarVoltage);
    float_mode->save(floatMode);
    cabin_temperature->save(temperature);

    // update timer
    lastUpdate = millis();
  }
}
