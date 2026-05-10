/**
 * @file funciones.h
 * @author CURSOR
 * @brief Motor lógico y de renderizado para Proyecto Tetris en C.
 * @version 1.1
 * @date 2026
 * * @note Esta versión del juego solo muestra la caida constante de un tetromino.
 */

#ifndef TETRIS_H_INCLUDED
#define TETRIS_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <windows.h> // Incluye la función Sleep(), usada para determinar la velocidad del tetromino
#include "GBT/gbt.h"
#include "pantalla.h"
#include "paletacolor.h"
#include "tetromino.h"

/* --- Códigos de Retorno --- */

/* --- Configuraciones del Juego --- */
/*
#define CANTIDAD_FILAS 12
#define CANTIDAD_COLUMNAS 10
#define TIEMPO_ESPERA 500  // Milisegundos entre caídas
#define CANTIDAD_MINOS 4   // Cantidad de bloques por tetromino
*/
/* --- Estructuras de Datos --- */

/**
 * @brief Representa una unidad mínima en el tablero.
 */
/*
typedef struct {
    char caracter;   ///< Símbolo visual (ej: 'X' o '.')
    bool ocupado;    ///< Estado de la celda (true = bloque fijo)
} t_celda;

typedef struct {
    size_t ancho;
    size_t alto;
} t_dimensiones;
*/
/**
 * @brief Matriz de juego que contiene solo las piezas ya fijadas.
 */
/*
typedef struct {
    t_dimensiones dimensiones;
    t_celda celda[CANTIDAD_FILAS][CANTIDAD_COLUMNAS];
    bool game_over;
    bool actualizar; ///< (¡No implementado!) Flag para forzar el redibujado cuando hay movimiento
} t_tablero;
*/
/**
 * @brief Representa un punto en el plano cartesiano del tablero.
 */
/*
typedef struct {
    unsigned fila; ///< Corresponde al subindice de una fila.
    unsigned columna; ///< Corresponde al subindice de una columna.
    unsigned color;
} t_mino;
*/
/**
 * @brief Define la pieza activa compuesta por 4 minos independientes (tetromino en caída).
 */
/*
typedef struct {
    t_mino mino_a;
    t_mino mino_b;
    t_mino mino_c;
    t_mino mino_d;
} t_tetromino;
*/
/* --- Prototipos de Funciones --- */












#endif // TETRIS_H_INCLUDED
