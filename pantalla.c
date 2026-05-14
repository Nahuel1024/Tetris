#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "GBT/gbt.h"
#include "GBT/gbt_graficos.h"
#include "pantalla.h"
#include "paletacolor.h"

//#define TAM_CELDA 10 //cuantos pixeles ocupa cada celda

int tablero[FILAS][COLUMNAS] = {0};
int ancho_sistema;
int alto_sistema;
int ancho_tablero = COLUMNAS * TAM_CELDA;
int alto_tablero  = (FILAS-2)* TAM_CELDA; // solo 20 visibles

void iniciar_pantalla(int reso)  //Dibuja la pantalla
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
void dibujar(int pieza[4][4], int pos_x, int pos_y) //LE MANDAMOS LA PIEZA, Y LA POSICION QUE QUEREMOS esta posicion tiene que ser siempre la misma creo que tiene que ser  0 0, 0 1.
{
    gbt_borrar_backbuffer(0); // fondo negro        //pos_x se refiere a la fila y pos_y se refiere a las columnas

    int ancho_tablero = COLUMNAS * TAM_CELDA;
    int alto_tablero = (FILAS-2) * TAM_CELDA;

    int centro_x = (ancho_sistema - ancho_tablero) / 2;  //Calculamos el centro de la ventana
    int centro_y = (alto_sistema - alto_tablero) / 2;

    dibujar_rectangulo(centro_x,centro_y,ancho_tablero,alto_tablero,2);
    dibujar_matriz(centro_x, centro_y);
    dibujar_pieza(pieza, pos_x, pos_y, centro_x, centro_y);
    gbt_volcar_backbuffer();// Vuelca los píxeles del backbuffer en la ventana.

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
    for (int fila = 2; fila < FILAS; fila++) // Las FILAS ARRANCAN EN 2 PORQUE LAS 2 PRIMERAS SON INVISIBLES
    {
        for (int col = 0; col < COLUMNAS; col++)
        {
            int x = ini_x + col * TAM_CELDA;
            int y = ini_y + (FILAS - 2) * TAM_CELDA; // RESTAMOS A FILAS 2 YA QUE 2 SON INVISIBLES

            int color = INTERFAZ;

            if (tablero[fila][col] != 0)
            {
                color = tablero[fila][col];
            }

            dibujar_cuadrado(x, y, color, TAM_CELDA);
        }
    }
}
void dibujar_pieza(int pieza[4][4], int pos_x, int pos_y, int ini_x, int ini_y) //DIBUJA TETROMINO
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (pieza[i][j] != 0)  // RECORRE LA MATRIZ, SI ES DISTINTO DE 0 EL CONTENIDO
            {
                int x = ini_x + (pos_y + j) * TAM_CELDA; // ini_x es el centro del tablero, a la posicion del tablero, pos_y le suma la columna dentro de la pieza.
                int y = ini_y + (pos_x + i - 2) * TAM_CELDA; // misma logica que lo de arriba pero con x, y le restamos -2 por las filas invisibles

                dibujar_cuadrado(x, y, pieza[i][j], TAM_CELDA); //Dibuja el tetrominio en esta nueva pos.
            }
        }
    }
}
void dibujar_rectangulo(int x, int y, int ancho, int alto, int color) // centro_x/ contro_y/ ancho_tablero/ alto_tablero/ fondo
{
    for (int i = 0; i < alto; i++)
    {
        for (int j = 0; j < ancho; j++)
        {

            gbt_dibujar_pixel(x + j, y + i, color); //Esta dibujando el fondo rectangular del tablero
        }
    }
}
// esta dibujando pixel por pixel.
