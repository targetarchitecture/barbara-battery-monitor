#include "gpsModule.h"

TinyGPSPlus GPSModule;
//HardwareSerial SerialGPS(1);

//volatile TinyGPSLocation location;

void setup_gps()
{
  //GPSSerial.begin(9600, SERIAL_8N1, 16, 17);

  // 9600 NMEA is the default baud rate for Adafruit MTK GPS's- some use 4800
  GPSSerial.begin(9600);

//turn on RMC (recommended minimum) and GGA (fix data) including altitude
  GPSSerial.write(PMTK_SET_NMEA_OUTPUT_RMCGGA);
  GPSSerial.flush();

// #define PMTK_SET_NMEA_UPDATE_10Sec "$PMTK220,10000*2F"
//   GPSSerial.write(PMTK_SET_NMEA_UPDATE_10Sec); // 10 sec update rate
//   GPSSerial.flush();

   delay(1000);

  // loop_gps();

  // delay(1000);
}

void loop_gps() // run over and over again
{
  while (GPSSerial.available() > 0)
  {
    GPSModule.encode(GPSSerial.read());
  }

//   if (GPSModule.location.isValid() == true && GPSModule.location.isUpdated() == true )
//   {
// location = GPSModule.location;


//     Serial.print("LAT=");
//     Serial.println(GPSModule.location.lat(), 6);
//     Serial.print("LONG=");
//     Serial.println(GPSModule.location.lng(), 6);
//     Serial.print("ALT=");
//     Serial.println(GPSModule.altitude.meters());

//     latitude = GPSModule.location.lat();
//     longitude = GPSModule.location.lng();
//     elevation = GPSModule.altitude.meters();
//     locationAge = GPSModule.location.age();
//   }

  //Serial.print("GPSModule.location.isUpdated=");
  //Serial.println(GPSModule.location.isUpdated());

  //Serial.print("GPSModule.location.age=");
  //Serial.println(GPSModule.location.age());

 // if (GPSModule.location.isValid() == true)
  //{
    // if ((GPSModule.location.age() - millis()) > 1000 * 60 * 2)
    // {
    //   latitude = 0;
    //   longitude = 0;
    //   elevation = 0;
    // }
    // else
    // {


    //}
  //}
}