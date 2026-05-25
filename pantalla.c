/**
 * @file pantalla.c
 * @brief Implementacion grafica. Traduce la matriz logica a pixeles en pantalla.
 */

#include "pantalla.h"
#include "fuente.h"
#include "pantallainicio.h"

/* ========================================================================== */
/* VARIABLES GLOBALES DE ESTADO VISUAL                                        */
/* ========================================================================== */

int    ancho_sistema;
int    alto_sistema;

/* ========================================================================== */
/* SECCION: INICIALIZACION Y ORQUESTACION                                     */
/* ========================================================================== */

void iniciar_pantalla(int reso)
{
    if(reso == 0)
    {
        ancho_sistema = ANCHO_CGA;
        alto_sistema  = ALTO_CGA;
    }
    else
    {
        ancho_sistema = ANCHO_VGA;
        alto_sistema  = ALTO_VGA;
    }

    gbt_crear_ventana("Tetris", ancho_sistema, alto_sistema, TAM_ESCALA);
}

void dibujar(const t_tablero *var_tablero, const t_tetromino *tetromino)
{
    gbt_borrar_backbuffer(0);

    int ancho_tablero = var_tablero->dimensiones.ancho * TAM_CELDA;
    int alto_tablero  = var_tablero->dimensiones.alto  * TAM_CELDA;

    int margen_horizontal = (ancho_sistema - ancho_tablero) / 2;
    int margen_vertical   = (alto_sistema  - alto_tablero)  / 2;

    dibujar_rectangulo(0, 0, ancho_sistema, alto_sistema, 7);

    dibujar_hud(margen_horizontal, margen_vertical, ancho_tablero);
    dibujar_tablero(var_tablero, margen_horizontal, margen_vertical);
    dibujar_pieza(tetromino, margen_horizontal, margen_vertical);

    gbt_volcar_backbuffer();
}

/* ========================================================================== */
/* SECCION: RENDERIZADO DE COMPONENTES DEL JUEGO                              */
/* ========================================================================== */

void dibujar_tablero(const t_tablero *var_tablero, int ini_x, int ini_y)
{
    for(int i = 2; i < var_tablero->dimensiones.alto; i++)
    {
        for(int j = 0; j < var_tablero->dimensiones.ancho; j++)
        {
            int eje_horizontal = ini_x + j * TAM_CELDA;
            int eje_vertical   = ini_y + i * TAM_CELDA;

            dibujar_cuadrado(eje_horizontal,
                             eje_vertical,
                             var_tablero->celda[i][j].color,
                             TAM_CELDA);
        }
    }
}

void dibujar_pieza(const t_tetromino *tetromino, int ini_x, int ini_y)
{
    for(int i = 0; i < CANTIDAD_MINOS; i++)
    {
        if(!mino_en_area_spawn(&tetromino->mino[i]))
            dibujar_cuadrado(ini_x + tetromino->mino[i].coordenadas.columna * TAM_CELDA,
                             ini_y + tetromino->mino[i].coordenadas.fila    * TAM_CELDA,
                             tetromino->mino[i].color,
                             TAM_CELDA);
    }
}

/* ========================================================================== */
/* SECCION: PRIMITIVAS GRAFICAS BASICAS                                       */
/* ========================================================================== */

void dibujar_cuadrado(int x, int y, int color, int tam)
{
    int borde_claro  = 15;
    int borde_oscuro = 14;

    for(int i = 1; i < tam - 1; i++)
        for(int j = 1; j < tam - 1; j++)
            gbt_dibujar_pixel(x + j, y + i, color);

    for(int i = 0; i < tam; i++)
        gbt_dibujar_pixel(x + i, y,           borde_claro);

    for(int i = 0; i < tam; i++)
        gbt_dibujar_pixel(x, y + i,           borde_claro);

    for(int i = 0; i < tam; i++)
        gbt_dibujar_pixel(x + i, y + tam - 1, borde_oscuro);

    for(int i = 0; i < tam; i++)
        gbt_dibujar_pixel(x + tam - 1, y + i, borde_oscuro);
}

void dibujar_rectangulo(int x, int y, int ancho, int alto, int color)
{
    for(int i = 0; i < alto; i++)
        for(int j = 0; j < ancho; j++)
            gbt_dibujar_pixel(x + j, y + i, color);
}

void dibujar_cartel_pausa(void)
{
    dibujar_rectangulo(180, 180, 280, 120, 7);

    dibujar_rectangulo(180, 180, 280, 4, 14);
    dibujar_rectangulo(180, 296, 280, 4, 14);
    dibujar_rectangulo(180, 180, 4, 120, 14);
    dibujar_rectangulo(456, 180, 4, 120, 14);

    fuente_dibujar_texto(&FUENTE_LARGE, 260, 220, "PAUSA", 14);
    fuente_dibujar_texto(&FUENTE_LARGE, 200, 260, "ENTER PARA CONTINUAR", 14);
}
