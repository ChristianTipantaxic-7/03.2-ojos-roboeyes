
#include "config.h"
#include "config_pwm.h"
#include "i2c_manager.h"
#include "display.h"
#include "logo.h"
#include "logboot.h"
#include "eyes.h"
#include "debug_serial.h"
#include "motores.h"

// =====================================================
// VARIABLES PRINCIPALES
// =====================================================

bool bootComplete = false;
unsigned long bootTime = 0;

// =====================================================
// DIBUJAR FLECHAS EN LA PANTALLA OLED
// =====================================================

void dibujarFlechaArriba() {
    display.drawLine(64, 27, 64, 48, SSD1306_WHITE);
    display.fillTriangle(64, 7, 46, 29, 82, 29, SSD1306_WHITE);
}

void dibujarFlechaAbajo() {
    display.drawLine(64, 8, 64, 30, SSD1306_WHITE);
    display.fillTriangle(64, 51, 46, 29, 82, 29, SSD1306_WHITE);
}

void dibujarFlechaDerecha() {
    display.drawLine(30, 30, 94, 30, SSD1306_WHITE);
    display.fillTriangle(113, 30, 89, 14, 89, 46, SSD1306_WHITE);
}

void dibujarFlechaIzquierda() {
    display.drawLine(34, 30, 98, 30, SSD1306_WHITE);
    display.fillTriangle(15, 30, 39, 14, 39, 46, SSD1306_WHITE);
}

// =====================================================
// MOSTRAR MOVIMIENTO EN OLED
// =====================================================

void mostrarIndicadorMovimiento(Movimiento movimiento) {

    static Movimiento ultimoMovimiento = MOV_PARE;
    static bool primeraVez = true;

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
            break;

        case MOV_ATRAS:
            dibujarFlechaAbajo();
            display.setTextSize(1);
            display.setCursor(49, 55);
            display.print(F("ATRAS"));
            break;

        case MOV_DERECHA:
            dibujarFlechaDerecha();
            display.setTextSize(1);
            display.setCursor(46, 55);
            display.print(F("DERECHA"));
            break;

        case MOV_IZQUIERDA:
            dibujarFlechaIzquierda();
            display.setTextSize(1);
            display.setCursor(40, 55);
            display.print(F("IZQUIERDA"));
            break;

        case MOV_PARE:
            display.drawRoundRect(22, 13, 84, 38, 4, SSD1306_WHITE);
            display.setTextSize(2);
            display.setCursor(38, 24);
            display.print(F("PARE"));
            break;
    }

    display.display();

    Serial.print(F("[OLED] Movimiento: "));
    Serial.println((int)movimiento);
}

// =====================================================
// CONFIGURACION INICIAL
// =====================================================

void setup() {

    Serial.begin(115200);

    Serial.println(F("[BOOT] Sistema NIBO"));

    // Inicializar motores
    initMotors();

    // Inicializar comunicacion I2C
    initI2C();
    scanI2C();
    testI2CDevice();

    // Inicializar pantalla
    initDisplay();

    // Mostrar presentacion
    showLogo();
    delay(1500);

    testDisplay();
    delay(1000);

    showLogo();
    delay(1000);

    // Inicializar ojos animados
    initEyes();

    // Mostrar instrucciones
    printHelp();

    bootTime = millis();
}

// =====================================================
// BUCLE PRINCIPAL
// =====================================================

void loop() {

    // Etapa de inicio
    if (!bootComplete) {

        debugSerialTick();
        updateEyes();

        if (millis() - bootTime >= LOGO_TIME_MS) {

            bootComplete = true;

            Serial.println(F("[BOOT] Inicio terminado"));
        }

        return;
    }

    // Etapa de funcionamiento
    motorSequenceTick();

    mostrarIndicadorMovimiento(obtenerMovimiento());
}
