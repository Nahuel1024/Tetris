/**
 * @file fuente.c
 * @brief Implementacion del sistema unificado de fuentes bitmap.
 */

#include "fuente.h"
#include <string.h>

/* ========================================================================== */
/* BITMAPS: FUENTE LARGE 8x8                                                  */
/* ========================================================================== */

static const uint8_t bmp_large_A[8] = {0x3C,0x66,0xC3,0xFF,0xC3,0xC3,0xC3,0x00};
static const uint8_t bmp_large_C[8] = {0x3C,0x66,0xC0,0xC0,0xC0,0x66,0x3C,0x00};
static const uint8_t bmp_large_E[8] = {0xFE,0xC0,0xC0,0xFC,0xC0,0xC0,0xFE,0x00};
static const uint8_t bmp_large_G[8] = {0x3C,0x66,0xC0,0xCF,0xC3,0x66,0x3C,0x00};
static const uint8_t bmp_large_I[8] = {0x7E,0x18,0x18,0x18,0x18,0x18,0x7E,0x00};
static const uint8_t bmp_large_M[8] = {0xC3,0xE7,0xFF,0xDB,0xC3,0xC3,0xC3,0x00};
static const uint8_t bmp_large_N[8] = {0xC3,0xE3,0xF3,0xDB,0xCF,0xC7,0xC3,0x00};
static const uint8_t bmp_large_O[8] = {0x3C,0x66,0xC3,0xC3,0xC3,0x66,0x3C,0x00};
static const uint8_t bmp_large_P[8] = {0xFC,0xC6,0xC6,0xFC,0xC0,0xC0,0xC0,0x00};
static const uint8_t bmp_large_R[8] = {0xFC,0xC6,0xC6,0xFC,0xD8,0xCC,0xC6,0x00};
static const uint8_t bmp_large_S[8] = {0x7E,0xC0,0xC0,0x7C,0x06,0x06,0xFC,0x00};
static const uint8_t bmp_large_T[8] = {0xFF,0x18,0x18,0x18,0x18,0x18,0x18,0x00};
static const uint8_t bmp_large_U[8] = {0xC6,0xC6,0xC6,0xC6,0xC6,0xC6,0x7C,0x00};
static const uint8_t bmp_large_X[8] = {0xC3,0x66,0x3C,0x18,0x3C,0x66,0xC3,0x00};

static const uint8_t bmp_large_0[8] = {0x3C,0x66,0xCE,0xD6,0xE6,0x66,0x3C,0x00};
static const uint8_t bmp_large_1[8] = {0x18,0x38,0x18,0x18,0x18,0x18,0x7E,0x00};
static const uint8_t bmp_large_2[8] = {0x3C,0x66,0x06,0x1C,0x30,0x60,0x7E,0x00};
static const uint8_t bmp_large_3[8] = {0x3C,0x66,0x06,0x1C,0x06,0x66,0x3C,0x00};
static const uint8_t bmp_large_4[8] = {0x0C,0x1C,0x3C,0x6C,0xFE,0x0C,0x0C,0x00};
static const uint8_t bmp_large_5[8] = {0x7E,0x60,0x7C,0x06,0x06,0x66,0x3C,0x00};
static const uint8_t bmp_large_6[8] = {0x3C,0x60,0x7C,0x66,0x66,0x66,0x3C,0x00};
static const uint8_t bmp_large_7[8] = {0x7E,0x06,0x0C,0x18,0x30,0x30,0x30,0x00};
static const uint8_t bmp_large_8[8] = {0x3C,0x66,0x66,0x3C,0x66,0x66,0x3C,0x00};
static const uint8_t bmp_large_9[8] = {0x3C,0x66,0x66,0x3E,0x06,0x0C,0x38,0x00};

/* ========================================================================== */
/* BITMAPS: FUENTE SMALL 5x7                                                  */
/* ========================================================================== */

static const uint8_t bmp_small_A[7] = {0x0E,0x11,0x11,0x1F,0x11,0x11,0x11};
static const uint8_t bmp_small_B[7] = {0x1E,0x11,0x11,0x1E,0x11,0x11,0x1E};
static const uint8_t bmp_small_C[7] = {0x0E,0x11,0x10,0x10,0x10,0x11,0x0E};
static const uint8_t bmp_small_D[7] = {0x1E,0x11,0x11,0x11,0x11,0x11,0x1E};
static const uint8_t bmp_small_E[7] = {0x1F,0x10,0x10,0x1E,0x10,0x10,0x1F};
static const uint8_t bmp_small_F[7] = {0x1F,0x10,0x10,0x1E,0x10,0x10,0x10};
static const uint8_t bmp_small_G[7] = {0x0E,0x11,0x10,0x17,0x11,0x11,0x0F};
static const uint8_t bmp_small_H[7] = {0x11,0x11,0x11,0x1F,0x11,0x11,0x11};
static const uint8_t bmp_small_I[7] = {0x0E,0x04,0x04,0x04,0x04,0x04,0x0E};
static const uint8_t bmp_small_J[7] = {0x07,0x02,0x02,0x02,0x02,0x12,0x0C};
static const uint8_t bmp_small_K[7] = {0x11,0x12,0x14,0x18,0x14,0x12,0x11};
static const uint8_t bmp_small_L[7] = {0x10,0x10,0x10,0x10,0x10,0x10,0x1F};
static const uint8_t bmp_small_M[7] = {0x11,0x1B,0x15,0x15,0x11,0x11,0x11};
static const uint8_t bmp_small_N[7] = {0x11,0x19,0x15,0x13,0x11,0x11,0x11};
static const uint8_t bmp_small_O[7] = {0x0E,0x11,0x11,0x11,0x11,0x11,0x0E};
static const uint8_t bmp_small_P[7] = {0x1E,0x11,0x11,0x1E,0x10,0x10,0x10};
static const uint8_t bmp_small_Q[7] = {0x0E,0x11,0x11,0x11,0x15,0x12,0x0D};
static const uint8_t bmp_small_R[7] = {0x1E,0x11,0x11,0x1E,0x14,0x12,0x11};
static const uint8_t bmp_small_S[7] = {0x0F,0x10,0x10,0x0E,0x01,0x01,0x1E};
static const uint8_t bmp_small_T[7] = {0x1F,0x04,0x04,0x04,0x04,0x04,0x04};
static const uint8_t bmp_small_U[7] = {0x11,0x11,0x11,0x11,0x11,0x11,0x0E};
static const uint8_t bmp_small_V[7] = {0x11,0x11,0x11,0x11,0x11,0x0A,0x04};
static const uint8_t bmp_small_W[7] = {0x11,0x11,0x11,0x15,0x15,0x1B,0x11};
static const uint8_t bmp_small_X[7] = {0x11,0x11,0x0A,0x04,0x0A,0x11,0x11};
static const uint8_t bmp_small_Y[7] = {0x11,0x11,0x0A,0x04,0x04,0x04,0x04};
static const uint8_t bmp_small_Z[7] = {0x1F,0x01,0x02,0x04,0x08,0x10,0x1F};

