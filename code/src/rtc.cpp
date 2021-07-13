#include <Arduino.h>
#include "rtc.h"

const char *monthName[12] = {
    "Jan", "Feb", "Mar", "Apr", "May", "Jun",
    "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};

tmElements_t tm;

bool parseRTC = false;
bool configRTC = false;

void setup_rtc()
{

  if (RTC.read(tm) == false)
  {
    configRTC = true;

    if (RTC.chipPresent())
    {
      Serial.println("The DS1307 is stopped.  Please run the SetTime");
      Serial.println("example to initialize the time and begin running.");
      Serial.println();

      // first parameter: Time zone in floating point (for India); second parameter: 1 for European summer time; 2 for US daylight saving time; 0 for no DST adjustment; (contributed by viewwer, not tested by me)
      strDateTime DT = NTPch.getNTPtime(0, 1);

      Serial.println(DT.epochTime);

      // check dateTime.valid before using the returned time
      // Use "setSendInterval" or "setRecvTimeout" if required

      Serial.println(DT.valid);

      if (DT.valid)
      {
        Serial.println("DT.valid");

        //   dateTime = DT;

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
    else
    {
      Serial.println("DS1307 read error!  Please check the circuitry.");
      Serial.println();
    }
  }
  else
  {
    Serial.println("DS1307 read correctly");

    Serial.print("Ok, Time = ");
    print2digits(tm.Hour);
    Serial.write(':');
    print2digits(tm.Minute);
    Serial.write(':');
    print2digits(tm.Second);
    Serial.print(", Date (D/M/Y) = ");
    Serial.print(tm.Day);
    Serial.write('/');
    Serial.print(tm.Month);
    Serial.write('/');
    Serial.print(tmYearToCalendar(tm.Year));
    Serial.println();
  }
}

//   // get the date and time the compiler was run
//   if (getDate(__DATE__) && getTime(__TIME__)) {
//     parse = true;
//     // and configure the RTC with this info
//     if (RTC.write(tm)) {
//       config = true;
//     }
//   }

void print2digits(int number)
{
  if (number >= 0 && number < 10)
  {
    Serial.write('0');
  }
  Serial.print(number);
}

void loop_rtc()
{
  tmElements_t tm;

  if (RTC.read(tm))
  {
    Serial.print("Ok, Time = ");
    print2digits(tm.Hour);
    Serial.write(':');
    print2digits(tm.Minute);
    Serial.write(':');
    print2digits(tm.Second);
    Serial.print(", Date (D/M/Y) = ");
    Serial.print(tm.Day);
    Serial.write('/');
    Serial.print(tm.Month);
    Serial.write('/');
    Serial.print(tmYearToCalendar(tm.Year));
    Serial.println();
  }
  else
  {
    if (RTC.chipPresent())
    {
      Serial.println("The DS1307 is stopped.  Please run the SetTime");
      Serial.println("example to initialize the time and begin running.");
      Serial.println();
    }
    else
    {
      Serial.println("DS1307 read error!  Please check the circuitry.");
      Serial.println();
    }
    delay(9000);
  }
  delay(1000);
}