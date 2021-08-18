#include <TinyGPS++.h>

// what's the name of the hardware serial port?
#define GPSSerial Serial2

extern volatile double latitude;
extern volatile double longitude;
extern volatile double elevation;

void loop_gps();
void setup_gps();