/* ========================================================================== */
/* ARRAYS DE GLIFOS                                                           */
/* ========================================================================== */

static const t_glifo glifos_large[] = {
    {'0',bmp_large_0},{'1',bmp_large_1},{'2',bmp_large_2},{'3',bmp_large_3},
    {'4',bmp_large_4},{'5',bmp_large_5},{'6',bmp_large_6},{'7',bmp_large_7},
    {'8',bmp_large_8},{'9',bmp_large_9},
    {'A',bmp_large_A},{'C',bmp_large_C},{'E',bmp_large_E},{'G',bmp_large_G},
    {'I',bmp_large_I},{'M',bmp_large_M},{'N',bmp_large_N},{'O',bmp_large_O},
    {'P',bmp_large_P},{'R',bmp_large_R},{'S',bmp_large_S},{'T',bmp_large_T},
    {'U',bmp_large_U},{'X',bmp_large_X},
};

static const t_glifo glifos_small[] = {
    {'A',bmp_small_A},{'B',bmp_small_B},{'C',bmp_small_C},{'D',bmp_small_D},
    {'E',bmp_small_E},{'F',bmp_small_F},{'G',bmp_small_G},{'H',bmp_small_H},
    {'I',bmp_small_I},{'J',bmp_small_J},{'K',bmp_small_K},{'L',bmp_small_L},
    {'M',bmp_small_M},{'N',bmp_small_N},{'O',bmp_small_O},{'P',bmp_small_P},
    {'Q',bmp_small_Q},{'R',bmp_small_R},{'S',bmp_small_S},{'T',bmp_small_T},
    {'U',bmp_small_U},{'V',bmp_small_V},{'W',bmp_small_W},{'X',bmp_small_X},
    {'Y',bmp_small_Y},{'Z',bmp_small_Z},
};

/* ========================================================================== */
/* DEFINICION DE FUENTES                                                      */
/* ========================================================================== */

const t_fuente FUENTE_LARGE = {"LARGE", 8, 8, 10, glifos_large, 24};
const t_fuente FUENTE_SMALL = {"SMALL", 5, 7,  6, glifos_small, 26};

/* ========================================================================== */
/* HELPERS INTERNOS                                                           */
/* ========================================================================== */

static const t_glifo* fuente_buscar_glifo(const t_fuente *fuente, char c)
{
    for(int i = 0; i < fuente->cantidad; i++)
        if(fuente->glifos[i].caracter == c)
            return &fuente->glifos[i];
    return NULL;
}

static uint8_t fuente_mascara_inicio(const t_fuente *fuente)
{
    return (uint8_t)(1 << (fuente->ancho - 1));
}

/* ========================================================================== */
/* PRIMITIVAS DE DIBUJO                                                       */
/* ========================================================================== */

void fuente_dibujar_caracter(const t_fuente *fuente, const t_layout *layout,
                              int x, int y, char c, int color)
{
    const t_glifo *glifo = fuente_buscar_glifo(fuente, c);
    if(glifo == NULL)
        return;

    int factor  = (int)layout->escala_pantalla;
    uint8_t msb = fuente_mascara_inicio(fuente);

    for(int fila = 0; fila < fuente->alto; fila++)
    {
        uint8_t mascara = glifo->bitmap[fila];
        for(int col = 0; col < fuente->ancho; col++)
        {
            if(mascara & (msb >> col))
            {
                for(int py = 0; py < factor; py++)
                    for(int px = 0; px < factor; px++)
                        gbt_dibujar_pixel(x + col * factor + px,
                                          y + fila * factor + py,
                                          color);
            }
        }
    }
}

void fuente_dibujar_texto(const t_fuente *fuente, const t_layout *layout,
                           int x, int y, const char *texto, int color)
{
    int avance = fuente->espaciado * (int)layout->escala_pantalla;
    while(*texto)
    {
        fuente_dibujar_caracter(fuente, layout, x, y, *texto, color);
        x += avance;
        texto++;
    }
}

int fuente_ancho_texto(const t_fuente *fuente, const t_layout *layout, const char *texto)
{
    return (int)strlen(texto) * fuente->espaciado * (int)layout->escala_pantalla;
}

int fuente_alto_glifo(const t_fuente *fuente, const t_layout *layout)
{
    return fuente->alto * (int)layout->escala_pantalla;
}
