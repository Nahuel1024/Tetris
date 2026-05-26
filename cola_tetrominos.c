/**
 * @file cola_tetrominos.c
 * @brief Implementacion del TDA Cola de Tetrominos.
 */

#include "cola_tetrominos.h"
#include "juego.h"
#include <stdlib.h>

/* ========================================================================== */
/* HELPER INTERNO: GENERACION DE TETROMINO SIN SPAWN                         */
/* ========================================================================== */

/**
 * @brief Genera forma y color de un tetromino aleatorio sin posicionarlo
 *        en el tablero.
 *
 * Las coordenadas quedan en cero ya que este tetromino es solo para preview.
 * Cuando pase a ser el activo, cola_tetrominos_avanzar() lo posicionara
 * correctamente en el area de spawn via tetromino_insertar().
 *
 * @param tetromino  Tetromino a inicializar.
 */
static void tetromino_generar(t_tetromino *tetromino)
{
    size_t tipo = rand() % 7;

    /// Coordenadas en cero: este tetromino es solo preview, no esta en el tablero
    for(int i = 0; i < CANTIDAD_MINOS; i++)
    {
        tetromino->mino[i].coordenadas.fila    = 0;
        tetromino->mino[i].coordenadas.columna = 0;
        tetromino->mino[i].color               = (unsigned)tipo;
    }

    switch(tipo)
    {
        case I: tetromino->pieza = 'I'; break;
        case O: tetromino->pieza = 'O'; break;
        case T: tetromino->pieza = 'T'; break;
        case S: tetromino->pieza = 'S'; break;
        case L: tetromino->pieza = 'L'; break;
        case J: tetromino->pieza = 'J'; break;
        case Z: tetromino->pieza = 'Z'; break;
    }
}

/* ========================================================================== */
/* IMPLEMENTACION DEL TDA                                                     */
/* ========================================================================== */

void cola_tetrominos_inicializar(t_cola_tetrominos *cola, t_tablero *tablero)
{
    gbt_vector_crear(&cola->vector, sizeof(t_tetromino));

    /// Posicion 0: tetromino activo, posicionado en el area de spawn
    t_tetromino actual;
    tetromino_insertar(tablero, &actual);
    gbt_vector_insertar_al_final(&cola->vector, &actual);

    /// Posicion 1: tetromino siguiente, solo forma y color para el preview
    t_tetromino siguiente;
    tetromino_generar(&siguiente);
    gbt_vector_insertar_al_final(&cola->vector, &siguiente);
}

t_tetromino* cola_tetrominos_actual(t_cola_tetrominos *cola)
{
    return (t_tetromino*)cola->vector.vec;
}

t_tetromino* cola_tetrominos_siguiente(t_cola_tetrominos *cola)
{
    return (t_tetromino*)cola->vector.vec + 1;
}

bool cola_tetrominos_avanzar(t_cola_tetrominos *cola, t_tablero *tablero)
{
    /// El siguiente pasa a ser el activo copiandolo en posicion 0
    t_tetromino *actual    = cola_tetrominos_actual(cola);
    t_tetromino *siguiente = cola_tetrominos_siguiente(cola);
    *actual = *siguiente;

    /// Posicionamos el nuevo activo en el area de spawn del tablero.
    /// tetromino_insertar() sobrescribe coordenadas pero respeta pieza y color
    /// si los seteamos antes. Como queremos un nuevo aleatorio, lo llamamos
    /// directamente y dejamos que elija el tipo.
    if(!tetromino_insertar(tablero, actual))
        return false;   ///< Area de spawn ocupada: game over

    /// Generamos un nuevo tetromino siguiente (solo preview)
    tetromino_generar(siguiente);

    return true;
}

void cola_tetrominos_destruir(t_cola_tetrominos *cola)
{
    gbt_vector_destruir(&cola->vector);
}
