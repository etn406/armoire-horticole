#ifndef ARMOIRE_HORTI_RELAYS_H
#define ARMOIRE_HORTI_RELAYS_H

#include <Arduino.h>
#include <ArduinoJson.h>
#include "config.h"

/**
 * Represents a relay
 */
struct Relay
{
    String name;
    int pin;
    bool value;
};

/**
 * Handle the relays (to turn on/off lights and the heating mat).
 */
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
        {"relay-0", AH_RELAY_1_PIN, true},
        {"relay-1", AH_RELAY_2_PIN, true},
        {"relay-2", AH_RELAY_3_PIN, true},
        {"relay-3", AH_RELAY_4_PIN, true},
    };

    bool mainOnOff = true;
    void update();
};

#endif