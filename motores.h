
#pragma once

#include <Arduino.h>
#include "config_pwm.h"

// =====================================================
// ESTADOS DE MOVIMIENTO
// =====================================================

enum Movimiento {
    MOV_ADELANTE,
    MOV_ATRAS,
    MOV_DERECHA,
    MOV_IZQUIERDA,
    MOV_PARE
};

// =====================================================
// VARIABLES DEL SISTEMA
// =====================================================

Movimiento movimientoActual = MOV_PARE;

unsigned long tiempoInicioMovimiento = 0;

int pasoMovimiento = 0;

const unsigned long DURACION_MOVIMIENTO = 2000;
const unsigned long DURACION_PARE = 1000;

// =====================================================
// LIMITAR VELOCIDAD
// =====================================================

int limitarVelocidad(int velocidad) {
    return constrain(velocidad, 0, 255);
}

// =====================================================
// INICIALIZAR MOTORES
// =====================================================

void initMotors() {

    pinMode(MOTOR_IZQ_IN1, OUTPUT);
    pinMode(MOTOR_IZQ_IN2, OUTPUT);

    pinMode(MOTOR_DER_IN1, OUTPUT);
    pinMode(MOTOR_DER_IN2, OUTPUT);

    ledcAttach(MOTOR_IZQ_PWM, PWM_FRECUENCIA, PWM_RESOLUCION);
    ledcAttach(MOTOR_DER_PWM, PWM_FRECUENCIA, PWM_RESOLUCION);

    detener();

    Serial.println(F("[MOTORES] Inicializados"));

    // Comenzar la secuencia avanzando
    pasoMovimiento = -1;
    tiempoInicioMovimiento = millis();
}

// =====================================================
// CONTROL DEL MOTOR IZQUIERDO
// =====================================================

void motorIzquierdo(int direccion, int velocidad) {

    velocidad = limitarVelocidad(velocidad);

    digitalWrite(MOTOR_IZQ_IN1, direccion == 1);
    digitalWrite(MOTOR_IZQ_IN2, direccion == -1);

    ledcWrite(MOTOR_IZQ_PWM, velocidad);
}

// =====================================================
// CONTROL DEL MOTOR DERECHO
// =====================================================

void motorDerecho(int direccion, int velocidad) {

    velocidad = limitarVelocidad(velocidad);

    digitalWrite(MOTOR_DER_IN1, direccion == 1);
    digitalWrite(MOTOR_DER_IN2, direccion == -1);

    ledcWrite(MOTOR_DER_PWM, velocidad);
}

// =====================================================
// MOVIMIENTOS
// =====================================================

void adelante(int velocidad = VELOCIDAD) {

    motorIzquierdo(1, velocidad);
    motorDerecho(1, velocidad);

    movimientoActual = MOV_ADELANTE;
}

void atras(int velocidad = VELOCIDAD) {

    motorIzquierdo(-1, velocidad);
    motorDerecho(-1, velocidad);

    movimientoActual = MOV_ATRAS;
}

void girarDerecha(int velocidad = VELOCIDAD) {

    motorIzquierdo(1, velocidad);
    motorDerecho(-1, velocidad);

    movimientoActual = MOV_DERECHA;
}

void girarIzquierda(int velocidad = VELOCIDAD) {

    motorIzquierdo(-1, velocidad);
    motorDerecho(1, velocidad);

    movimientoActual = MOV_IZQUIERDA;
}

void detener() {

    ledcWrite(MOTOR_IZQ_PWM, 0);
    ledcWrite(MOTOR_DER_PWM, 0);

    digitalWrite(MOTOR_IZQ_IN1, LOW);
    digitalWrite(MOTOR_IZQ_IN2, LOW);

    digitalWrite(MOTOR_DER_IN1, LOW);
    digitalWrite(MOTOR_DER_IN2, LOW);

    movimientoActual = MOV_PARE;
}

// =====================================================
// OBTENER MOVIMIENTO ACTUAL
// =====================================================

Movimiento obtenerMovimiento() {
    return movimientoActual;
}

// =====================================================
// EJECUTAR PASOS DE LA SECUENCIA
// =====================================================

void ejecutarPaso(int paso) {

    switch (paso) {

        case 0:
            adelante();
            Serial.println(F("[MOTORES] Adelante"));
            break;

        case 1:
            detener();
            Serial.println(F("[MOTORES] Pare"));
            break;

        case 2:
            atras();
            Serial.println(F("[MOTORES] Atras"));
            break;

        case 3:
            detener();
            Serial.println(F("[MOTORES] Pare"));
            break;

        case 4:
            girarDerecha();
            Serial.println(F("[MOTORES] Derecha"));
            break;

        case 5:
            detener();
            Serial.println(F("[MOTORES] Pare"));
            break;

        case 6:
            girarIzquierda();
            Serial.println(F("[MOTORES] Izquierda"));
            break;

        case 7:
            detener();
            Serial.println(F("[MOTORES] Pare"));
            break;
    }
}

// =====================================================
// CONTROL AUTOMATICO DE LA SECUENCIA
// =====================================================

void motorSequenceTick() {

    unsigned long ahora = millis();

    unsigned long duracionActual =
        (pasoMovimiento % 2 == 0)
        ? DURACION_MOVIMIENTO
        : DURACION_PARE;

    if (ahora - tiempoInicioMovimiento >= duracionActual) {

        pasoMovimiento++;

        if (pasoMovimiento > 7) {
            pasoMovimiento = 0;
        }

        ejecutarPaso(pasoMovimiento);

        tiempoInicioMovimiento = ahora;
    }
}
