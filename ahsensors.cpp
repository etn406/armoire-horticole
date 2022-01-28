#include "ahsensors.h"

void AHSensors::setup()
{
    for (auto &sensor : dht)
    {
        sensor.begin();
    }

    updateSensorsValues();
}

void AHSensors::loop(const long time)
{
    if (time > lastUpdateTime + AH_SENSORS_REFRESH_INTERVAL)
    {
        lastUpdateTime = time;

        updateSensorsValues();

        onUpdate(
            getAverageTemperature(),
            getAverageHumidity());
    }
}

/**
 * @brief température moyenne
 * 
 * @return float 
 */
float AHSensors::getAverageTemperature()
{
    float total = 0;

    for (int i = 0; i < AH_SENSORS_COUNT; i++)
    {
        total += temperature[i];
    }

    return total / float(AH_SENSORS_COUNT);
}

/**
 * @brief humidité moyenne
 * 
 * @return float 
 */
float AHSensors::getAverageHumidity()
{
    float total = 0;

    for (int i = 0; i < AH_SENSORS_COUNT; i++)
    {
        total += humidity[i];
    }

    return total / float(AH_SENSORS_COUNT);
}

String AHSensors::getSensorsValuesJSON()
{
    String responseJSONString = "";
    DynamicJsonDocument responseJSON(192);

    const size_t CAPACITY = JSON_OBJECT_SIZE(AH_SENSORS_COUNT);

    for (int i = 0; i < AH_SENSORS_COUNT; i++)
    {
        StaticJsonDocument<CAPACITY> doc;
        JsonObject obj = doc.to<JsonObject>();

        obj["id"] = i;
        obj["humidity"] = humidity[i];
        obj["temperature"] = temperature[i];

        responseJSON.add(obj);
    }

    serializeJson(responseJSON, responseJSONString);
    return responseJSONString;
}

void AHSensors::updateSensorsValues()
{
    for (int i = 0; i < AH_SENSORS_COUNT; i++)
    {
        temperature[i] = dht[i].readTemperature();
        humidity[i] = dht[i].readHumidity();
    }
}
