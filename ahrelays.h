#ifndef ARMOIRE_HORTI_RELAYS_H
#define ARMOIRE_HORTI_RELAYS_H

#include <Arduino.h>
#include <ArduinoJson.h>
#include "config.h"

struct Relay
{
    String name;
    int pin;
    bool value;
};

class AHRelays
{
public:
    void setup();
    void loop(const long time);
    void setRelay(String relayName, bool value);
    bool toggleAll();
    String getRelaysValuesJSON();

private:
    Relay relays[AH_RELAYS_COUNT] = {
        {"led-1", AH_RELAY_1_PIN, true},
        {"led-2", AH_RELAY_2_PIN, true},
        {"led-3", AH_RELAY_3_PIN, true},
        {"heat", AH_RELAY_HEAT_PIN, true},
    };

    bool mainOnOff = true;
    void update();
};

#endif