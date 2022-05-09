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

        data->temperature = getAverageTemperature();
        data->humidity = getAverageHumidity();
        data->connected[0] = isSensorConnected(0);
        data->connected[1] = isSensorConnected(1);
        data->connected[2] = isSensorConnected(2);
    }
}

/**
 * @brief Température moyenne
 */
float AHSensors::getAverageTemperature()
{
    float total = 0;
    int count = 0;

    for (int i = 0; i < AH_SENSORS_COUNT; i++)
    {
        if (isSensorConnected(i))
        {
            total += temperature[i];
            count++;
        }
    }

    if (count > 0)
        return total / float(count);
    else
        return 0;
}

/**
 * @brief Humidité moyenne
 */
float AHSensors::getAverageHumidity()
{
    float total = 0;
    int count = 0;

    for (int i = 0; i < AH_SENSORS_COUNT; i++)
    {
        if (isSensorConnected(i))
        {
            total += humidity[i];
            count++;
        }
    }

    if (count > 0)
        return total / float(count);
    else
        return 0;
}

/**
 * @brief Vérifie qu'un capteur est connecté
 */
bool AHSensors::isSensorConnected(int id)
{
    if (id < 0 || id >= AH_SENSORS_COUNT)
    {
        return false;
    }
    else
    {
        const bool temperatureIsOK = !isnan(temperature[id]) && temperature[id] > -100 && temperature[id] <= 100;
        const bool humidityIsOK = !isnan(humidity[id]) && humidity[id] >= 0 && humidity[id] <= 100;

        return temperatureIsOK && humidityIsOK;
    }
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
