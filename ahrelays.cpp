#include "ahrelays.h"

void AHRelays::setup()
{
    for (auto &relay : relays)
    {
        pinMode(relay.pin, OUTPUT);
        digitalWrite(relay.pin, relay.value);
    }
}

void AHRelays::loop(const long time)
{
    // // Allumer la LED pendant une demi seconde à chaque update
    // if (currentTime > lastUpdateTime && currentTime < lastUpdateTime + 500)
    // {
    //     digitalWrite(RELAY1, LOW);
    //     digitalWrite(RELAY2, HIGH);
    //     digitalWrite(RELAY3, LOW);
    //     digitalWrite(RELAY4, HIGH);
    // }
    // else
    // {
    //     digitalWrite(RELAY1, HIGH);
    //     digitalWrite(RELAY2, LOW);
    //     digitalWrite(RELAY3, HIGH);
    //     digitalWrite(RELAY4, LOW);
    // }
}

void AHRelays::toggleAll()
{
    mainOnOff = !mainOnOff;
    update();
}

void AHRelays::setRelay(String name, bool on)
{
    for (auto &relay : relays)
    {
        if (relay.name == name)
        {
            relay.value = on ? HIGH : LOW;
        }
    }
}

void AHRelays::update()
{
    if (mainOnOff)
    {
        for (auto &relay : relays)
        {
            digitalWrite(relay.pin, relay.value);
        }
    }
    else
    {
        for (auto &relay : relays)
        {
            digitalWrite(relay.pin, LOW);
        }
    }
}