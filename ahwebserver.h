#ifndef ARMOIRE_HORTI_WEBSERVER_LIB_H
#define ARMOIRE_HORTI_WEBSERVER_LIB_H

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>
#include "ahsensors.h"

/**
 * The webserver handles two things:
 * - the wifi portal to setup the wifi connection at first.
 * - if the arduino is connected to a router, it serves a server with an API and a basic HTML home.
 */
class AHWebServer
{
public:
    AHData *data;

    void setup();
    void loop();
    String getStatusAsText();

    String (*onSensorsRequest)() = []()
    { return String("{\"error\":\"onSensorsRequest is undefined\"}"); };

    String (*onRelaysValuesRequest)() = []()
    { return String("{\"error\":\"onRelaysValuesRequest is undefined\"}"); };

    String (*onRelayChangeRequest)(String name, bool value) = [](String name, bool value)
    { return String("{\"error\":\"onRelayChangeRequest is undefined\"}"); };

private:
    AHSensors ahSensors;
    WiFiManager wifiManager;
    std::unique_ptr<ESP8266WebServer> server;
    String getArgValue(String name);
    String getRequestDescription();
    String currentIP = "";
    String status2 = "";
    wl_status_t lastWiFiStatus = WL_DISCONNECTED;

    void handleRoot();
    void updateStatus();
    void updateData();
};

#endif