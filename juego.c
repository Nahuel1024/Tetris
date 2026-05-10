/**
 * @file juego.c
 * @brief Implementación de las mecánicas de juego, colisiones y spawn.
 */

#include "juego.h"
#include <stdlib.h> // Para rand() y system()
#include <stdio.h>  // Para printf()

/* ========================================================================== */
/* SECCIÓN: FÍSICAS Y COLISIONES                                              */
/* ========================================================================== */

/**
 * COMPLEJO: Detección de Colisión (Look-ahead)
 * Comprobamos el "suelo" evaluando el estado de la matriz en (fila + 1).
 * Si se alcanza el límite inferior de la matriz (CANTIDAD_FILAS - 1), o si
 * la celda directamente debajo está ocupada, se detecta el impacto.
 */
bool mino_sobre_suelo(const t_tablero *tablero, const t_mino *mino)
{
    return (
        (mino->coordenadas.fila == CANTIDAD_FILAS - 1) ||
        (tablero->celda[mino->coordenadas.fila + 1][mino->coordenadas.columna].ocupado)
    );
}

/**
 * COMPLEJO: Leyes de De Morgan Aplicadas a Físicas
 * La pieza se considera en estado de "caída" SOLO SI NINGUNO de sus 4 minos
 * ha detectado el suelo. Al usar el operador lógico AND (&&) entre negaciones (!),
 * garantizamos que si un solo bloque toca algo, la estructura completa se detenga.
 */
bool tetromino_cayendo(const t_tablero *tablero, const t_tetromino *tetromino)
{
    return (
        (!mino_sobre_suelo(tablero, &tetromino->mino_a)) &&
        (!mino_sobre_suelo(tablero, &tetromino->mino_b)) &&
        (!mino_sobre_suelo(tablero, &tetromino->mino_c)) &&
        (!mino_sobre_suelo(tablero, &tetromino->mino_d))
    );
}

/* ========================================================================== */
/* SECCIÓN: GESTIÓN DE ESTADO Y SPAWN                                         */
/* ========================================================================== */

void mino_fijar(t_tablero *tablero, const t_mino *mino)
{
    tablero->celda[mino->coordenadas.fila][mino->coordenadas.columna].ocupado = true;
    tablero->celda[mino->coordenadas.fila][mino->coordenadas.columna].caracter = '#';
    tablero->celda[mino->coordenadas.fila][mino->coordenadas.columna].color = mino->color;
}

void tablero_actualizar(t_tablero *tablero, const t_tetromino *tetromino)
{
    mino_fijar(tablero, &tetromino->mino_a);
    mino_fijar(tablero, &tetromino->mino_b);
    mino_fijar(tablero, &tetromino->mino_c);
    mino_fijar(tablero, &tetromino->mino_d);
}

/**
 * COMPLEJO: Mapeo Geométrico de Nacimiento
 * Las piezas se construyen dinámicamente en las filas 0 y 1. Se calcula
 * el 'centro' del tablero para posicionarlas simétricamente sin importar
 * la resolución. Se asigna la base de la pieza a la fila inferior (1) y
 * la punta a la fila superior (0) para facilitar futuras rotaciones.
 */
