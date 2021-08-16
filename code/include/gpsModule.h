//#include <Adafruit_GPS.h>
//#include "types.h"
#include <TinyGPS++.h>

// what's the name of the hardware serial port?
#define GPSSerial Serial2

// Connect to the GPS on the hardware port
//Adafruit_GPS GPS(&GPSSerial);

// Set GPSECHO to 'false' to turn off echoing the GPS data to the Serial console
// Set to 'true' if you want to debug and listen to the raw GPS sentences
//#define GPSECHO false

//uint32_t timer = millis();

//TinyGPSPlus gps;
//HardwareSerial SerialGPS(1);

void loop_gps();
void setup_gps();