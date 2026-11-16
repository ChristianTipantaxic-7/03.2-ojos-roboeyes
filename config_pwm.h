
#pragma once

#include <Arduino.h>

// --- Motor izquierdo: L293D ---
#define MOTOR_IZQ_PWM 32
#define MOTOR_IZQ_IN1 25
#define MOTOR_IZQ_IN2 26

// --- Motor derecho: L293D ---
#define MOTOR_DER_PWM 33
#define MOTOR_DER_IN1 27
#define MOTOR_DER_IN2 14

// --- Configuracion PWM ---
#define PWM_FRECUENCIA 1000
#define PWM_RESOLUCION 8
#define VELOCIDAD 180

// --- Relés indicadores ---
#define RELE_ADELANTE 16
#define RELE_ATRAS 17
#define RELE_DERECHA 18
#define RELE_IZQUIERDA 19

// 1 = activo HIGH / 0 = activo LOW
#define RELES_ACTIVOS_HIGH 1
