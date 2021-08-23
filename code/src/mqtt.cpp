#include "mqtt.h"

//MQTT definitions
WiFiClient c;
PubSubClient MQTTClient(c);

uint32_t last_satellites = 0;
double last_lat = 0;
double last_lng = 0;

void setup_mqtt()
{

    //wait for the wifi semaphore flag to become available
    xSemaphoreTake(wifiSemaphore, portMAX_DELAY);

    // //MQTT definitions
    // WiFiClient c;
    // PubSubClient MQTTClient(c);

    MQTTClient.setServer(MQTT_SERVER, 1883);

    if (wifiMulti.run() == WL_CONNECTED)
    {
        Serial.println("Connecting to MQTT server");

        if (MQTTClient.connect(MQTT_CLIENTID, MQTT_USERNAME, MQTT_KEY))
        {
            Serial.println("Connected to MQTT server");

            MQTTClient.publish(MQTT_IP_TOPIC, WiFi.localIP().toString().c_str(), true);
        }
    }

    //give back the wifi flag for the next task
    xSemaphoreGive(wifiSemaphore);
}

void loop_mqtt()
{
    //wait for the wifi semaphore flag to become available
    xSemaphoreTake(wifiSemaphore, portMAX_DELAY);

    if (wifiMulti.run() == WL_CONNECTED)
    {
        //Serial.println("connect mqtt...");
        if (MQTTClient.connect(MQTT_CLIENTID, MQTT_USERNAME, MQTT_KEY))
        {
            //Serial.println("Connected to MQTT server");
            {
                std::stringstream payload;
                payload << GPSModule.location.age();
                MQTTClient.publish(MQTT_AGE_TOPIC, payload.str().c_str(), true);
            }

            if (last_satellites != GPSModule.satellites.value())
            {
                {
                    std::stringstream payload;
                    payload << GPSModule.satellites.value();
                    MQTTClient.publish(MQTT_SATELITE_TOPIC, payload.str().c_str(), true);
                }
            }

            if (GPSModule.location.age() < 20000)
            {
                if (last_lat != GPSModule.location.lat())
                {
                    {
                        std::stringstream payload;
                        payload << GPSModule.location.lat();
                        MQTTClient.publish(MQTT_LAT_TOPIC, payload.str().c_str(), true);
                    }
                }
                if (last_lng != GPSModule.location.lng())
                {
                    {
                        std::stringstream payload;
                        payload << GPSModule.location.lng();
                        MQTTClient.publish(MQTT_LON_TOPIC, payload.str().c_str(), true);
                    }
                }
            }
            else
            {
                MQTTClient.publish(MQTT_LAT_TOPIC, "NO GPS", true);
                MQTTClient.publish(MQTT_LON_TOPIC, "NO GPS", true);
            }
        }
    }

    //give back the wifi flag for the next task
    xSemaphoreGive(wifiSemaphore);
}