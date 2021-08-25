#include "colour.h"

Melopero_APDS9960 device;

void setup_colour()
{
    //wait for the i2c semaphore flag to become available
    xSemaphoreTake(i2cSemaphore, portMAX_DELAY);

    device.init();  // Initialize the comunication library
    device.reset(); // Reset all interrupt settings and power off the device

    device.enableAlsEngine();          // enable the color/ALS engine
    device.setAlsIntegrationTime(450); // set the color engine integration time
    device.updateSaturation();         // updates the saturation value, stored in device.alsSaturation

    device.wakeUp(); // wake up the device

    //give back the i2c flag for the next task
    xSemaphoreGive(i2cSemaphore);
}

void loop_colour()
{
    //wait for the i2c semaphore flag to become available
    xSemaphoreTake(i2cSemaphore, portMAX_DELAY);

    device.updateColorData(); // update the values stored in device.red/green/blue/clear

    //give back the i2c flag for the next task
    xSemaphoreGive(i2cSemaphore);

    colour[0] = device.red;
    colour[1] = device.green;
    colour[2] = device.blue;
    colour[3] = device.clear;
}
