#pragma once

#include <Arduino.h>

// ============================================================================
// CONFIGURACION GLOBAL DEL PROYECTO
// ESP32 + OLED + RoboEyes
// ============================================================================

// --- Bus I2C ---------------------------------------------------------------
#define I2C_SDA_PIN 21
#define I2C_SCL_PIN 22
#define I2C_FREQUENCY_HZ 400000

// --- Pantalla OLED ---------------------------------------------------------
#define OLED_I2C_ADDRESS 0x3C
#define OLED_WIDTH 128
#define OLED_HEIGHT 64
#define OLED_RESET_PIN -1

// --- RoboEyes --------------------------------------------------------------
#define EYES_MAX_FPS 60

// --- Arranque --------------------------------------------------------------
#define LOGO_TIME_MS 3000