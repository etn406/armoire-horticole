#ifndef ARMOIRE_HORTI_SENSORS_STATUS_H
#define ARMOIRE_HORTI_SENSORS_STATUS_H

/**
 * Represent the current status of the cabinet,
 * displayed on the screen and/or be sent to a remote web interface.
 */
struct AHData
{
    /**
     * Current wifi status.
     */
    String wifiStatusText = "Status unknown";

    /**
     * Current average temperature (C°)
     */
    float temperature = 0.0;

    /**
     * Current average humidity %
     */
    float humidity = 0.0;

    /**
     * Indicates if each sensor is well connected.
     */
    bool connected[3] = {false, false, false};
};

#endif