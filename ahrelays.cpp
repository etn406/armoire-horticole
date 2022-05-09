#include "ahrelays.h"

void AHRelays::setup()
{
    for (int i = 0; i < AH_RELAYS_COUNT; i++)
    {
        const Relay relay = relays[i];
        pinMode(relay.pin, OUTPUT);
        digitalWrite(relay.pin, relay.value ? LOW : HIGH);
    }
}

void AHRelays::loop(const long time)
{
}

bool AHRelays::toggleAll()
{
    mainOnOff = !mainOnOff;
    update();
    return mainOnOff;
}

void AHRelays::setRelay(String name, bool value)
{
    if (name.equals("main"))
    {
        mainOnOff = value;

        if (mainOnOff)
        {
            // Si on allume "main" et que tous les autres interrupteurs sont OFF,
            // alors on allume tout
            bool allOff = true;
            for (int i = 0; i < AH_RELAYS_COUNT; i++)
            {
                allOff = allOff && (relays[i].value == false);
            }

            if (allOff)
            {
                for (int i = 0; i < AH_RELAYS_COUNT; i++)
                {
                    relays[i].value = true;
                }
            }
        }
    }
    else
    {
        for (int i = 0; i < AH_RELAYS_COUNT; i++)
        {
            if (relays[i].name.equals(name))
            {
                relays[i].value = value;
            }
        }
    }

    update();
}

void AHRelays::update()
{
    if (mainOnOff)
    {
        for (int i = 0; i < AH_RELAYS_COUNT; i++)
        {
            const Relay relay = relays[i];
            digitalWrite(relay.pin, relay.value ? LOW : HIGH);
        }
        // digitalWrite(AH_RELAY_1_PIN, relays[0].value ? LOW: HIGH);
        // digitalWrite(AH_RELAY_2_PIN, relays[1].value ? LOW: HIGH);
        // digitalWrite(AH_RELAY_3_PIN, relays[2].value ? LOW: HIGH);
        // digitalWrite(AH_RELAY_HEAT_PIN, relays[3].value ? LOW: HIGH);
    }
    else
    {
        // for (int i = 0; i < AH_RELAYS_COUNT; i++)
        // {
        //     const Relay relay = relays[i];
        //     digitalWrite(relay.pin, HIGH);
        // }

        digitalWrite(AH_RELAY_1_PIN, HIGH);
        digitalWrite(AH_RELAY_2_PIN, HIGH);
        digitalWrite(AH_RELAY_3_PIN, HIGH);
        digitalWrite(AH_RELAY_4_PIN, HIGH);
    }
}

String AHRelays::getRelaysValuesJSON()
{
    String responseJSONString = "";
    DynamicJsonDocument responseJSON(350);

    const size_t CAPACITY = JSON_OBJECT_SIZE(10);

    for (int i = 0; i < AH_RELAYS_COUNT; i++)
    {
        const Relay relay = relays[i];

        StaticJsonDocument<CAPACITY> doc;
        JsonObject obj = doc.to<JsonObject>();

        obj["name"] = relay.name;
        obj["value"] = relay.value;

        responseJSON.add(obj);
    }

    StaticJsonDocument<CAPACITY> doc;
    JsonObject obj = doc.to<JsonObject>();

    obj["name"] = "main";
    obj["value"] = mainOnOff;

    responseJSON.add(obj);

    serializeJson(responseJSON, responseJSONString);
    return responseJSONString;
}
