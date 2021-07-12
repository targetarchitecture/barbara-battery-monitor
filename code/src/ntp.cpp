#include <Arduino.h>
#include "ntp.h"

NTPtime NTPch("uk.pool.ntp.org");   

strDateTime dateTime;

void loop_ntp() {

  // first parameter: Time zone in floating point (for India); second parameter: 1 for European summer time; 2 for US daylight saving time; 0 for no DST adjustment; (contributed by viewwer, not tested by me)
  dateTime = NTPch.getNTPtime(0, 1);

  // check dateTime.valid before using the returned time
  // Use "setSendInterval" or "setRecvTimeout" if required
  if(dateTime.valid){
    NTPch.printDateTime(dateTime);

    // byte actualHour = dateTime.hour;
    // byte actualMinute = dateTime.minute;
    // byte actualsecond = dateTime.second;
    // int actualyear = dateTime.year;
    // byte actualMonth = dateTime.month;
    // byte actualday =dateTime.day;
    // byte actualdayofWeek = dateTime.dayofWeek;
  }
}