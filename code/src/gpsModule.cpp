#include "gpsModule.h"

TinyGPSPlus GPSModule;
//HardwareSerial SerialGPS(1);

void setup_gps()
{
  //GPSSerial.begin(9600, SERIAL_8N1, 16, 17);

  // 9600 NMEA is the default baud rate for Adafruit MTK GPS's- some use 4800
  GPSSerial.begin(9600);

//turn on RMC (recommended minimum) and GGA (fix data) including altitude
#define PMTK_SET_NMEA_OUTPUT_RMCGGA "$PMTK314,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0*28"
  GPSSerial.write(PMTK_SET_NMEA_OUTPUT_RMCGGA);

  // uncomment this line to turn on RMC (recommended minimum) and GGA (fix data) including altitude
  // GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCGGA);

#define PMTK_SET_NMEA_UPDATE_10Sec "$PMTK220,10000*2F"
  GPSSerial.write(PMTK_SET_NMEA_UPDATE_10Sec); // 10 sec update rate

  delay(1000);
}

void loop_gps() // run over and over again
{
  while (GPSSerial.available() > 0)
  {
    GPSModule.encode(GPSSerial.read());
  }

  Serial.print("LAT=");
  Serial.println(GPSModule.location.lat(), 6);
  Serial.print("LONG=");
  Serial.println(GPSModule.location.lng(), 6);
  Serial.print("ALT=");
  Serial.println(GPSModule.altitude.meters());
}