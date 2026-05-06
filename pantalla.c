#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "GBT/gbt.h"
#include "GBT/gbt_graficos.h"
#include "pantalla.h"
#include "paletacolor.h"

#define TAM_CELDA 10

int tablero[FILAS][COLUMNAS] = {0};
int ancho_sistema;
int alto_sistema;
int ancho_tablero = COLUMNAS * TAM_CELDA;
int alto_tablero  = 20 * TAM_CELDA; // solo 20 visibles

void iniciar_pantalla(int reso)
{
    if(reso == 0)
    {
        ancho_sistema = ANCHO_CGA;
        alto_sistema = ALTO_CGA;
    }
    else
    {
        ancho_sistema = ANCHO_VGA;
        alto_sistema = ALTO_VGA;
    }

    gbt_crear_ventana("Tetris", ancho_sistema, alto_sistema, TAM_ESCALA);
}

void dibujar(int pieza[4][4], int pos_x, int pos_y)
{
    gbt_borrar_backbuffer(0); // fondo negro

    int ancho_tablero = COLUMNAS * TAM_CELDA;
    int alto_tablero = (FILAS - 2) * TAM_CELDA;

    /* COMPLEJO: Cálculo de centrado
       Al restarle al ancho de la ventana el ancho del tablero, obtenemos
       el espacio sobrante. Dividirlo por 2 nos da exactamente la coordenada 'x' e 'y'
       donde debemos empezar a dibujar para que el tablero quede en el medio. */
    int margen_x = (ancho_sistema - ancho_tablero) / 2;
    int margen_y = (alto_sistema - alto_tablero) / 2;

    dibujar_rectangulo(margen_x,margen_y,ancho_tablero,alto_tablero,FONDO);
    dibujar_matriz(margen_x, margen_y);
    dibujar_pieza(pieza, pos_x, pos_y, margen_x, margen_y);

    gbt_volcar_backbuffer();
}

void dibujar_cuadrado(int x, int y, int color, int tam)
{
    for (int i = 0; i < tam; i++)
    {
        for (int j = 0; j < tam; j++)
        {
            gbt_dibujar_pixel(x + j, y + i, color);
        }
    }
}

void dibujar_matriz(int ini_x, int ini_y)
{
    /* COMPLEJO: Filas invisibles
       El bucle arranca en fila = 2 porque las filas 0 y 1 son la zona donde
       nacen las piezas (fuera de la pantalla). */
    for (int fila = 2; fila < FILAS; fila++)
    {
        for (int col = 0; col < COLUMNAS; col++)
        {
            int x = ini_x + col * TAM_CELDA;
            /* Se resta 2 a la fila actual para que la fila 2 de la matriz lógica
               se dibuje en la fila 0 de la pantalla física. */
            int y = ini_y + (fila - 2) * TAM_CELDA;

            int color = INTERFAZ;

            if (tablero[fila][col] != 0)
            {
                color = tablero[fila][col];
            }

            dibujar_cuadrado(x, y, color, TAM_CELDA);
        }
    }
}

void dibujar_pieza(int pieza[4][4], int pos_x, int pos_y, int ini_x, int ini_y)
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (pieza[i][j] != 0)
            {
                /* COMPLEJO: Coordenadas cruzadas
                   Aquí está cruzada la nomenclatura: pos_y representa las columnas (eje X)
                   y pos_x representa las filas (eje Y).
                   'j' avanza por las columnas de la pieza, 'i' avanza por las filas. */
                int x = ini_x + (pos_y + j) * TAM_CELDA;
                int y = ini_y + (pos_x + i - 2) * TAM_CELDA; // El -2 oculta la pieza si nace muy arriba

                dibujar_cuadrado(x, y, pieza[i][j], TAM_CELDA);
            }
        }
    }
}

void dibujar_rectangulo(int x, int y, int ancho, int alto, int color)
{
    for (int i = 0; i < alto; i++)
    {
        for (int j = 0; j < ancho; j++)
        {
            gbt_dibujar_pixel(x + j, y + i, color);
        }
    }
}
