#include <Arduino.h>
#include "ntp.h"

NTPtime NTPch("uk.pool.ntp.org");

strDateTime dateTime;

void loop_ntp()
{

  // first parameter: Time zone in floating point (for India); second parameter: 1 for European summer time; 2 for US daylight saving time; 0 for no DST adjustment; (contributed by viewwer, not tested by me)
  strDateTime DT = NTPch.getNTPtime(0, 1);

  // check dateTime.valid before using the returned time
  // Use "setSendInterval" or "setRecvTimeout" if required
  if (DT.valid)
  {
    dateTime = DT;

    NTPch.printDateTime(DT);

    // byte actualHour = dateTime.hour;
    // byte actualMinute = dateTime.minute;
    // byte actualsecond = dateTime.second;
    // int actualyear = dateTime.year;
    // byte actualMonth = dateTime.month;
    // byte actualday =dateTime.day;
    // byte actualdayofWeek = dateTime.dayofWeek;


        tmElements_t tm;
        tm.Day = DT.day;
        tm.Hour = DT.hour;
        tm.Minute = DT.minute;
        tm.Month = DT.month;
        tm.Second = DT.second;
        tm.Wday = DT.dayofWeek;
        tm.Year = DT.year;

   Serial.println("The DS1307 writing time");

        RTC.write(tm);

           Serial.println("Completed writing time");

  }
}