#ifndef ARMOIRE_HORTI_WEBSERVER_LIB_H
#define ARMOIRE_HORTI_WEBSERVER_LIB_H

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>
#include "ahsensors.h"

class AHWebServer
{
public:
    void setup();
    void loop();
    String getStatusText1();
    String getStatusText2();

    String (*onSensorsRequest)() = []()
    { return String("{\"error\":\"onSensorsRequest is undefined\"}"); };

    // String (*onRelaysRequest)() = []()
    // { return String("{\"error\":\"onRelaysRequest is undefined\"}"); };

    void (*onRelayChangeRequest)(String name, bool on) = [](String name, bool on) {};

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
};

#endif