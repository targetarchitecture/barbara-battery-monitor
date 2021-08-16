#include "wificonnect.h"

WiFiMulti wifiMulti;

void setup_wifi()
{
  WiFi.mode(WIFI_STA);
  wifiMulti.addAP(WIFI_SSID_1, WIFI_PASS_1);
  wifiMulti.addAP(WIFI_SSID_2, WIFI_PASS_2);

  Serial.println("Connecting Wifi...");

  if (wifiMulti.run(10000) == WL_CONNECTED)
  {
    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
  }
}

void loop_wifi()
{
  if (wifiMulti.run(1000) != WL_CONNECTED)
  {
    Serial.println("WiFi not connected!");
  }
}