bool tetromino_insertar(t_tablero *tablero, t_tetromino *tetromino)
{
    if(!buffer_libre(tablero))
    {
        tablero->game_over = true;
        return false;
    }

    size_t subindice_tetromino = rand() % 7;
    unsigned centro = tablero->dimensiones.ancho / 2;

    switch(subindice_tetromino)
    {
    case I:
        tetromino->mino_a.coordenadas.fila = 1; tetromino->mino_a.coordenadas.columna = centro - 1;
        tetromino->mino_b.coordenadas.fila = 1; tetromino->mino_b.coordenadas.columna = centro;
        tetromino->mino_c.coordenadas.fila = 1; tetromino->mino_c.coordenadas.columna = centro + 1;
        tetromino->mino_d.coordenadas.fila = 1; tetromino->mino_d.coordenadas.columna = centro + 2;
        break;
    case O:
        tetromino->mino_a.coordenadas.fila = 0; tetromino->mino_a.coordenadas.columna = centro - 1;
        tetromino->mino_b.coordenadas.fila = 0; tetromino->mino_b.coordenadas.columna = centro;
        tetromino->mino_c.coordenadas.fila = 1; tetromino->mino_c.coordenadas.columna = centro - 1;
        tetromino->mino_d.coordenadas.fila = 1; tetromino->mino_d.coordenadas.columna = centro;
        break;
    case T:
        tetromino->mino_a.coordenadas.fila = 0; tetromino->mino_a.coordenadas.columna = centro;
        tetromino->mino_b.coordenadas.fila = 1; tetromino->mino_b.coordenadas.columna = centro - 1;
        tetromino->mino_c.coordenadas.fila = 1; tetromino->mino_c.coordenadas.columna = centro;
        tetromino->mino_d.coordenadas.fila = 1; tetromino->mino_d.coordenadas.columna = centro + 1;
        break;
    case S:
        tetromino->mino_a.coordenadas.fila = 0; tetromino->mino_a.coordenadas.columna = centro;
        tetromino->mino_b.coordenadas.fila = 0; tetromino->mino_b.coordenadas.columna = centro + 1;
        tetromino->mino_c.coordenadas.fila = 1; tetromino->mino_c.coordenadas.columna = centro - 1;
        tetromino->mino_d.coordenadas.fila = 1; tetromino->mino_d.coordenadas.columna = centro;
        break;
    case L:
        tetromino->mino_a.coordenadas.fila = 0; tetromino->mino_a.coordenadas.columna = centro + 1;
        tetromino->mino_b.coordenadas.fila = 1; tetromino->mino_b.coordenadas.columna = centro - 1;
        tetromino->mino_c.coordenadas.fila = 1; tetromino->mino_c.coordenadas.columna = centro;
        tetromino->mino_d.coordenadas.fila = 1; tetromino->mino_d.coordenadas.columna = centro + 1;
        break;
    case J:
        tetromino->mino_a.coordenadas.fila = 0; tetromino->mino_a.coordenadas.columna = centro - 1;
        tetromino->mino_b.coordenadas.fila = 1; tetromino->mino_b.coordenadas.columna = centro - 1;
        tetromino->mino_c.coordenadas.fila = 1; tetromino->mino_c.coordenadas.columna = centro;
        tetromino->mino_d.coordenadas.fila = 1; tetromino->mino_d.coordenadas.columna = centro + 1;
        break;
    case Z:
        tetromino->mino_a.coordenadas.fila = 0; tetromino->mino_a.coordenadas.columna = centro - 1;
        tetromino->mino_b.coordenadas.fila = 0; tetromino->mino_b.coordenadas.columna = centro;
        tetromino->mino_c.coordenadas.fila = 1; tetromino->mino_c.coordenadas.columna = centro;
        tetromino->mino_d.coordenadas.fila = 1; tetromino->mino_d.coordenadas.columna = centro + 1;
        break;
    }

    tetromino->mino_a.color = subindice_tetromino;
    tetromino->mino_b.color = subindice_tetromino;
    tetromino->mino_c.color = subindice_tetromino;
    tetromino->mino_d.color = subindice_tetromino;

    return true;
}

/* ========================================================================== */
/* SECCIÓN: RENDERIZADO POR CONSOLA (DEBUG)                                   */
/* ========================================================================== */

/**
 * COMPLEJO: Jerarquía de Dibujado Visual
 * Para generar el frame por consola sin parpadeos severos, limpiamos pantalla (cls).
 * La prioridad de pintado es estricta:
 * 1º Pieza activa superpuesta.
 * 2º Caracter de vacío (si no está ocupado).
 * 3º Bloque ya fijado en la matriz.
 */
void tablero_mostrar(const t_tablero *tablero, const t_tetromino *tetromino)
{
    system("cls");
    t_coordenadas coordenadas_matriz;

    printf("   <!");
    for(int j = 0; j < CANTIDAD_COLUMNAS; j++) printf("===");
    printf("!>\n");

    for(int i = 2; i < CANTIDAD_FILAS; i++)
    {
        printf("[%d]<!", i - 2);
        for(int j = 0; j < CANTIDAD_COLUMNAS; j++)
        {
            coordenadas_inicializar(&coordenadas_matriz, i, j);

            if(es_mino(&coordenadas_matriz, tetromino))
            {
                printf("[#]");
            }
            else if(!tablero->celda[i][j].ocupado)
            {
                printf(" %c ", tablero->celda[i][j].caracter);
            }
            else
            {
                printf("[%c]", tablero->celda[i][j].caracter);
            }
        }
        printf("!>\n");
    }

    printf("   <!");
    for(int j = 0; j < CANTIDAD_COLUMNAS; j++) printf("===");
    printf("!>\n\n");
}
