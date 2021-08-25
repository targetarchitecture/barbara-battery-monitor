#include <TinyGPS++.h>

// what's the name of the hardware serial port?
#define GPSSerial Serial2

#define PMTK_SET_NMEA_OUTPUT_RMCGGA "$PMTK314,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0*28"

void loop_gps();
void setup_gps();