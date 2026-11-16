
#pragma once

#include <Arduino.h>
#include "config.h"

// ============================================================================
// ESTADOS DE MOVIMIENTO
// ============================================================================

enum Movimiento {
    MOV_ADELANTE,
    MOV_ATRAS,
    MOV_DERECHA,
    MOV_IZQUIERDA,
    MOV_PARE
};

// ============================================================================
// VARIABLES DE CONTROL
// ============================================================================

Movimiento movimientoActual = MOV_PARE;

unsigned long tiempoMovimiento = 0;
unsigned long tiempoInicioMovimiento = 0;

int pasoMovimiento = -1;

const unsigned long DURACION_MOVIMIENTO = 2000;
const unsigned long DURACION_PARE = 1000;

// ============================================================================
// FUNCIONES AUXILIARES
// ============================================================================

int limitarVelocidad(int velocidad) {
    return constrain(velocidad, 0, 255);
}

void escribirRele(int pin, bool activar) {

#if RELES_ACTIVOS_HIGH
    digitalWrite(pin, activar ? HIGH : LOW);
#else
    digitalWrite(pin, activar ? LOW : HIGH);
#endif

}

void apagarReles() {
    escribirRele(RELE_ADELANTE, false);
    escribirRele(RELE_ATRAS, false);
    escribirRele(RELE_DERECHA, false);
    escribirRele(RELE_IZQUIERDA, false);
}

void actualizarRele(Movimiento movimiento) {

    apagarReles();

    switch (movimiento) {

        case MOV_ADELANTE:
            escribirRele(RELE_ADELANTE, true);
            break;

        case MOV_ATRAS:
            escribirRele(RELE_ATRAS, true);
            break;

        case MOV_DERECHA:
            escribirRele(RELE_DERECHA, true);
            break;

        case MOV_IZQUIERDA:
            escribirRele(RELE_IZQUIERDA, true);
            break;

        case MOV_PARE:
            break;
    }
}

void cambiarMovimiento(Movimiento movimiento) {
    movimientoActual = movimiento;
    actualizarRele(movimiento);
}

// ============================================================================
// INICIALIZACION
// ============================================================================

void initMotors() {

    pinMode(MOTOR_IZQ_IN1, OUTPUT);
    pinMode(MOTOR_IZQ_IN2, OUTPUT);

    pinMode(MOTOR_DER_IN1, OUTPUT);
    pinMode(MOTOR_DER_IN2, OUTPUT);

    pinMode(RELE_ADELANTE, OUTPUT);
    pinMode(RELE_ATRAS, OUTPUT);
    pinMode(RELE_DERECHA, OUTPUT);
    pinMode(RELE_IZQUIERDA, OUTPUT);

    apagarReles();

    bool pwmIzq = ledcAttach(
        MOTOR_IZQ_PWM,
        PWM_FRECUENCIA,
        PWM_RESOLUCION
    );

    bool pwmDer = ledcAttach(
        MOTOR_DER_PWM,
        PWM_FRECUENCIA,
        PWM_RESOLUCION
    );

    ledcWrite(MOTOR_IZQ_PWM, 0);
    ledcWrite(MOTOR_DER_PWM, 0);

    digitalWrite(MOTOR_IZQ_IN1, LOW);
    digitalWrite(MOTOR_IZQ_IN2, LOW);
    digitalWrite(MOTOR_DER_IN1, LOW);
    digitalWrite(MOTOR_DER_IN2, LOW);

    movimientoActual = MOV_PARE;

    if (pwmIzq && pwmDer) {
        Serial.println(F("[MOTORES] PWM inicializado"));
    } else {
        Serial.println(F("[ERROR] No se pudo inicializar PWM"));
    }

    Serial.println(F("[MOTORES] Inicializados"));
}

// ============================================================================
// CONTROL DE MOTORES
// ============================================================================

void motorIzquierdo(int direccion, int velocidad) {

    velocidad = limitarVelocidad(velocidad);

    digitalWrite(MOTOR_IZQ_IN1, direccion == 1);
    digitalWrite(MOTOR_IZQ_IN2, direccion == -1);

    ledcWrite(MOTOR_IZQ_PWM, velocidad);
}

void motorDerecho(int direccion, int velocidad) {

    velocidad = limitarVelocidad(velocidad);

    digitalWrite(MOTOR_DER_IN1, direccion == 1);
    digitalWrite(MOTOR_DER_IN2, direccion == -1);

    ledcWrite(MOTOR_DER_PWM, velocidad);
}

// ============================================================================
// MOVIMIENTOS
// ============================================================================

void adelante(int velocidad = VELOCIDAD) {

    motorIzquierdo(1, velocidad);
    motorDerecho(1, velocidad);

    cambiarMovimiento(MOV_ADELANTE);
}

void atras(int velocidad = VELOCIDAD) {

    motorIzquierdo(-1, velocidad);
    motorDerecho(-1, velocidad);

    cambiarMovimiento(MOV_ATRAS);
}

void girarDerecha(int velocidad = VELOCIDAD) {

    motorIzquierdo(1, velocidad);
    motorDerecho(-1, velocidad);

    cambiarMovimiento(MOV_DERECHA);
}

void girarIzquierda(int velocidad = VELOCIDAD) {

    motorIzquierdo(-1, velocidad);
    motorDerecho(1, velocidad);

    cambiarMovimiento(MOV_IZQUIERDA);
}

void detener() {

    ledcWrite(MOTOR_IZQ_PWM, 0);
    ledcWrite(MOTOR_DER_PWM, 0);

    digitalWrite(MOTOR_IZQ_IN1, LOW);
    digitalWrite(MOTOR_IZQ_IN2, LOW);

    digitalWrite(MOTOR_DER_IN1, LOW);
    digitalWrite(MOTOR_DER_IN2, LOW);

    cambiarMovimiento(MOV_PARE);
}

// ============================================================================
// CONSULTAR MOVIMIENTO
// ============================================================================

Movimiento obtenerMovimiento() {
    return movimientoActual;
}

// ============================================================================
// SECUENCIA AUTOMATICA
// ============================================================================

void ejecutarPaso(int paso) {

    switch (paso) {

        case 0:
            adelante();
            Serial.println(F("[MOTORES] ADELANTE"));
            break;

        case 1:
            detener();
            Serial.println(F("[MOTORES] PARE"));
            break;

        case 2:
            atras();
            Serial.println(F("[MOTORES] ATRAS"));
            break;

        case 3:
            detener();
            Serial.println(F("[MOTORES] PARE"));
            break;

        case 4:
            girarDerecha();
            Serial.println(F("[MOTORES] DERECHA"));
            break;

        case 5:
            detener();
            Serial.println(F("[MOTORES] PARE"));
            break;

        case 6:
            girarIzquierda();
            Serial.println(F("[MOTORES] IZQUIERDA"));
            break;

        case 7:
            detener();
            Serial.println(F("[MOTORES] PARE"));
            break;
    }
}

void motorSequenceTick() {

    unsigned long ahora = millis();

    if (ahora - tiempoInicioMovimiento >= tiempoMovimiento) {

        pasoMovimiento++;

        if (pasoMovimiento > 7) {
            pasoMovimiento = 0;
        }

        ejecutarPaso(pasoMovimiento);

        tiempoInicioMovimiento = ahora;

        if (pasoMovimiento % 2 == 0) {
            tiempoMovimiento = DURACION_MOVIMIENTO;
        } else {
            tiempoMovimiento = DURACION_PARE;
        }
    }
}
