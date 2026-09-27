// logo.h

// ============================================

// RESPONSABILIDAD: Guardar el bitmap del logo de arranque y su geometria.

// No sabe nada de: OLED, bus I2C, ojos ni Monitor Serie.

// ============================================
//
// Estos datos ya estan listos: el reto no es dibujarlos, es leerlos bien y
// usarlos para pintar el marco de arranque en el panel.

#ifndef LOGO_H

#define LOGO_H

#include <Arduino.h>

#include "config.h"

// Dimensiones del bitmap en pixeles

#define LOGO_WIDTH 128
#define LOGO_HEIGHT 64

const unsigned char logo_bitmap[] PROGMEM = {

    // AQUÍ SE MANTIENE TODO EL BITMAP ORIGINAL QUE TE DIO EL PROFESOR

};

// CHECK 2.1: Usa estos datos (LOGO_WIDTH × LOGO_HEIGHT y logo_bitmap) para pintar el logo de arranque en el panel.

// Pregunta Guía: ¿Cuántos bytes ocupa el logo y por qué ese número sale de 128 × 64 / 8?

#endif