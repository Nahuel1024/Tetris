/**
 * @file funciones.c
 * @brief Implementación de la lógica de movimiento y renderizado del Tetris.
 */

#include "funciones.h"

/* -------------------------------------------------------------------------- */
/* GESTIÓN DEL TABLERO                               */
/* -------------------------------------------------------------------------- */

void tablero_inicializar(t_tablero *tablero)
{
    for(int i = 0; i < FILAS; i++)
    {
        for(int j = 0; j < COLUMNAS; j++)
        {
            tablero->celda[i][j].caracter = '.';
            tablero->celda[i][j].ocupado = false;
        }
    }
    tablero->game_over = false;
}

void tablero_mostrar(const t_tablero *tablero, const t_tetromino *tetromino)
{
    system("cls");
    t_coordenadas coordenadas_matriz;

    // Borde superior
    printf("   <!");
    for(int j = 0; j < COLUMNAS; j++) printf("===");
    printf("!>\n");

    // Cuerpo del tablero (se ocultan las filas 0 y 1 para el spawn)
    for(int i = 2; i < FILAS; i++)
    {
        printf("[%d]<!",i-2);
        for(int j = 0; j < COLUMNAS; j++)
        {
            coordenadas_inicializar(&coordenadas_matriz, i, j);

            if(es_mino(&coordenadas_matriz, tetromino))
            {
                printf("[#]"); // Pieza activa
            }
            else if(!tablero->celda[i][j].ocupado)
            {
                printf(" %c ", tablero->celda[i][j].caracter); // Vacío
            }
            else
            {
                printf("[%c]", tablero->celda[i][j].caracter); // Pieza fija
            }
        }
        printf("!>\n");
    }

    // Borde inferior
    printf("   <!");
    for(int j = 0; j < COLUMNAS; j++) printf("===");
    printf("!>\n\n");
}

/* -------------------------------------------------------------------------- */
/* LÓGICA DE TETROMINOS                              */
/* -------------------------------------------------------------------------- */

bool buffer_libre(const t_tablero *tablero)
{
    return (
        (!tablero->celda[0][4].ocupado) &&
        (!tablero->celda[0][5].ocupado) &&
        (!tablero->celda[1][5].ocupado) &&
        (!tablero->celda[1][6].ocupado)
    );
}


bool tetromino_insertar(t_tablero *tablero, t_tetromino *tetromino)
{
    if(!buffer_libre(tablero))
    {
        tablero->game_over = true;
        return false;
    }
    // Posiciona un tetromino inicial (Forma de 'S' por ejemplo)
    coordenadas_inicializar(&tetromino->mino_a, 0, 4);
    coordenadas_inicializar(&tetromino->mino_b, 0, 5);
    coordenadas_inicializar(&tetromino->mino_c, 1, 5);
    coordenadas_inicializar(&tetromino->mino_d, 1, 6);
    return true;
}

void tetromino_desplazar(t_tetromino *tetromino)
{
    mino_desplazar(&tetromino->mino_a);
    mino_desplazar(&tetromino->mino_b);
    mino_desplazar(&tetromino->mino_c);
    mino_desplazar(&tetromino->mino_d);
}

/* -------------------------------------------------------------------------- */
/* FUNCIONES AUXILIARES                              */
/* -------------------------------------------------------------------------- */

void coordenadas_inicializar(t_coordenadas *coordenadas, unsigned x, unsigned y)
{
    coordenadas->x = x;
    coordenadas->y = y;
}

bool es_mino(const t_coordenadas *celda, const t_tetromino *tetromino)
{
    return (celda->x == tetromino->mino_a.x && celda->y == tetromino->mino_a.y) ||
           (celda->x == tetromino->mino_b.x && celda->y == tetromino->mino_b.y) ||
           (celda->x == tetromino->mino_c.x && celda->y == tetromino->mino_c.y) ||
           (celda->x == tetromino->mino_d.x && celda->y == tetromino->mino_d.y);
}

void mino_desplazar(t_coordenadas *mino)
{
    if(mino->x == FILAS - 1)
        mino->x = 2; // Reinicia al tope visible
    else
        mino->x++;
}

bool mino_sobre_suelo(const t_tablero *tablero, const t_coordenadas *mino)
{
    return (
        (mino->x == FILAS - 1) ||
        (tablero->celda[mino->x + 1][mino->y].ocupado)
    );
}

bool tetromino_cayendo(const t_tablero *tablero, const t_tetromino *tetromino)
{
    return (
        (!mino_sobre_suelo(tablero, &tetromino->mino_a))&&
        (!mino_sobre_suelo(tablero, &tetromino->mino_b))&&
        (!mino_sobre_suelo(tablero, &tetromino->mino_c))&&
        (!mino_sobre_suelo(tablero, &tetromino->mino_d))
    );
}

void mino_fijar(t_tablero *tablero, const t_coordenadas *mino)
{
    tablero->celda[mino->x][mino->y].ocupado = true;
    tablero->celda[mino->x][mino->y].caracter = '#';
}

void tablero_actualizar(t_tablero *tablero, const t_tetromino *tetromino)
{
    mino_fijar(tablero, &tetromino->mino_a);
    mino_fijar(tablero, &tetromino->mino_b);
    mino_fijar(tablero, &tetromino->mino_c);
    mino_fijar(tablero, &tetromino->mino_d);
}

bool game_over(const t_tablero *tablero)
{
    return tablero->game_over;
}
