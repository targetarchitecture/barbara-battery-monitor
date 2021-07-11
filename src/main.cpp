#include <Arduino.h>
#include <epd.h>
#include <iot.h>
#include <ntp.h>
#include <sdlogging.h>

void setup()
{
    Serial.begin(115200);

    setup_epd();
    setup_io();    
}

void loop(){
    loop_io();
    loop_ntp();
    loop_epd();
}