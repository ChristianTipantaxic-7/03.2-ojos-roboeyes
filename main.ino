// main.ino
// ============================================
// RESPONSABILIDAD: Orquestar arranque y bucle principal del sistema.
// No sabe como hacer nada: solo llama a cada modulo en el orden correcto.
// ============================================

#include "config.h"
#include "i2c_manager.h"
#include "display.h"
#include "logo.h"
#include "logboot.h"
#include "eyes.h"
#include "debug_serial.h"

// Estados de la maquina de arranque y marca de tiempo de su ventana
bool bootComplete = false;
unsigned long bootTime = 0;

void setup() {
    Serial.begin(115200);
    Serial.println(F("[BOOT] sistema de ojos OLED"));

    // CHECK 1.5: Escribe las llamadas de los pasos 1 a 4 para dejar el bus y el panel listos.
    // Paso 1 — Puerto serie abierto a la velocidad del monitor.
    // Paso 2 — Bus I2C compartido levantado.
    // Paso 3 — Barrido del bus reportado.
    // Paso 4 — Dirección del panel sondeada.

    initI2C();
    scanI2C();
    testI2CDevice();

    // CHECK 2.4: Escribe las llamadas de los pasos 5 y 6 para pintar el logo y ejecutar el POST de pantalla.
    // Paso 5 — Panel inicializado.
    // Paso 6 — Logo pintado y POST de pantalla.

    initDisplay();
    showLogo();
    testDisplay();
    showLogo();

    // CHECK 3.4: Escribe la llamada del paso 7 para dejar los ojos listos.
    // Paso 7 — Ojos inicializados.

    initEyes();

    // CHECK 4.3: Escribe la llamada del paso 8, publica la ayuda y arma la ventana de arranque.
    // Paso 8 — Ayuda publicada y ventana de arranque armada.

    printHelp();

    bootTime = millis();
}

void loop() {

    // CHECK 2.4 (continuación): Mientras la ventana de arranque no expire,
    // mantenemos el logo en pantalla.

    if (!bootComplete) {

        if (millis() - bootTime >= LOGO_TIME_MS) {

            bootComplete = true;

            Serial.println(F("[BOOT] ventana de arranque terminada"));

        } else {

            return;

        }
    }

    // CHECK 4.3 (continuación): Con el arranque terminado,
    // atiende la consola y avanza la animación sin bloquear.

    debugSerialTick();
    updateEyes();

}