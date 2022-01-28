#ifndef ARMOIRE_HORTI_RELAYS_H
#define ARMOIRE_HORTI_RELAYS_H

#include <Arduino.h>
#include "config.h"

struct Relay
{
    String name;
    int pin;
    int value;
};

class AHRelays
{
public:
    void setup();
    void loop(const long time);
    void toggleAll();
    void setRelay(String relayName, bool on);

private:
    Relay relays[AH_RELAYS_COUNT] = {
        {"led-1", AH_RELAY_1_PIN, LOW},
        {"led-2", AH_RELAY_2_PIN, LOW},
        {"led-3", AH_RELAY_3_PIN, LOW},
        {"heat", AH_RELAY_HEAT_PIN, LOW},
    };

    bool mainOnOff = true;
    void update();
};

#endif