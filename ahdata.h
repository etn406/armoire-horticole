#ifndef ARMOIRE_HORTI_SENSORS_STATUS_H
#define ARMOIRE_HORTI_SENSORS_STATUS_H

struct AHData
{
    String wifiStatusText = "Status unknown";
    float temperature = 0.0;
    float humidity = 0.0;
    bool connected[3] = {false, false, false};
};

#endif