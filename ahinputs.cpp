#include "ahinputs.h"

void AHInputs::setup()
{
    pinMode(AH_BUTTON_ONOFF, INPUT_PULLUP);
}

void AHInputs::loop()
{
    const int onOffStatus = digitalRead(AH_BUTTON_ONOFF);

    if (lastOnOffStatus != onOffStatus)
    {
        lastOnOffStatus = onOffStatus;

        if (onOffStatus == HIGH)
        {
            onButtonOnOffPressed();
        }
    }
}