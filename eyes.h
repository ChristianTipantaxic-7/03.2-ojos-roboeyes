// eyes.h

// ============================================

// RESPONSABILIDAD: Animar los ojos del OLED y aplicar la expresión elegida.

// No sabe nada de: bus I2C, logos de arranque, POST ni Monitor Serie.

// ============================================

#ifndef EYES_H

#define EYES_H

#include <Arduino.h>

#include "display.h"

#include "config.h"

// Arduino.h del ESP32 puede definir DEFAULT.
// Se limpia antes de incluir RoboEyes para evitar
// el conflicto con la definición de RoboEyes.

#undef DEFAULT

#include <FluxGarage_RoboEyes.h>

// Instancia global: el sistema tiene un solo par de ojos

RoboEyes<Adafruit_SSD1306> roboEyes(display);

// CHECK 3.1: Inicializa los ojos con las dimensiones del panel
// y el objetivo de cuadros por segundo de config.h.

inline void initEyes() {

    roboEyes.begin(OLED_WIDTH, OLED_HEIGHT, EYES_MAX_FPS);

    Serial.print(F("[EYES] ojos listos a "));
    Serial.print(EYES_MAX_FPS);
    Serial.println(F(" fps"));
}

// CHECK 3.2: Avanza la animación un paso sin bloquear.

inline void updateEyes() {

    roboEyes.update();
}

// CHECK 3.3: Aplica la expresión pedida por tecla (1 a 7).

inline void setEyesMood(char key) {

    switch (key) {

        case '1':
            roboEyes.setMood(DEFAULT);
            break;

        case '2':
            roboEyes.setMood(TIRED);
            break;

        case '3':
            roboEyes.setMood(ANGRY);
            break;

        case '4':
            roboEyes.setMood(HAPPY);
            break;

        case '5':
            roboEyes.setMood(TIRED);
            break;

        case '6':
            roboEyes.setMood(ANGRY);
            break;

        case '7':
            roboEyes.setMood(HAPPY);
            break;

        default:
            break;
    }
}

#endif