#include "mqtt.h"

//MQTT definitions
WiFiClient c;
PubSubClient MQTTClient(c);

uint32_t last_satellites = 0;
double last_lat = 0;
double last_lng = 0;
float last_temperature = 0;
long last_colour = 0;
int last_hdop = 0;


void setup_mqtt()
{
    //wait for the wifi semaphore flag to become available
    //xSemaphoreTake(wifiSemaphore, portMAX_DELAY);

    MQTTClient.setServer(MQTT_SERVER, 1883);

    if (wifiMulti.run() == WL_CONNECTED)
    {
#ifdef SERIAL_OUPUT
        Serial.println("Connecting to MQTT server");
#endif
        if (MQTTClient.connect(MQTT_CLIENTID, MQTT_USERNAME, MQTT_KEY))
        {
#ifdef SERIAL_OUPUT
            Serial.println("Connected to MQTT server");
#endif
            MQTTClient.publish(MQTT_IP_TOPIC, WiFi.localIP().toString().c_str(), true);
        }
    }

    //give back the wifi flag for the next task
    //xSemaphoreGive(wifiSemaphore);
}

void loop_mqtt()
{
    //wait for the wifi semaphore flag to become available
    //xSemaphoreTake(wifiSemaphore, portMAX_DELAY);

    if (wifiMulti.run() == WL_CONNECTED)
    {
        if (MQTTClient.connect(MQTT_CLIENTID, MQTT_USERNAME, MQTT_KEY))
        {
#ifdef SERIAL_OUPUT
            Serial.println("Connected to MQTT server");
#endif
            {
                std::stringstream payload;
                payload << GPSModule.location.age();
                MQTTClient.publish(MQTT_AGE_TOPIC, payload.str().c_str(), true);

                lastIoTSentTime = millis();
            }

            if (last_satellites != GPSModule.satellites.value())
            {
                {
                    std::stringstream payload;
                    payload << GPSModule.satellites.value();
                    MQTTClient.publish(MQTT_SATELITE_TOPIC, payload.str().c_str(), true);

                    //lastSentTime = millis();
                }

                last_satellites = GPSModule.satellites.value();
            }

            if (last_hdop != GPSModule.hdop.value())
            {
                {
                    std::stringstream payload;
                    payload << GPSModule.hdop.value();
                    MQTTClient.publish(MQTT_HDOP_TOPIC, payload.str().c_str(), true);
                }

                last_hdop = GPSModule.hdop.value();
            }

            if (last_lat != GPSModule.location.lat())
            {
                {
                    std::stringstream payload;
                    payload << GPSModule.location.lat();
                    MQTTClient.publish(MQTT_LAT_TOPIC, payload.str().c_str(), true);

                    //lastSentTime = millis();
                }

                last_lat = GPSModule.location.lat();
            }

            if (last_lng != GPSModule.location.lng())
            {
                {
                    std::stringstream payload;
                    payload << GPSModule.location.lng();
                    MQTTClient.publish(MQTT_LON_TOPIC, payload.str().c_str(), true);

                    //lastSentTime = millis();
                }

                last_lng = GPSModule.location.lng();
            }

            if (last_temperature != temperature)
            {
                {
                    std::stringstream payload;
                    payload << temperature;
                    MQTTClient.publish(MQTT_TEMP_TOPIC, payload.str().c_str(), true);

                    //lastSentTime = millis();
                }

                last_temperature = temperature;
            }

            if (last_colour != colour[0] + colour[1] + colour[2] + colour[3])
            {
                {
                    std::stringstream payload;
                    payload << "R:" << colour[0] << "G:" << colour[1] << "B:" << colour[2] << "C:" << colour[3];
                    MQTTClient.publish(MQTT_COLOUR_TOPIC, payload.str().c_str(), true);

                    //lastSentTime = millis();
                }
                last_colour = colour[0] + colour[1] + colour[2] + colour[3];
            }
        }
    }

    //give back the wifi flag for the next task
    //xSemaphoreGive(wifiSemaphore);
}