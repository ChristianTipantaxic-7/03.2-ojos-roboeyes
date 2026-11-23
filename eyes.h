
#ifndef EYES_H
#define EYES_H

#include <Arduino.h>
#include "display.h"
#include "config.h"

#undef DEFAULT
#include <FluxGarage_RoboEyes.h>

// Crear objeto RoboEyes
RoboEyes<Adafruit_SSD1306> roboEyes(display);

// =====================================================
// INICIALIZAR OJOS
// =====================================================

inline void initEyes() {

    roboEyes.begin(
        OLED_WIDTH,
        OLED_HEIGHT,
        EYES_MAX_FPS
    );

    Serial.print(F("[EYES] Ojos inicializados a "));
    Serial.print(EYES_MAX_FPS);
    Serial.println(F(" FPS"));
}

// =====================================================
// ACTUALIZAR ANIMACIONES
// =====================================================

inline void updateEyes() {

    roboEyes.update();
}

// =====================================================
// CAMBIAR EXPRESIONES
// =====================================================

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
