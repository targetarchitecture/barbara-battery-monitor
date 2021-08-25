#include "iot.h"

void loop_iot()
{
  //wait for the wifi semaphore flag to become available
  xSemaphoreTake(wifiSemaphore, portMAX_DELAY);

  if (wifiMulti.run() == WL_CONNECTED)
  {
    WiFiClientSecure client;
    client.setInsecure(); //skip verification

    xSemaphoreTake(uartSemaphore, portMAX_DELAY);

#ifdef SERIAL_OUPUT
    Serial << "connect: " << LOGIC_APP_HOST << endl;
#endif

    while (!client.connect(LOGIC_APP_HOST, 443))
    {
      delay(50);
#ifdef SERIAL_OUPUT
      Serial << ".";
#endif
    }
#ifdef SERIAL_OUPUT
    Serial.println("Connected");
#endif

    DynamicJsonDocument doc(1024);

    doc["leisureVoltage"] = leisureVoltage;
    doc["carVoltage"] = carVoltage;
    doc["solarVoltage"] = solarVoltage;
    doc["temperature"] = temperature;
    doc["latitude"] = GPSModule.location.lat();
    doc["longitude"] = GPSModule.location.lng();
    doc["elevation"] = GPSModule.altitude.meters();

    JsonArray array = doc.createNestedArray("colour");
    array.add(colour[0]);
    array.add(colour[1]);
    array.add(colour[2]);
    array.add(colour[3]);

    String postData;

    serializeJson(doc, postData);

    String path = LOGIC_APP_PATH;
    String msg = "POST " + path + " HTTP/1.1\r\n"
                                  "Host: " +
                 LOGIC_APP_HOST + "\r\n"
                                  "" +
                 "Content-Type: application/json\r\n"
                 "Content-Length: " +
                 postData.length() + "\r\n"
                                     "\r\n" +
                 postData;

    client.print(msg);

#ifdef SERIAL_OUPUT
    Serial.print(msg);
    Serial.print("\n*** Request sent, receiving response...");
#endif

    while (!!!client.available())
    {
      delay(50);
#ifdef SERIAL_OUPUT
      Serial.print(".");
#endif
    }

#ifdef SERIAL_OUPUT
    Serial.println();
    Serial.println("Got response");
#endif

    while (client.available())
    {
      auto X = client.read();
#ifdef SERIAL_OUPUT
      Serial.write(X);
#endif
    }

#ifdef SERIAL_OUPUT
    Serial.println();
    Serial.println("closing connection");
#endif

    client.stop();

    xSemaphoreGive(uartSemaphore);
  }

  //give back the wifi flag for the next task
  xSemaphoreGive(wifiSemaphore);
}
