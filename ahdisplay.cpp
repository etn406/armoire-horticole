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
    int xt = 41, yt = 55;
    int xh = 104, yh = 55;

    int16_t x1, y1;
    uint16_t w, h;

    String temperatureStr = String(int(round(temperature)));
    String humidityStr = String(int(round(humidity)));

    display.clearDisplay();
    display.setTextColor(SSD1306_WHITE);

    display.drawBitmap(0, 0, InterfaceBMP, display.width(), display.height(), 1);

    display.setFont(&FreeMonoBold18pt7b);
    display.getTextBounds(temperatureStr, 0, 0, &x1, &y1, &w, &h);
    display.setCursor(xt - w, yt);
    display.print(temperatureStr);

    display.getTextBounds(humidityStr, 0, 0, &x1, &y1, &w, &h);
    display.setCursor(xh - w, yh);
    display.print(humidityStr);

    display.setFont();
    display.setCursor(0, 0);
    display.print(wifiStatus);

    String seconds = String(int(time / 1000)) + "s";
    display.getTextBounds(seconds, 0, 0, &x1, &y1, &w, &h);
    display.setCursor(display.width() - w, 0);
    display.print(seconds);

    display.display();
}
