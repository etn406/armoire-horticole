#ifndef ARMOIRE_HORTI_SENSORS_LIB_H
#define ARMOIRE_HORTI_SENSORS_LIB_H

#include <Arduino.h>
#include <DHT.h>
#include <ArduinoJson.h>
#include "config.h"
#include "ahdata.h"

/**
 * Handle up to 3 temperature and humidity sensors.
 */
class AHSensors
{
public:
    void setup();
    void loop(const long time);
    float getAverageTemperature();
    float getAverageHumidity();
    bool isSensorConnected(int id);
    String getSensorsValuesJSON();
    AHData *data;

private:
    long lastUpdateTime = 0;
    void updateSensorsValues();

    DHT dht[AH_SENSORS_COUNT] = {
        {AH_DHT1_PIN, DHT22},
        {AH_DHT2_PIN, DHT22},
        {AH_DHT3_PIN, DHT22},
    };

    float humidity[AH_SENSORS_COUNT];
    float temperature[AH_SENSORS_COUNT];
};

#endif