#ifndef LOGBOOT_H
#define LOGBOOT_H

#include <Arduino.h>
#include "display.h"

inline void showLogo() {

    display.clearDisplay();

    // Antena
    display.drawLine(64, 5, 64, 12, SSD1306_WHITE);
    display.fillCircle(64, 4, 3, SSD1306_WHITE);

    // Cabeza del robot
    display.drawRoundRect(35, 12, 58, 32, 7, SSD1306_WHITE);

    // Ojos
    display.fillCircle(50, 27, 4, SSD1306_WHITE);
    display.fillCircle(78, 27, 4, SSD1306_WHITE);

    // Boca
    display.drawLine(54, 36, 74, 36, SSD1306_WHITE);

    // Nombre
    display.setTextSize(2);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(40, 49);
    display.println(F("NIBO"));

    display.display();
}

inline void testDisplay() {

    display.clearDisplay();
    display.drawRect(54, 22, 20, 20, SSD1306_WHITE);
    display.display();

    Serial.println(F("POST OLED: prueba completada"));
}

#endif