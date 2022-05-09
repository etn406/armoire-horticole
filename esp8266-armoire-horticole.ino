#include <Arduino.h>
#include <DHT.h>
#include "ahwebserver.h"
#include "ahinputs.h"
#include "ahdisplay.h"
#include "ahsensors.h"
#include "ahrelays.h"
#include "ahdata.h"

unsigned long currentTime = 0;
unsigned long lastUpdateTime = 0;

bool connected = false;
String currentIP = "";

AHRelays ahRelays = AHRelays();
AHSensors ahSensors = AHSensors();
AHWebServer ahWebServer = AHWebServer();
AHInputs ahInputs = AHInputs();
AHDisplay ahDisplay = AHDisplay();
AHData data;

void setup()
{
    ahSensors.setup();

    // Lorsque les capteurs se mettent à jour
    ahSensors.data = &data;
    ahWebServer.data = &data;
    ahDisplay.data = &data;

    ahRelays.setup();
    ahInputs.setup();
    ahInputs.onButtonOnOffPressed = []()
    {
        ahRelays.toggleAll();
        ahDisplay.displayWifiInformations();
    };

    ahDisplay.setup();
    ahWebServer.setup();

    // Lorsqu'un client web demande les valeurs captées
    ahWebServer.onSensorsRequest = []()
    { return ahSensors.getSensorsValuesJSON(); };

    // Lorsqu'un client web demande les status des relays
    ahWebServer.onRelaysValuesRequest = []()
    { return ahRelays.getRelaysValuesJSON(); };

    // Lorsqu'un client web demande les valeurs captées
    ahWebServer.onRelayChangeRequest = [](String name, bool on)
    {
        ahRelays.setRelay(name, on);
        return ahRelays.getRelaysValuesJSON();
    };
}

void loop()
{
    currentTime = millis();

    ahWebServer.loop();
    ahSensors.loop(currentTime);
    ahInputs.loop();
    ahRelays.loop(currentTime);
    ahDisplay.loop(currentTime);

    delay(50);
}
