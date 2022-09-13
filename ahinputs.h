#ifndef ARMOIRE_HORTI_INPUTS_LIB_H
#define ARMOIRE_HORTI_INPUTS_LIB_H

#include <Arduino.h>
#include "config.h"

/**
 * Detects when the main button is pressed.
 */
class AHInputs
{
public:
    void setup();
    void loop();
    void (*onButtonOnOffPressed)() = []() {};

private:
    int lastOnOffStatus = LOW;
};

#endif