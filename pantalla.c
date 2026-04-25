#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "GBT/gbt.h"
#include "GBT/gbt_graficos.h"
#include "GBT/gbt_temporizador.h"
#include "pantalla.h"
#include "funciones.h"
#define FILAS 20
#define COLUMNAS 10
#define TAM_CELDA 10
#define TAM 200



int tablero[FILAS][COLUMNAS];
int ancho_ventana = COLUMNAS * TAM_CELDA;
int alto_ventana  = FILAS * TAM_CELDA;
void iniciar_pantalla(int reso)
{
  if(reso == 0)
  {
    gbt_crear_ventana("Tetris %dx%d",ANCHO_CGA,ALTO_CGA,TAM_ESCALA);
  }
  else
  {
    gbt_crear_ventana("Tetris",ANCHO_VGA,ALTO_VGA,TAM_ESCALA);
  }
}
void dibujar()
{
    gbt_borrar_backbuffer(0);

   int offset_x = (ANCHO_CGA - ancho_ventana) / 2;
   int offset_y = (ALTO_CGA - alto_ventana) / 2;

    for(int fila = 0; fila < FILAS; fila++)
    {
        for(int col = 0; col < COLUMNAS; col++)
        {
            int x = offset_x + col * TAM_CELDA;
            int y = offset_y + fila * TAM_CELDA;

            for(int i = 0; i < TAM_CELDA; i++)
                for(int j = 0; j < TAM_CELDA; j++)
                    gbt_dibujar_pixel(x + i, y + j, 1);
        }
    }

    gbt_volcar_backbuffer();
};
