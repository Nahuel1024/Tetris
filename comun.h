#ifndef COMUN_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

#define COMUN_H_INCLUDED

/**
 * @brief Representa un punto en el plano cartesiano del tablero.
 */
typedef struct {
    unsigned fila; ///< Corresponde al subindice de una fila.
    unsigned columna; ///< Corresponde al subindice de una columna.
} t_coordenadas;

/**
 * @brief Representa las dimensiones del tablero.
 */
typedef struct {
    size_t ancho;
    size_t alto;
} t_dimensiones;

/**
 * @brief Helper para asignar valores X e Y de forma rápida.
 */
void coordenadas_inicializar(t_coordenadas *coordenadas, unsigned x, unsigned y);

#endif // COMUN_H_INCLUDED
