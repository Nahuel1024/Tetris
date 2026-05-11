/**
 * @file pantalla.c
 * @brief Implementación gráfica. Traduce la matriz lógica a píxeles en pantalla.
 */

#include "pantalla.h"

/* ========================================================================== */
/* VARIABLES GLOBALES DE ESTADO VISUAL                                        */
/* ========================================================================== */

int ancho_sistema;
int alto_sistema;

/* ========================================================================== */
/* SECCIÓN: INICIALIZACIÓN Y ORQUESTACIÓN                                     */
/* ========================================================================== */

void iniciar_pantalla(int reso)
{
    if(reso == 0)
    {
        ancho_sistema = ANCHO_CGA;
        alto_sistema = ALTO_CGA;
    }
    else
    {
        ancho_sistema = ANCHO_VGA;
        alto_sistema = ALTO_VGA;
    }

    gbt_crear_ventana("Tetris", ancho_sistema, alto_sistema, TAM_ESCALA);
}

/**
 * COMPLEJO: Cálculo de Centrado Dinámico
 * Para que el tablero siempre quede en el centro de la pantalla sin importar
 * la resolución, restamos el ancho del tablero al ancho total de la ventana.
 * Dividir ese sobrante por 2 nos da el margen exacto (X e Y) desde donde
 * debemos empezar a pintar.
 */
void dibujar(const t_tablero *var_tablero, const t_tetromino *tetromino)
{
    gbt_borrar_backbuffer(0); // Fondo negro general

    int ancho_tablero = var_tablero->dimensiones.ancho * TAM_CELDA;
    int alto_tablero = var_tablero->dimensiones.alto * TAM_CELDA;

    int margen_horizontal = (ancho_sistema - ancho_tablero) / 2;
    int margen_vertical = (alto_sistema - alto_tablero) / 2;

    // 1. Dibujamos el color de fondo del área de juego
    dibujar_rectangulo(0, 0, ancho_sistema, alto_sistema, FONDO);

    // 2. Dibujamos los bloques fijos
    dibujar_tablero(var_tablero, margen_horizontal, margen_vertical);

    // 3. Superponemos la pieza en movimiento
    dibujar_pieza(tetromino, margen_horizontal, margen_vertical);

    gbt_volcar_backbuffer(); // Muestra el frame terminado en pantalla
}

/* ========================================================================== */
/* SECCIÓN: RENDERIZADO DE COMPONENTES DEL JUEGO                              */
/* ========================================================================== */

void dibujar_tablero(const t_tablero *var_tablero, int ini_x, int ini_y)
{
    for(int i = 0; i < var_tablero->dimensiones.alto; i++)
    {
        for(int j = 0; j < var_tablero->dimensiones.ancho; j++)
        {
            int eje_horizontal = ini_x + j * TAM_CELDA;
            int eje_vertical = ini_y + i * TAM_CELDA;

            dibujar_cuadrado(eje_horizontal,
                             eje_vertical,
                             var_tablero->celda[i][j].color,
                             TAM_CELDA);
        }
    }
}

/**
 * COMPLEJO: Ocultamiento en Zona de Spawn
 * Antes de dibujar cada mino, comprobamos que no esté en las filas 0 o 1
 * (!mino_en_area_spawn). Esto crea el efecto visual de que la pieza "baja"
 * entrando desde fuera de la pantalla, en lugar de aparecer de golpe.
 */
void dibujar_pieza(const t_tetromino *tetromino, int ini_x, int ini_y)
{
    for(int i = 0; i < CANTIDAD_MINOS; i++)
    {
        if(!mino_en_area_spawn(&tetromino->mino[i]))
        dibujar_cuadrado(ini_x + (tetromino->mino[i].coordenadas.columna) * TAM_CELDA,
                         ini_y + (tetromino->mino[i].coordenadas.fila) * TAM_CELDA,
                         tetromino->mino[i].color,
                         TAM_CELDA);
    }
}

/* ========================================================================== */
/* SECCIÓN: PRIMITIVAS GRÁFICAS BÁSICAS                                       */
/* ========================================================================== */

void dibujar_cuadrado(int x, int y, int color, int tam)
{
    for (int i = 0; i < tam; i++)
    {
        for (int j = 0; j < tam; j++)
        {
            gbt_dibujar_pixel(x + j, y + i, color);
        }
    }
}

void dibujar_rectangulo(int x, int y, int ancho, int alto, int color)
{
    for (int i = 0; i < alto; i++)
    {
        for (int j = 0; j < ancho; j++)
        {
            gbt_dibujar_pixel(x + j, y + i, color);
        }
    }
}
