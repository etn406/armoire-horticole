#ifndef ARMOIRE_HORTI_DISPLAY_LIB_H
#define ARMOIRE_HORTI_DISPLAY_LIB_H

#include <Arduino.h>
#include <Adafruit_SSD1306.h>
#include <Fonts/FreeMonoBold18pt7b.h>
#include <Fonts/Tiny3x3a2pt7b.h>
#include "./InterfaceBMP.h"
#include "config.h"

#define AH_SCREEN_WIDTH 128
#define AH_SCREEN_HEIGHT 64
#define AH_SCREEN_ADDRESS 0x3C
#define AH_OLED_RESET -1

// Intervalle de rafraichissement de l'écran en millisecondes
#define AH_DISPLAY_REFRESH_INTERVAL 1000

class AHDisplay
{
public:
    float temperature = 0.0;
    float humidity = 0.0;
    String wifiStatus = "";

    void setup();
    void loop(const long time);

private:
    long lastLoopUpdate = 0;
    void refreshDisplay(const long time);

    Adafruit_SSD1306 display = Adafruit_SSD1306(
        AH_SCREEN_WIDTH,
        AH_SCREEN_HEIGHT,
        &Wire,
        AH_OLED_RESET);
};

#endif