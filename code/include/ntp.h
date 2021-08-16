#include "time.h"

#define ntp_server "uk.pool.ntp.org"
#define gmtOffset_sec 0
#define daylightOffset_sec 3600

void loop_ntp();
void setup_ntp();
void printLocalTime();
