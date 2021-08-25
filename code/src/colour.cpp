#include "colour.h"

Melopero_APDS9960 device;

void setup_colour()
{
    Serial.println(device.init());  // Initialize the comunication library
    Serial.println(device.reset()); // Reset all interrupt settings and power off the device

    Serial.println(device.enableAlsEngine());          // enable the color/ALS engine
    Serial.println(device.setAlsIntegrationTime(450)); // set the color engine integration time
    Serial.println(device.updateSaturation());         // updates the saturation value, stored in device.alsSaturation

    // The device.alsSaturation variable represents the maximum value for the rgbc variables.
    // If you want a normalized value of the rgbc variables you have to divide them by the
    // alsSaturation.
    // device.red/green/blue/clear <-> Raw color value for red/green/blue/clear
    // device.alsSaturation <-> saturation value for rgbc (maximum value they can assume)
    // float norm_red = (float) device.red / (float) device.alsSaturation <-> normalized red value in range [0 - 1]

    Serial.println(device.wakeUp()); // wake up the device
}

void loop_colour()
{

    device.updateColorData(); // update the values stored in device.red/green/blue/clear

    Serial.println("Raw color data:");
    printColor(device.red, device.green, device.blue, device.clear); // print raw values
}

void printColor(uint16_t r, uint16_t g, uint16_t b, uint16_t c)
{
    Serial.print("R: ");
    Serial.print(r);
    Serial.print(" G: ");
    Serial.print(g);
    Serial.print(" B: ");
    Serial.print(b);
    Serial.print(" C: ");
    Serial.println(c);
}
