/**
 * @file tablero.c
 * @brief Implementación de las funciones de lógica y estado del tablero.
 */

#include "tablero.h"

/* ========================================================================== */
/* SECCIÓN: INICIALIZACIÓN                                                    */
/* ========================================================================== */

/**
 * COMPLEJO: Inicialización por Zonas
 * El tablero se divide visualmente mediante colores:
 * 1. Zona de Spawn (filas 0 y 1): Utiliza el color FONDO.
 * 2. Zona de Juego (filas 2 en adelante): Utiliza el color INTERFAZ.
 * Además, se asignan las coordenadas lógicas a cada celda para facilitar
 * las búsquedas posteriores.
 */
void tablero_inicializar(t_tablero *tablero, size_t cantidad_filas, size_t cantidad_columnas)
{
    for(int i = 0; i < cantidad_filas; i++)
    {
        for(int j = 0; j < cantidad_columnas; j++)
        {
            tablero->celda[i][j].coordenadas.fila = i;
            tablero->celda[i][j].coordenadas.columna = j;
            tablero->celda[i][j].caracter = '.';
            tablero->celda[i][j].ocupado = false;

            if(i == 0 || i == 1)
                tablero->celda[i][j].color = FONDO;
            else
                tablero->celda[i][j].color = INTERFAZ;
        }
    }
    tablero->dimensiones.ancho = cantidad_columnas;
    tablero->dimensiones.alto = cantidad_filas;
    tablero->game_over = false;
}

/* ========================================================================== */
/* SECCIÓN: VALIDACIONES Y ESTADO                                             */
/* ========================================================================== */

bool buffer_libre(const t_tablero *tablero)
{
    // Revisa exhaustivamente las primeras dos filas para detectar colisiones de spawn
    return (
        (!tablero->celda[0][0].ocupado) && (!tablero->celda[0][1].ocupado) &&
        (!tablero->celda[0][2].ocupado) && (!tablero->celda[0][3].ocupado) &&
        (!tablero->celda[0][4].ocupado) && (!tablero->celda[0][5].ocupado) &&
        (!tablero->celda[0][6].ocupado) && (!tablero->celda[0][7].ocupado) &&
        (!tablero->celda[0][8].ocupado) && (!tablero->celda[0][9].ocupado) &&

        (!tablero->celda[1][0].ocupado) && (!tablero->celda[1][1].ocupado) &&
        (!tablero->celda[1][2].ocupado) && (!tablero->celda[1][3].ocupado) &&
        (!tablero->celda[1][4].ocupado) && (!tablero->celda[1][5].ocupado) &&
        (!tablero->celda[1][6].ocupado) && (!tablero->celda[1][7].ocupado) &&
        (!tablero->celda[1][8].ocupado) && (!tablero->celda[1][9].ocupado)
    );
}

bool game_over(const t_tablero *tablero)
{
    return tablero->game_over;
}
