
#ifndef DISPLAY_H
#define DISPLAY_H

#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#include "config.h"

// Crear pantalla OLED
Adafruit_SSD1306 display(
    OLED_WIDTH,
    OLED_HEIGHT,
    &Wire,
    OLED_RESET_PIN
);

// =====================================================
// INICIALIZAR PANTALLA
// =====================================================

inline void initDisplay() {

    if (!display.begin(
        SSD1306_SWITCHCAPVCC,
        OLED_I2C_ADDRESS
    )) {

        Serial.println(F("[OLED] Error al inicializar"));
        return;
    }

    display.clearDisplay();
    display.display();

    Serial.println(F("[OLED] Inicializada correctamente"));
}

// =====================================================
// MOSTRAR TEXTO
// =====================================================

inline void showText(
    const __FlashStringHelper* texto,
    int x,
    int y,
    uint8_t tamano
) {

    display.setTextSize(tamano);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(x, y);
    display.println(texto);
    display.display();
}

// =====================================================
// PROBAR PANTALLA
// =====================================================

inline void testDisplay() {

    display.clearDisplay();

    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(20, 20);

    display.println(F("NIBO"));
    display.setCursor(20, 35);
    display.println(F("OLED FUNCIONANDO"));

    display.display();

    Serial.println(F("[OLED] Prueba completada"));
}

#endif
