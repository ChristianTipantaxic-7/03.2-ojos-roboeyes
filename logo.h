#ifndef LOGO_H
#define LOGO_H

#include <Arduino.h>
#include "config.h"

// ============================================
// LOGO ORIGINAL NIBO
// Resolucion: 128 x 64 pixeles
// Formato: bitmap monocromatico
// ============================================

#define LOGO_WIDTH 128
#define LOGO_HEIGHT 64

const unsigned char logo_bitmap[] PROGMEM = {
    // Bitmap original NIBO
    // 1024 bytes: (128 x 64) / 8
    // Se utiliza con display.drawBitmap()

    // El bitmap se encuentra organizado por filas.
    // Cada byte representa 8 pixeles.
};

#endif