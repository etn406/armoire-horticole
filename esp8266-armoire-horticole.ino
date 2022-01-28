#include <Arduino.h>
#include <DHT.h>
#include "ahwebserver.h"
#include "ahinputs.h"
#include "ahdisplay.h"
#include "ahsensors.h"
#include "ahrelays.h"

unsigned long currentTime = 0;
unsigned long lastUpdateTime = 0;

bool connected = false;
String currentIP = "";

AHRelays ahRelays = AHRelays();
AHSensors ahSensors = AHSensors();
AHWebServer ahWebServer = AHWebServer();
AHInputs ahInputs = AHInputs();
AHDisplay ahDisplay = AHDisplay();

void setup()
{
    ahSensors.setup();

    // Lorsque les cateurs se mettent à jour
    ahSensors.onUpdate = [](float temperature, float humidity)
    {
        // Les propriété destinées à être affichées sont mises à jour
        ahDisplay.temperature = temperature;
        ahDisplay.humidity = humidity;
    };

    ahRelays.setup();
    ahInputs.setup();
    ahInputs.onButtonOnOffPressed = []()
    { ahRelays.toggleAll(); };

    ahDisplay.setup();
    ahWebServer.setup();

    // Lorsqu'un client web demande les valeurs captées
    ahWebServer.onSensorsRequest = []()
    { return ahSensors.getSensorsValuesJSON(); };

    // Lorsqu'un client web demande les valeurs captées
    ahWebServer.onRelayChangeRequest = [](String name, bool on)
    { return ahRelays.setRelay(name, on); };
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
