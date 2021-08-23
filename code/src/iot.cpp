#include "iot.h"

void loop_iot()
{
  //wait for the wifi semaphore flag to become available
  xSemaphoreTake(wifiSemaphore, portMAX_DELAY);

  if (wifiMulti.run() == WL_CONNECTED)
  {
    WiFiClientSecure client;
    client.setInsecure(); //skip verification

    Serial.print("connect: ");
    Serial.println(LOGIC_APP_HOST);
    while (!client.connect(LOGIC_APP_HOST, 443))
    {
      Serial.print(".");
    }
    Serial.println("Connected");

    DynamicJsonDocument doc(1024);

    doc["leisureVoltage"] = leisureVoltage;
    doc["carVoltage"] = carVoltage;
    doc["solarVoltage"] = solarVoltage;
    doc["temperature"] = temperature;
    doc["latitude"] = GPSModule.location.lat();
    doc["longitude"] = GPSModule.location.lat();
    doc["elevation"] = GPSModule.altitude.meters();
    doc["floatMode"] = floatMode;

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
    Serial.print(msg);

    Serial.print("\n*** Request sent, receiving response...");

    while (!!!client.available())
    {
      delay(50);
      Serial.print(".");
    }

    Serial.println();
    Serial.println("Got response");

    while (client.available())
    {
      Serial.write(client.read());
    }

    Serial.println();
    Serial.println("closing connection");
    client.stop();
  }

  //give back the wifi flag for the next task
  xSemaphoreGive(wifiSemaphore);
}
