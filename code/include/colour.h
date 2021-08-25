#include "Melopero_APDS9960.h"

extern volatile uint16_t colour[4];

extern SemaphoreHandle_t i2cSemaphore;

void setup_colour();
void loop_colour();

