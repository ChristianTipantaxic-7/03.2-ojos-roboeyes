// main.ino
#include "config.h"
#include "i2c_manager.h"
#include "display.h"
#include "logo.h"
#include "logboot.h"
#include "eyes.h"
#include "debug_serial.h"

bool bootComplete = false;
unsigned long bootTime = 0;

void setup() {
    Serial.begin(115200);
    Serial.println(F("[BOOT] sistema de ojos OLED"));

    initI2C();
    scanI2C();
    testI2CDevice();

    initDisplay();

    showLogo();
    delay(1500);

    testDisplay();
    delay(1000);

    showLogo();
    delay(1000);

    initEyes();

    printHelp();

    bootTime = millis();
}

void loop() {
    if (!bootComplete) {
        if (millis() - bootTime >= LOGO_TIME_MS) {
            bootComplete = true;
            Serial.println(F("[BOOT] ventana de arranque terminada"));
        } else {
            return;
        }
    }

    debugSerialTick();
    updateEyes();
}