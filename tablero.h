/**
 * @file tablero.h
 * @brief Definición de la estructura del tablero y sus funciones de gestión.
 * @version 1.2
 */

#ifndef TABLERO_H_INCLUDED
#define TABLERO_H_INCLUDED

#include "paletacolor.h"
#include "tetromino.h"
#include "comun.h"

/* ========================================================================== */
/* ESTRUCTURAS DE DATOS                                                       */
/* ========================================================================== */

/**
 * @brief Representa una unidad mínima en el tablero.
 */
typedef struct {
    t_coordenadas coordenadas; ///< Ubicación física en la matriz
    char caracter;             ///< Símbolo visual (ej: 'X' o '.')
    int color;                 ///< Índice de color para el renderizado
    bool ocupado;              ///< Estado de la celda (true = bloque fijo)
} t_celda;

/**
 * @brief Matriz de juego que contiene solo las piezas ya fijadas.
 */
typedef struct {
    t_dimensiones dimensiones;                       ///< Ancho y alto actual
    t_celda celda[CANTIDAD_FILAS][CANTIDAD_COLUMNAS]; ///< Grilla de celdas
    bool game_over;                                  ///< Estado de la partida
    bool actualizar;                                 ///< Flag para forzar redibujado
} t_tablero;

/* ========================================================================== */
/* PROTOTIPOS DE FUNCIONES                                                    */
/* ========================================================================== */

/* --- Ciclo de Vida y Gestión --- */

/**
 * @brief Limpia el tablero y lo setea con caracteres de fondo.
 */
void tablero_inicializar(t_tablero *tablero, size_t cantidad_filas, size_t cantidad_columnas);

/**
 * @brief Verifica si las filas de spawn están libres para una nueva pieza.
 */
bool buffer_libre(const t_tablero *tablero);

/**
 * @brief Consulta el estado de finalización del juego.
 */
bool game_over(const t_tablero *tablero);

#endif // TABLERO_H_INCLUDED
