#ifndef DEBUG_SERIAL_H
#define DEBUG_SERIAL_H

#include <Arduino.h>
#include "config.h"
#include "eyes.h"

// ============================================
// AYUDA DEL MONITOR SERIE
// ============================================

inline void printHelp() {

    Serial.println();
    Serial.println(F("========== NIBO =========="));
    Serial.println(F(" CONTROL DE EXPRESIONES"));
    Serial.println(F("=========================="));
    Serial.println(F("1 - Normal"));
    Serial.println(F("2 - Cansado"));
    Serial.println(F("3 - Enojado"));
    Serial.println(F("4 - Feliz"));
    Serial.println(F("5 - Cansado"));
    Serial.println(F("6 - Enojado"));
    Serial.println(F("7 - Feliz"));
    Serial.println(F("h - Mostrar ayuda"));
    Serial.println(F("=========================="));
    Serial.println();

}

// ============================================
// LECTURA DE COMANDOS
// ============================================

inline void debugSerialTick() {

    if (!Serial.available()) {
        return;
    }

    char command = Serial.read();

    if (command < 32) {
        return;
    }

    if (command >= '1' && command <= '7') {

        setEyesMood(command);

        Serial.print(F("[NIBO] Expresion seleccionada: "));
        Serial.println(command);

    }

    else if (command == 'h' || command == 'H') {

        printHelp();

    }

}

#endif