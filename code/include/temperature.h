#include <Adafruit_MCP9808.h>
#include <Streaming.h>    

void setup_temperature();
void loop_temperature();

extern volatile float temperature;

extern SemaphoreHandle_t i2cSemaphore;
