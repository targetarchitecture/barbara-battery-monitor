#include "wificonnect.h"

WiFiMulti wifiMulti;

void setup_wifi()
{
  WiFi.mode(WIFI_STA);
  wifiMulti.addAP(WIFI_SSID_1, WIFI_PASS_1);
  wifiMulti.addAP(WIFI_SSID_2, WIFI_PASS_2);
  wifiMulti.addAP(WIFI_SSID_3, WIFI_PASS_3);

  Serial << "Connecting Wifi..." << endl;

  if (wifiMulti.run(10000) == WL_CONNECTED)
  {
    Serial << endl
           << "WiFi connected" << endl
           << "IP address: " << WiFi.localIP() << endl;
  }
}

