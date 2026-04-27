#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "GBT/gbt.h"
#include "GBT/gbt_graficos.h"
#include "GBT/gbt_temporizador.h"
#include "pantalla.h"
#include "funciones.h"
#include "paletacolor.h"
#define FILAS 20
#define COLUMNAS 10
#define TAM_CELDA 10
#define TAM 200
int tablero[FILAS][COLUMNAS];
int ancho_tablero = COLUMNAS * TAM_CELDA;
int alto_tablero  = FILAS * TAM_CELDA;
int ancho_sistema = ANCHO_VGA;
int alto_sistema = ALTO_VGA;
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
void dibujar() //Dibuja un cuadrado en el medio de pantalla, del color asignado en gbt_dibujar_pixel()
{
    gbt_borrar_backbuffer(0);

   int offset_x = (ancho_sistema - ancho_tablero) / 2;
   int offset_y = (alto_sistema - alto_tablero) / 2;

    for(int fila = 0; fila < FILAS; fila++)
    {
        for(int col = 0; col < COLUMNAS; col++)
        {
            int x = offset_x + col * TAM_CELDA;
            int y = offset_y + fila * TAM_CELDA;

            for(int i = 0; i < TAM_CELDA; i++)
                for(int j = 0; j < TAM_CELDA; j++)
                    gbt_dibujar_pixel(x + i, y + j, INTERFAZ); //El color es el del FONDO
        }
    }

    gbt_volcar_backbuffer();
};
