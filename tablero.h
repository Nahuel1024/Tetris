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
    t_dimensiones dimensiones;                          ///< Ancho y alto actual
    t_celda celda[CANTIDAD_FILAS][CANTIDAD_COLUMNAS];   ///< Grilla de celdas
    bool game_over;                                     ///< Estado de la partida
    unsigned fila_cuspide;                              ///< Fila más alta
    bool actualizar;                                    ///< Flag para forzar redibujado
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
 * @brief Verifica si unas coordenadas se encuentran dentro del tablero
 */
bool coordenadas_dentro_del_tablero(const t_tablero *tablero, const t_coordenadas *coordenadas);

/**
 * @brief Verifica si el tablero tiene una casilla libre en las coordenadas dadas
 */
bool coordenadas_libres(const t_tablero *tablero, const t_coordenadas *coordenadas);

/**
 * @brief Devuelve la fila con el mino más alto
 */
void tablero_actualizar_fila_cuspide(t_tablero * tablero);

/**
 * @brief Copia en la fila_destino la fila_fuente
 */
void desplazar_filas(t_tablero *tablero, t_celda *fila_destino, t_celda *fila_fuente);

/**
 * @brief Elimina una fila del tablero, haciendo que las filas que están por encima se acomoden
 */
void tablero_eliminar_fila(t_tablero *tablero, unsigned fila);

/**
 * @brief Revisa el tablero buscando filas completas, devuelve el numero de filas encontradas
 */
unsigned tablero_revisar_filas_completas(t_tablero * tablero);

/**
 * @brief Verifica si las filas de spawn están libres para una nueva pieza.
 */
bool buffer_libre(const t_tablero *tablero);

/**
 * @brief Consulta el estado de finalización del juego.
 */
bool game_over(const t_tablero *tablero);

#endif // TABLERO_H_INCLUDED
