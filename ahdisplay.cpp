#include "ahdisplay.h"

void AHDisplay::setup()
{
    // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
    if (!display.begin(SSD1306_SWITCHCAPVCC, AH_SCREEN_ADDRESS))
    {
        Serial.println(F("SSD1306 allocation failed"));
        digitalWrite(LED_BUILTIN, HIGH);
        for (;;)
            ; // Don't proceed, loop forever
    }
    else
    {
        display.clearDisplay();
    }
}

void AHDisplay::loop(const long time)
{
    if (time > lastLoopUpdate + AH_DISPLAY_REFRESH_INTERVAL)
    {
        lastLoopUpdate = time;
        refreshDisplay(time);
    }
}

void AHDisplay::refreshDisplay(const long time)
{
    display.clearDisplay();
    display.setTextColor(SSD1306_WHITE);

    if (time > lastShowIntroductionTime + AH_DISPLAY_TIME_OF_WIFI_INFOS)
    {
        display.drawBitmap(0, 0, INTERFACE_BITMAP, display.width(), display.height(), 1);

        drawCat(time);
        drawSensorsStatus(time);
        drawTemperatureAndHumidity(time);
    }
    else
    {
        drawIntroductionScreen(time);
    }

    display.display();
}

void AHDisplay::displayWifiInformations()
{
    lastShowIntroductionTime = lastLoopUpdate;
}

void AHDisplay::drawIntroductionScreen(const long time)
{
    int x = 1, y = 1;

    int16_t x1, y1;
    uint16_t w, h;

    const String ssid = AH_WIFI_PORTAL_SSID;
    const String password = AH_WIFI_PORTAL_PASS;

    display.setFont();
    display.getTextBounds(ssid, 0, 0, &x1, &y1, &w, &h);
    display.setCursor(x, y);
    display.print(data->wifiStatusText + "\n" + ssid + "\nPass: " + password);
}

void AHDisplay::drawSensorsStatus(const long time)
{
    display.drawBitmap(sensorsPositions[0], sensorsPositions[1], data->connected[0] ? SENSOR_OK : SENSOR_KO, 5, 5, 1);
    display.drawBitmap(sensorsPositions[2], sensorsPositions[3], data->connected[1] ? SENSOR_OK : SENSOR_KO, 5, 5, 1);
    display.drawBitmap(sensorsPositions[4], sensorsPositions[5], data->connected[2] ? SENSOR_OK : SENSOR_KO, 5, 5, 1);
}

void AHDisplay::drawTemperatureAndHumidity(const long time)
{
    int xt = 41, yt = 55;
    int xh = 104, yh = 55;

    int16_t x1, y1;
    uint16_t w, h;

    const bool allSensorsDisconnect = !data->connected[0] && !data->connected[1] && !data->connected[2];

    String temperatureStr = String(int(round(data->temperature)));
    String humidityStr = String(int(round(data->humidity)));

    display.setFont(&FreeMonoBold18pt7b);
    display.getTextBounds(temperatureStr, 0, 0, &x1, &y1, &w, &h);
    display.setCursor(xt - w, yt);

    if (allSensorsDisconnect)
        display.print('?');
    else
        display.print(temperatureStr);

    display.getTextBounds(humidityStr, 0, 0, &x1, &y1, &w, &h);
    display.setCursor(xh - w, yh);

    if (allSensorsDisconnect)
        display.print('?');
    else
        display.print(humidityStr);
}

void AHDisplay::drawCat(const long time)
{
    const int frame = int(time / 500) % 9;

    switch (frame)
    {
    default:
    case 0:
        display.drawBitmap(catTailPosition[0], catTailPosition[1], CAT_TAIL_1, 20, 14, 1);
        break;
    case 1:
        display.drawBitmap(catTailPosition[0], catTailPosition[1], CAT_TAIL_2, 20, 14, 1);
        break;
    case 2:
        display.drawBitmap(catTailPosition[0], catTailPosition[1], CAT_TAIL_3, 20, 14, 1);
        break;
    case 3:
        display.drawBitmap(catTailPosition[0], catTailPosition[1], CAT_TAIL_4, 20, 14, 1);
        break;
    case 4:
        display.drawBitmap(catTailPosition[0], catTailPosition[1], CAT_TAIL_5, 20, 14, 1);
        break;
    case 5:
        display.drawBitmap(catTailPosition[0], catTailPosition[1], CAT_TAIL_6, 20, 14, 1);
        break;
    case 6:
        display.drawBitmap(catTailPosition[0], catTailPosition[1], CAT_TAIL_7, 20, 14, 1);
        break;
    case 7:
        display.drawBitmap(catTailPosition[0], catTailPosition[1], CAT_TAIL_8, 20, 14, 1);
        break;
    case 8:
        display.drawBitmap(catTailPosition[0], catTailPosition[1], CAT_TAIL_9, 20, 14, 1);
        break;
    }
}
