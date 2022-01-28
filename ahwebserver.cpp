#include "ahwebserver.h"
#include "config.h"

String AHWebServer::getRequestDescription()
{
    String description = "URI: " + server->uri() + "\n";
    description += "Method: " + String((server->method() == HTTP_GET) ? "GET" : "POST") + "\n";
    description += "Arguments: " + String(server->args()) + "\n";

    for (int i = 0; i < server->args(); i++)
    {
        description += "\t" + server->argName(i) + ":\t" + server->arg(i) + "\n";
    }

    return description;
}

void AHWebServer::handleRoot()
{
    server->send(200, "text/html",
                 "<!DOCTYPE html>"
                 "<html>"
                 " <head>"
                 "  <meta charset=\"utf-8\">"
                 "  <meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">"
                 "  <title>Armoire horticole</title>"
                 "  <link rel=\"stylesheet\" href=\"https://cdn.jsdelivr.net/npm/bootswatch@4.5.2/dist/sketchy/bootstrap.min.css\">"
                 "  <script src=\"https://cdn.jsdelivr.net/npm/chart.js\"></script>"
                 "  <style>"
                 "   body {display: flex; flex-direction: column; text-align: center;}"
                 "   .card {margin: 20px;}"
                 "   .card-body {display: flex; flex-direction: column; text-align: center;}"
                 "   button.btn:not(:last-child) {margin-bottom: 20px;}"
                 "  </style>"
                 "  <script>"

                 "   function readStoredData() {"
                 "    return JSON.parse(localStorage.getItem('ahData') || '{data:[]}');"
                 "   }"

                 "   function storeData(data) {"
                 "    localStorage.setItem('ahData', JSON.stringify(data, null, '\\t'))"
                 "   }"

                 "   function getSensorValues() {"
                 "    fetch('/get-sensors-values').then((res) => res.text()).then((json) => {"
                 "     const newData = JSON.parse(json);"
                 "     newData.date = new Date;"
                 "     const ahData = readStoredData()"
                 "     ahData.data.push(newData);"
                 "     storeData(ahData)"
                 "    })"
                 "   };"

                 "  </script>"
                 " </head>"
                 " <body>"
                 "  <div class=\"card border-primary mb-3\">"
                 "   <div class=\"card-header\">Armoire horticole</div>"
                 "   <div class=\"card-body\">"
                 "    <button onclick=\"turnRelay(1, 0)\" class=\"btn btn-lg btn-secondary\">LED OFF</button>"
                 "    <button onclick=\"turnRelay(1, 1)\" class=\"btn btn-lg btn-success\">LED ON</button>"
                 "    <button onclick=\"turnRelay(2, 0)\" class=\"btn btn-lg btn-secondary\">HEAT OFF</button>"
                 "    <button onclick=\"turnRelay(2, 1)\" class=\"btn btn-lg btn-success\">HEAT ON</button>"
                 "   </div>"
                 "  </div>"
                 " </body>"
                 "</html>");
}

void AHWebServer::setup()
{
    // Serial.println("Hello hello, tryin' to connect, don't mind me");

    WiFi.mode(WIFI_STA);
    bool res = wifiManager.autoConnect(AH_WIFI_PORTAL_SSID, AH_WIFI_PORTAL_PASS);

    if (!res)
    {
        // Serial.println("Failed to connect");
        ESP.restart();
    }
    else
    {
        //if you get here you have connected to the WiFi
        // Serial.println("Connected to WiFi !");

        server.reset(new ESP8266WebServer(WiFi.localIP(), 80));
        server->enableCORS(true);

        server->on("/is-armoire-horticole", [&]()
                   { server->send(200, "text/plain", "yes"); });

        server->on("/home", [&]()
                   { handleRoot(); });

        server->on("/get-sensors-values", [&]()
                   { server->send(200, "application/json", onSensorsRequest()); });

        // server->on("/get-relays-values", [&]()
        //            { server->send(200, "application/json", onRelaysRequest()); });

        server->onNotFound([&]()
                           { server->send(404, "text/plain", "File Not Found\n\n" + getRequestDescription()); });

        server->begin();

        // Serial.println("HTTP server started");
        // Serial.println(WiFi.localIP());
    }
}

String AHWebServer::getArgValue(String name)
{
    for (int i = 0; i < server->args(); i++)
    {
        if (server->argName(i).equals(name))
        {
            return server->arg(i);
        }
    }

    return "";
}

String AHWebServer::getStatusText1()
{
    if (lastWiFiStatus != WL_CONNECTED)
    {
        if (lastWiFiStatus == WL_CONNECTION_LOST)
        {
            return "Connection lost";
        }
        else if (lastWiFiStatus == WL_DISCONNECTED)
        {
            return "Disconnected";
        }
        else if (lastWiFiStatus == WL_IDLE_STATUS)
        {
            return "Idle";
        }
        else
        {
            return "???";
        }
    }
    else
    {
        return currentIP;
    }
}

String AHWebServer::getStatusText2()
{
}

void AHWebServer::updateStatus()
{
    wl_status_t wifiStatus = WiFi.status();

    if (lastWiFiStatus != wifiStatus)
    {
        lastWiFiStatus = wifiStatus;

        if (wifiStatus == WL_CONNECTED)
        {
            currentIP = WiFi.localIP().toString();
        }
    }
}

void AHWebServer::loop()
{
    updateStatus();
    server->handleClient();
}
