// debug_serial.h

// ============================================

// RESPONSABILIDAD: Leer comandos del Monitor Serie y mostrar la ayuda.

// No sabe nada de: bus I2C, OLED, logos ni animacion interna de los ojos.

// ============================================

#ifndef DEBUG_SERIAL_H

#define DEBUG_SERIAL_H

#include <Arduino.h>

#include "config.h"

#include "eyes.h"

// CHECK 4.1: Publica el bloque de ayuda con las 7 expresiones y la tecla de ayuda.

// Pregunta Guía: ¿Qué debe ver un compañero que abre el monitor por primera vez?

inline void printHelp() {

    Serial.println();
    Serial.println(F("=== CONTROL DE EXPRESIONES ==="));
    Serial.println(F("1 - Expresion 1"));
    Serial.println(F("2 - Expresion 2"));
    Serial.println(F("3 - Expresion 3"));
    Serial.println(F("4 - Expresion 4"));
    Serial.println(F("5 - Expresion 5"));
    Serial.println(F("6 - Expresion 6"));
    Serial.println(F("7 - Expresion 7"));
    Serial.println(F("h - Mostrar ayuda"));
    Serial.println(F("==============================="));
    Serial.println();

}

// CHECK 4.2: Atiende el puerto sin bloquear: una tecla, respuesta inmediata; teclas 1 a 7 cambian la expresion, h repite la ayuda, los caracteres de control se ignoran en silencio.

// Pregunta Guía: ¿Qué pasa con una tecla desconocida y qué pasa con un carácter de control?

inline void debugSerialTick() {

    if (!Serial.available()) {
        return;
    }

    char command = Serial.read();

    // Ignorar caracteres de control como Enter, salto de línea, etc.
    if (command < 32) {
        return;
    }

    // Teclas 1 a 7 cambian la expresión.
    if (command >= '1' && command <= '7') {
        setEyesMood(command);
    }

    // h o H muestran nuevamente la ayuda.
    else if (command == 'h' || command == 'H') {
        printHelp();
    }

}

#endif