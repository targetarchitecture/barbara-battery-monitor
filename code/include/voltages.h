#include <Streaming.h>    
#include <INA219_WE.h>

void setup_voltages();
void loop_voltages();

extern volatile float  leisureVoltage;
extern volatile float  carVoltage;
extern volatile float  solarVoltage;

extern SemaphoreHandle_t i2cSemaphore;
extern SemaphoreHandle_t uartSemaphore;