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
double escala_pantalla;

/* ========================================================================== */
/* SECCIÓN: INICIALIZACIÓN Y ORQUESTACIÓN                                     */
/* ========================================================================== */

void iniciar_pantalla(int reso)
{
    if(reso == 0)
    {
        ancho_sistema = ANCHO_CGA;
        alto_sistema = ALTO_CGA;
        escala_pantalla = 1;
    }
    else
    {
        ancho_sistema = ANCHO_VGA;
        alto_sistema = ALTO_VGA;
        escala_pantalla = 1.5;
    }

    gbt_crear_ventana("Tetris", ancho_sistema, alto_sistema, 2);
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
    gbt_borrar_backbuffer(0);

    int ancho_tablero = var_tablero->dimensiones.ancho * TAM_CELDA_RESOLUCION;
    int alto_tablero_visible = (var_tablero->dimensiones.alto - FILAS_SPAWN) * TAM_CELDA_RESOLUCION;

    int margen_horizontal = (ancho_sistema - ancho_tablero) / 2;
    int margen_vertical   = (alto_sistema - alto_tablero_visible) / 2;

    // Al calcular el margen vertical, corremos el origen hacia arriba
    // la cantidad de filas de spawn, para que dibujar_tablero
    // (que itera desde i=2) empiece exactamente en margen_vertical.
    int origen_y = margen_vertical - FILAS_SPAWN * TAM_CELDA_RESOLUCION;

    dibujar_rectangulo(0, 0, ancho_sistema, alto_sistema, FONDO);
    dibujar_tablero(var_tablero, margen_horizontal, origen_y);
    dibujar_pieza(tetromino, margen_horizontal, origen_y);

    gbt_volcar_backbuffer();
}

/* ========================================================================== */
/* SECCIÓN: RENDERIZADO DE COMPONENTES DEL JUEGO                              */
/* ========================================================================== */

void dibujar_tablero(const t_tablero *var_tablero, int ini_x, int ini_y)
{
    int i;
    for(i = 2; i < var_tablero->dimensiones.alto; i++)
    {
        for(int j = 0; j < var_tablero->dimensiones.ancho; j++)
        {
            int eje_horizontal = ini_x + j * TAM_CELDA_RESOLUCION;
            int eje_vertical = ini_y + i * TAM_CELDA_RESOLUCION;

            dibujar_cuadrado(eje_horizontal,
                             eje_vertical,
                             var_tablero->celda[i][j].color,
                             TAM_CELDA_RESOLUCION);
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
        dibujar_cuadrado(ini_x + (tetromino->mino[i].coordenadas.columna) * TAM_CELDA_RESOLUCION,
                         ini_y + (tetromino->mino[i].coordenadas.fila) * TAM_CELDA_RESOLUCION,
                         tetromino->mino[i].color,
                         TAM_CELDA_RESOLUCION);
    }
}

/* ========================================================================== */
/* SECCIÓN: PRIMITIVAS GRÁFICAS BÁSICAS                                       */
/* ========================================================================== */

void dibujar_cuadrado(int x, int y, int color, int tam)
{
    int borde_claro = 15;
    int borde_oscuro = BORDE;

    // Grosor proporcional: 1px por cada 10px de tamaño (mínimo 1px)
    int grosor = (tam + 9) / 10;
    if(grosor < 1) grosor = 1;

    // Relleno: respeta el grosor del borde en los 4 lados
    for(int i = grosor; i < tam - grosor; i++)
        for(int j = grosor; j < tam - grosor; j++)
            gbt_dibujar_pixel(x + j, y + i, color);

    // Bordes con grosor variable
    for(int g = 0; g < grosor; g++)
    {
        // Superior e izquierdo: claros
        for(int i = 0; i < tam; i++)
        {
            gbt_dibujar_pixel(x + i, y + g,       borde_claro);  // superior
            gbt_dibujar_pixel(x + g, y + i,       borde_claro);  // izquierdo
        }
        // Inferior y derecho: oscuros
        for(int i = 0; i < tam; i++)
        {
            gbt_dibujar_pixel(x + i, y + tam - 1 - g, borde_oscuro);  // inferior
            gbt_dibujar_pixel(x + tam - 1 - g, y + i, borde_oscuro);  // derecho
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
