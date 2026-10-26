
#include "config.h"
#include "i2c_manager.h"
#include "display.h"
#include "logo.h"
#include "logboot.h"
#include "eyes.h"
#include "debug_serial.h"
#include "motores.h"

bool bootComplete = false;
unsigned long bootTime = 0;

// Flecha hacia arriba: adelante
void dibujarFlechaArriba() {
    display.drawLine(64, 27, 64, 48, SSD1306_WHITE);
    display.fillTriangle(
        64, 7,
        46, 29,
        82, 29,
        SSD1306_WHITE
    );
}

// Flecha hacia abajo: atras
void dibujarFlechaAbajo() {
    display.drawLine(64, 8, 64, 30, SSD1306_WHITE);
    display.fillTriangle(
        64, 51,
        46, 29,
        82, 29,
        SSD1306_WHITE
    );
}

// Flecha hacia la derecha
void dibujarFlechaDerecha() {
    display.drawLine(30, 30, 94, 30, SSD1306_WHITE);
    display.fillTriangle(
        113, 30,
        89, 14,
        89, 46,
        SSD1306_WHITE
    );
}

// Flecha hacia la izquierda
void dibujarFlechaIzquierda() {
    display.drawLine(34, 30, 98, 30, SSD1306_WHITE);
    display.fillTriangle(
        15, 30,
        39, 14,
        39, 46,
        SSD1306_WHITE
    );
}

// Mostrar flecha o PARE en la OLED
void mostrarIndicadorMovimiento(Movimiento movimiento) {
    static Movimiento ultimoMovimiento = MOV_PARE;
    static bool primeraVez = true;

    // Redibujar solo cuando cambia el movimiento
    if (!primeraVez && movimiento == ultimoMovimiento) {
        return;
    }

    primeraVez = false;
    ultimoMovimiento = movimiento;

    display.clearDisplay();
    display.setTextColor(SSD1306_WHITE);

    switch (movimiento) {
        case MOV_ADELANTE:
            dibujarFlechaArriba();
            display.setTextSize(1);
            display.setCursor(43, 55);
            display.print(F("ADELANTE"));
            Serial.println(F("[OLED] ADELANTE"));
            break;

        case MOV_ATRAS:
            dibujarFlechaAbajo();
            display.setTextSize(1);
            display.setCursor(49, 55);
            display.print(F("ATRAS"));
            Serial.println(F("[OLED] ATRAS"));
            break;

        case MOV_DERECHA:
            dibujarFlechaDerecha();
            display.setTextSize(1);
            display.setCursor(46, 55);
            display.print(F("DERECHA"));
            Serial.println(F("[OLED] DERECHA"));
            break;

        case MOV_IZQUIERDA:
            dibujarFlechaIzquierda();
            display.setTextSize(1);
            display.setCursor(40, 55);
            display.print(F("IZQUIERDA"));
            Serial.println(F("[OLED] IZQUIERDA"));
            break;

        case MOV_PARE:
            display.drawRoundRect(
                22, 13, 84, 38, 4, SSD1306_WHITE
            );
            display.setTextSize(2);
            display.setCursor(38, 24);
            display.print(F("PARE"));
            Serial.println(F("[OLED] PARE"));
            break;
    }

    display.display();
}

void setup() {
    Serial.begin(115200);
    Serial.println(F("[BOOT] Sistema OLED y motores"));

    // Inicializar motores
    initMotors();

    // Inicializar I2C con los pines originales
    initI2C();
    scanI2C();
    testI2CDevice();

    // Inicializar pantalla
    initDisplay();

    // Secuencia original de arranque
    showLogo();
    delay(1500);

    testDisplay();
    delay(1000);

    showLogo();
    delay(1000);

    // Inicializar ojos animados
    initEyes();
    printHelp();

    bootTime = millis();
}

void loop() {
    // Mostrar ojos durante el arranque
    if (!bootComplete) {
        debugSerialTick();
        updateEyes();

        if (millis() - bootTime >= LOGO_TIME_MS) {
            bootComplete = true;
            Serial.println(F("[BOOT] Inicio terminado"));
        }

        return;
    }

    // Ejecutar secuencia de los motores
    motorSequenceTick();

    // Mostrar la indicación sin que los ojos la sobrescriban
    mostrarIndicadorMovimiento(obtenerMovimiento());
}
