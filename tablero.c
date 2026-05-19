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

bool coordenadas_dentro_del_tablero(const t_tablero *tablero, const t_coordenadas *coordenadas)
{
    return (
        (coordenadas->fila >= 0) &&
        (coordenadas->fila < tablero->dimensiones.alto) &&
        (coordenadas->columna >= 0) &&
        (coordenadas->columna < tablero->dimensiones.ancho)
    );
}

bool coordenadas_libres(const t_tablero *tablero, const t_coordenadas *coordenadas)
{
    return !(tablero->celda[coordenadas->fila][coordenadas->columna].ocupado);
}

void tablero_actualizar_fila_cuspide(t_tablero * tablero)
{
    unsigned fila = 2, fila_cuspide = 0, columna;

    while(fila < tablero->dimensiones.alto && fila_cuspide == 0)
    {
        columna = 0;
        while(columna < tablero->dimensiones.ancho && fila_cuspide == 0)
        {
            if(tablero->celda[fila][columna].ocupado)
                fila_cuspide = fila;
            columna++;
        }
        fila++;
    }

    tablero->fila_cuspide = fila_cuspide;
}

void tablero_inicializar_fila(t_tablero *tablero, t_celda *fila)
{
    t_celda *puntero_celda = NULL,
            *ultima_celda = fila + tablero->dimensiones.ancho - 1;

    unsigned numero_fila = fila - (*tablero->celda);
    for(puntero_celda = fila; puntero_celda <= ultima_celda; puntero_celda++)
    {
        puntero_celda->caracter = '.';
        puntero_celda->color = INTERFAZ;
        puntero_celda->coordenadas.fila = numero_fila;
        puntero_celda->coordenadas.columna = puntero_celda - fila;
        puntero_celda->ocupado = false;
    }
}

void desplazar_filas(t_tablero *tablero, t_celda *fila_destino, t_celda *fila_fuente)
{
    size_t tamanio_fila = tablero->dimensiones.ancho * sizeof(t_celda);
    memcpy(fila_destino, fila_fuente, tamanio_fila);
}

void tablero_eliminar_fila(t_tablero *tablero, unsigned fila)
{
    int i;
    for(i = fila; i > tablero->fila_cuspide; i--)
    {
        desplazar_filas(tablero ,tablero->celda[i], tablero->celda[i - 1]);
    }
    tablero_inicializar_fila(tablero, tablero->celda[i]);
}

unsigned tablero_revisar_filas_completas(t_tablero * tablero)
{
    unsigned filas_encontradas = 0, columna;
    for(unsigned fila = 0; fila < tablero->dimensiones.alto; fila++)
    {
        columna = 0;
        while(tablero->celda[fila][columna].ocupado && columna < tablero->dimensiones.ancho)
        {
            columna++;
        }
        if(columna == tablero->dimensiones.ancho)
        {
            filas_encontradas++;
            tablero_eliminar_fila(tablero, fila);
        }
    }
    return filas_encontradas;
}


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
