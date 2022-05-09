#ifndef ARMOIRE_HORTI_DISPLAY_LIB_H
#define ARMOIRE_HORTI_DISPLAY_LIB_H

#include <Arduino.h>
#include <Adafruit_SSD1306.h>
#include <Fonts/FreeMonoBold18pt7b.h>
#include <Fonts/FreeMono9pt7b.h>
#include "./images/images.h"
#include "./images/cat-tail.h"
#include "ahdata.h"
#include "config.h"

#define AH_SCREEN_WIDTH 128
#define AH_SCREEN_HEIGHT 64
#define AH_SCREEN_ADDRESS 0x3C
#define AH_OLED_RESET -1

// Intervalle de rafraichissement de l'écran en millisecondes
#define AH_DISPLAY_REFRESH_INTERVAL 500

class AHDisplay
{
public:
    AHData *data;
    String wifiStatus = "";
    bool mainOnOff = true;

    void setup();
    void loop(const long time);
    void displayWifiInformations();

private:
    int catTailPosition[2] = {57, 9};

    int sensorsPositions[6] = {
        14, 21,
        31, 21,
        48, 21};

    long lastLoopUpdate = 0;
    long lastShowIntroductionTime = 0;

    Adafruit_SSD1306 display = Adafruit_SSD1306(
        AH_SCREEN_WIDTH,
        AH_SCREEN_HEIGHT,
        &Wire,
        AH_OLED_RESET);

    void refreshDisplay(const long time);
    void drawClock(const long time);
    void drawSensorsStatus(const long time);
    void drawTemperatureAndHumidity(const long time);
    void drawCat(const long time);
    void drawIntroductionScreen(const long time);
};

#endif