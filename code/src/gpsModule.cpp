#include "gpsModule.h"

TinyGPSPlus GPSModule;

void setup_gps()
{
  // 9600 NMEA is the default baud rate for Adafruit MTK GPS's- some use 4800
  GPSSerial.begin(9600);

  //turn on RMC (recommended minimum) and GGA (fix data) including altitude
  GPSSerial.write(PMTK_SET_NMEA_OUTPUT_RMCGGA);
  GPSSerial.flush();

  // #define PMTK_SET_NMEA_UPDATE_10Sec "$PMTK220,10000*2F"
  //   GPSSerial.write(PMTK_SET_NMEA_UPDATE_10Sec); // 10 sec update rate
  //   GPSSerial.flush();

  delay(1000);
}

void loop_gps() // run over and over again
{
  while (GPSSerial.available() > 0)
  {
    GPSModule.encode(GPSSerial.read());
  }
}