
#ifndef MOTORES_H
#define MOTORES_H

#include <Arduino.h>

// Pines originales de los cuatro reles
const int rele1A = 25;
const int rele1B = 26;
const int rele2A = 27;
const int rele2B = 14;

// Estados del movimiento
enum Movimiento {
    MOV_PARE,
    MOV_ADELANTE,
    MOV_ATRAS,
    MOV_DERECHA,
    MOV_IZQUIERDA
};

static Movimiento estadoMovimiento = MOV_PARE;

// Motor izquierdo
inline void motorIzquierdo(bool adelante) {
    digitalWrite(rele1A, adelante ? HIGH : LOW);
    digitalWrite(rele1B, adelante ? HIGH : LOW);
}

// Motor derecho
inline void motorDerecho(bool adelante) {
    digitalWrite(rele2A, adelante ? HIGH : LOW);
    digitalWrite(rele2B, adelante ? HIGH : LOW);
}

// Detener motores
inline void detenerMotorIzquierdo() {
    digitalWrite(rele1A, HIGH);
    digitalWrite(rele1B, LOW);
}

inline void detenerMotorDerecho() {
    digitalWrite(rele2A, HIGH);
    digitalWrite(rele2B, LOW);
}

inline void detener() {
    detenerMotorIzquierdo();
    detenerMotorDerecho();
}

// Movimientos
inline void adelante() {
    motorIzquierdo(true);
    motorDerecho(true);
}

inline void atras() {
    motorIzquierdo(false);
    motorDerecho(false);
}

inline void derecha() {
    motorIzquierdo(true);
    motorDerecho(false);
}

inline void izquierda() {
    motorIzquierdo(false);
    motorDerecho(true);
}

// Inicializar relés
inline void initMotors() {
    pinMode(rele1A, OUTPUT);
    pinMode(rele1B, OUTPUT);
    pinMode(rele2A, OUTPUT);
    pinMode(rele2B, OUTPUT);

    detener();
    Serial.println(F("[MOTORES] Pines inicializados."));
}

// Obtener el movimiento actual
inline Movimiento obtenerMovimiento() {
    return estadoMovimiento;
}

// Duración de cada fase en milisegundos
static unsigned long motorPhaseStart = 0;
static uint8_t motorPhase = 0;
static bool motorSequenceStarted = false;

inline unsigned long duracionFaseMotor(uint8_t fase) {
    switch (fase) {
        case 0: return 2000; // Adelante
        case 1: return 700;  // Pare
        case 2: return 2000; // Atras
        case 3: return 700;  // Pare
        case 4: return 1500; // Derecha
        case 5: return 700;  // Pare
        case 6: return 1500; // Izquierda
        case 7: return 1500; // Pare
        default: return 1000;
    }
}

// Aplicar movimiento y actualizar su estado
inline void aplicarFaseMotor(uint8_t fase) {
    switch (fase) {
        case 0:
            estadoMovimiento = MOV_ADELANTE;
            adelante();
            break;

        case 1:
            estadoMovimiento = MOV_PARE;
            detener();
            break;

        case 2:
            estadoMovimiento = MOV_ATRAS;
            atras();
            break;

        case 3:
            estadoMovimiento = MOV_PARE;
            detener();
            break;

        case 4:
            estadoMovimiento = MOV_DERECHA;
            derecha();
            break;

        case 5:
            estadoMovimiento = MOV_PARE;
            detener();
            break;

        case 6:
            estadoMovimiento = MOV_IZQUIERDA;
            izquierda();
            break;

        case 7:
            estadoMovimiento = MOV_PARE;
            detener();
            break;
    }
}

// Secuencia automática sin delays
inline void motorSequenceTick() {
    unsigned long ahora = millis();

    if (!motorSequenceStarted) {
        motorSequenceStarted = true;
        motorPhase = 0;
        aplicarFaseMotor(motorPhase);
        motorPhaseStart = ahora;

        Serial.println(F("[MOTORES] Secuencia iniciada."));
        return;
    }

    if (ahora - motorPhaseStart >= duracionFaseMotor(motorPhase)) {
        motorPhase = (motorPhase + 1) % 8;
        aplicarFaseMotor(motorPhase);
        motorPhaseStart = ahora;
    }
}

#endif
