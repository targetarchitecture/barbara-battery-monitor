#include "iot.h"

// holds the current count value for our sketch
int count2 = 0;

// holds the boolean (true/false) state of the light
bool is_on = false;

// track time of last published messages and limit feed->save events to once
// every IO_LOOP_DELAY milliseconds
#define IO_LOOP_DELAY 6000
unsigned long lastUpdate;

AdafruitIO_WiFi iot(IO_USERNAME, IO_KEY, WIFI_SSID, WIFI_PASS);

// set up the 'counter' feed
AdafruitIO_Feed *counter = iot.feed("leisure-voltage");

// set up the 'counter-two' feed
AdafruitIO_Feed *counter_two = iot.feed("car-voltage");

// set up the 'light' feed
AdafruitIO_Feed *light = iot.feed("solar-voltage");

void setup_io()
{
  Serial.print("Connecting to Adafruit IO");

  // connect to io.adafruit.com
  iot.connect();

  // attach message handler for the counter feed.
  //counter->onMessage(handleCount);

  // attach the same message handler for the second counter feed.
  //counter_two->onMessage(handleCount);

  // attach a new message handler for the light feed.
  //light->onMessage(handleLight);

  // wait for a connection
  while (iot.status() < AIO_CONNECTED)
  {
    Serial.print(".");
    delay(500);
  }

  // we are connected
  Serial.println();
  Serial.println(iot.statusText());

  // make sure all feeds get their current values right away
  // counter->get();
  // counter_two->get();
  // light->get();
}

void loop_io()
{
  // process messages and keep connection alive
  iot.run();

  if (millis() > (lastUpdate + IO_LOOP_DELAY))
  {
    Serial.println();

    writeToLog(String(count2));

    // save current count to 'counter'
    Serial.print("sending -> counter ");
    Serial.println(count2);
    counter->save(count2);

    // increment the count by 1 and save the value to 'counter-two'
    Serial.print("sending -> counter-two ");
    Serial.println(analogRead(A0));
    counter_two->save(analogRead(A0));

    // print out the light value we are sending to Adafruit IO
    Serial.print("sending -> light ");
    if (is_on)
      Serial.println("is on.\n");
    else
      Serial.println("is off.\n");

    // save state of light to 'light' feed
    light->save(is_on);

    // increment count value
    count2++;

    // for the purpose of this demo, toggle the
    // light state based on the count value
    if ((count2 % 2) == 0)
      is_on = true;
    else
      is_on = false;

    // update timer
    lastUpdate = millis();

    //This tries to stop the CPU melting
    delay(1000);
  }
}

// // you can set a separate message handler for a single feed,
// // as we do in this example for the light feed
// void handleLight(AdafruitIO_Data *data) {

//   // print out the received light value
//   Serial.print("received <- light ");

//   // use the isTrue helper to get the
//   // boolean state of the light
//   if(data->isTrue())
//     Serial.println("is on.");
//   else
//     Serial.println("is off.");

// }

// // you can also attach multiple feeds to the same
// // meesage handler function. both counter and counter-two
// // are attached to this callback function, and messages
// // for both will be received by this function.
// void handleCount(AdafruitIO_Data *data) {

//   Serial.print("received <- ");

//   // since we are using the same function to handle
//   // messages for two feeds, we can use feedName() in
//   // order to find out which feed the message came from.
//   Serial.print(data->feedName());
//   Serial.print(" ");

//   // print out the received count or counter-two value
//   Serial.println(data->value());

// }
