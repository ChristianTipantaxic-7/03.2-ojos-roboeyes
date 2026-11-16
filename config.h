
#pragma once

#include <Arduino.h>

// ============================================================================
// CONFIGURACION GLOBAL DEL PROYECTO
// ESP32 + OLED + RoboEyes + L293D + RELES
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

// --- Motor izquierdo: L293D -----------------------------------------------
#define MOTOR_IZQ_PWM 32
#define MOTOR_IZQ_IN1 25
#define MOTOR_IZQ_IN2 26

// --- Motor derecho: L293D --------------------------------------------------
#define MOTOR_DER_PWM 33
#define MOTOR_DER_IN1 27
#define MOTOR_DER_IN2 14

// --- PWM -------------------------------------------------------------------
#define PWM_FRECUENCIA 1000
#define PWM_RESOLUCION 8
#define VELOCIDAD 180

// --- Relés indicadores -----------------------------------------------------
#define RELE_ADELANTE 16
#define RELE_ATRAS 17
#define RELE_DERECHA 18
#define RELE_IZQUIERDA 19

// Cambiar a 0 si tus módulos de relé se activan con LOW
#define RELES_ACTIVOS_HIGH 1
