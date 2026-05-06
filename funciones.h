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
#include "tetromino.h"

/* --- Configuraciones del Juego --- */
#define CANTIDAD_FILAS 12
#define CANTIDAD_COLUMNAS 10
#define TIEMPO_ESPERA 500  // Milisegundos entre caídas
#define CANTIDAD_MINOS 4   // Cantidad de bloques por tetromino

/* --- Códigos de Retorno --- */
#define OK 0

/* --- Estructuras de Datos --- */

/**
 * @brief Representa una unidad mínima en el tablero.
 */
typedef struct {
    char caracter;   ///< Símbolo visual (ej: 'X' o '.')
    bool ocupado;    ///< Estado de la celda (true = bloque fijo)
} t_celda;

typedef struct {
    size_t ancho;
    size_t alto;
} t_dimensiones;

/**
 * @brief Matriz de juego que contiene solo las piezas ya fijadas.
 */
typedef struct {
    t_dimensiones dimensiones;
    t_celda celda[CANTIDAD_FILAS][CANTIDAD_COLUMNAS];
    bool game_over;
    bool actualizar; ///< (¡No implementado!) Flag para forzar el redibujado cuando hay movimiento
} t_tablero;

/**
 * @brief Representa un punto en el plano cartesiano del tablero.
 */
typedef struct {
    unsigned x; ///< Corresponde al subindice de una fila.
    unsigned y; ///< Corresponde al subindice de una columna.
} t_coordenadas;

/**
 * @brief Define la pieza activa compuesta por 4 minos independientes (tetromino en caída).
 */
typedef struct {
    t_coordenadas mino_a;
    t_coordenadas mino_b;
    t_coordenadas mino_c;
    t_coordenadas mino_d;
} t_tetromino;

/* --- Prototipos de Funciones --- */

/**
 * @brief Limpia el tablero y lo setea con caracteres de fondo.
 */
void tablero_inicializar(t_tablero *tablero, size_t cantidad_filas, size_t cantidad_columnas);

/**
 * @brief Verifica si una coordenada específica del tablero coincide con
 * la posición de algún mino del tetromino actual.
 * @return true si la celda debe pintarse como parte de la pieza activa.
 */
bool es_mino(const t_coordenadas *celda, const t_tetromino *tetromino);

/**
 * @brief Helper para asignar valores X e Y de forma rápida.
 */
void coordenadas_inicializar(t_coordenadas *coordenadas, unsigned x, unsigned y);

/**
 * @brief Renderiza en consola el tablero y superpone la pieza en caída.
 * @param tablero Puntero al estado fijo del juego.
 * @param tetromino Puntero a la pieza que se está moviendo.
 */
void tablero_mostrar(const t_tablero *tablero, const t_tetromino *tetromino);

/**
 * @brief Genera o coloca un nuevo tetromino en la parte superior del tablero.
 */
bool buffer_libre(const t_tablero *tablero);
void tetromino_insertar_coordenadas(t_tetromino *tetromino, size_t subindice_tetromino);
bool tetromino_insertar(t_tablero *tablero, t_tetromino *tetromino);

/**
 * @brief Aplica el desplazamiento vertical (caída) a un solo mino.
 */
void mino_desplazar(t_coordenadas *mino);

/**
 * @brief Aplica el desplazamiento vertical (caída) a los 4 minos del tetromino activo.
 */
void tetromino_desplazar(t_tetromino *tetromino);

bool mino_sobre_suelo(const t_tablero *tablero, const t_coordenadas *mino);
bool tetromino_cayendo(const t_tablero *tablero, const t_tetromino *tetromino);
void mino_fijar(t_tablero *tablero, const t_coordenadas *mino);
void tablero_actualizar(t_tablero *tablero, const t_tetromino *tetromino);
bool game_over(const t_tablero *tablero);

#endif // TETRIS_H_INCLUDED
