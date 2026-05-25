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
double escala_pantalla;
int    margen_y;      ///< Primer pixel Y visible (0 en CGA, 60 en VGA)
int    alto_visible;  ///< Alto del area realmente utilizable por los dibujos

/* ========================================================================== */
/* SECCION: INICIALIZACION Y ORQUESTACION                                     */
/* ========================================================================== */

void iniciar_pantalla(int reso)
{
    if(reso == 0)
    {
        ancho_sistema   = ANCHO_CGA;
        alto_sistema    = ALTO_CGA;
        escala_pantalla = 1.0;
        margen_y        = 0;
    }
    else
    {
        ancho_sistema   = ANCHO_VGA;
        alto_sistema    = ALTO_VGA;
        escala_pantalla = 1.5;
        margen_y        = 60;
    }

    alto_visible = alto_sistema - margen_y * 2;

    gbt_crear_ventana("Tetris", ancho_sistema, alto_sistema, TAM_ESCALA);
}

/**
 * Calculo de Centrado Dinamico.
 * alto_tablero_visible descuenta las FILAS_SPAWN para representar unicamente
 * las filas visibles. El centrado vertical parte desde margen_y para quedar
 * dentro del area visible del monitor en cualquier resolucion.
 */
void dibujar(const t_tablero *var_tablero, const t_tetromino *tetromino)
{
    gbt_borrar_backbuffer(0);

    int ancho_tablero        = var_tablero->dimensiones.ancho * TAM_CELDA;
    int alto_tablero_visible = (var_tablero->dimensiones.alto - FILAS_SPAWN) * TAM_CELDA;

    int margen_horizontal = (ancho_sistema - ancho_tablero) / 2;
    int margen_vertical   = margen_y + (alto_visible - alto_tablero_visible) / 2;

    dibujar_rectangulo(0, margen_y, ancho_sistema, alto_visible, FONDO);

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
            int eje_vertical   = ini_y + (i - FILAS_SPAWN) * TAM_CELDA;

            dibujar_cuadrado(eje_horizontal,
                             eje_vertical,
                             var_tablero->celda[i][j].color,
                             TAM_CELDA);
        }
    }
}

/**
 * Ocultamiento en Zona de Spawn.
 * Antes de dibujar cada mino comprobamos que no este en las filas 0 o 1.
 * Esto crea el efecto de que la pieza entra desde fuera de la pantalla.
 */
void dibujar_pieza(const t_tetromino *tetromino, int ini_x, int ini_y)
{
    for(int i = 0; i < CANTIDAD_MINOS; i++)
    {
        if(!mino_en_area_spawn(&tetromino->mino[i]))
            dibujar_cuadrado(ini_x + tetromino->mino[i].coordenadas.columna * TAM_CELDA,
                             ini_y + (tetromino->mino[i].coordenadas.fila - FILAS_SPAWN) * TAM_CELDA,
                             tetromino->mino[i].color,
                             TAM_CELDA);
    }
}

/* ========================================================================== */
/* SECCION: PRIMITIVAS GRAFICAS BASICAS                                       */
/* ========================================================================== */

void dibujar_cuadrado(int x, int y, int color, int tam)
{
    /// Grosor proporcional: 1px en CGA (escala 1.0), 2px en VGA (escala 1.5)
    int grosor = (int)(escala_pantalla + 0.5);

    for(int i = grosor; i < tam - grosor; i++)
        for(int j = grosor; j < tam - grosor; j++)
            gbt_dibujar_pixel(x + j, y + i, color);

    for(int g = 0; g < grosor; g++)
    {
        for(int i = 0; i < tam; i++)
        {
            gbt_dibujar_pixel(x + i, y + g,            15);    ///< Superior claro
            gbt_dibujar_pixel(x + g, y + i,            15);    ///< Izquierdo claro
            gbt_dibujar_pixel(x + i, y + tam - 1 - g,  BORDE); ///< Inferior oscuro
            gbt_dibujar_pixel(x + tam - 1 - g, y + i,  BORDE); ///< Derecho oscuro
        }
    }
}

void dibujar_rectangulo(int x, int y, int ancho, int alto, int color)
{
    for(int i = 0; i < alto; i++)
        for(int j = 0; j < ancho; j++)
            gbt_dibujar_pixel(x + j, y + i, color);
}

void dibujar_cartel_pausa(void)
{
    /// Fondo del cartel centrado en el area visible
    int cartel_ancho = (int)(280 * escala_pantalla);
    int cartel_alto  = (int)(120 * escala_pantalla);
    int cartel_x     = (ancho_sistema - cartel_ancho) / 2;
    int cartel_y     = margen_y + (alto_visible - cartel_alto) / 2;
    int borde        = (int)(4 * escala_pantalla);

    dibujar_rectangulo(cartel_x, cartel_y, cartel_ancho, cartel_alto, FONDO);

    dibujar_rectangulo(cartel_x,                       cartel_y,                        cartel_ancho, borde, BORDE);
    dibujar_rectangulo(cartel_x,                       cartel_y + cartel_alto - borde,  cartel_ancho, borde, BORDE);
    dibujar_rectangulo(cartel_x,                       cartel_y,                        borde, cartel_alto,  BORDE);
    dibujar_rectangulo(cartel_x + cartel_ancho - borde, cartel_y,                       borde, cartel_alto,  BORDE);

    int texto_y_pausa = cartel_y + (int)(40 * escala_pantalla);
    int texto_y_enter = cartel_y + (int)(80 * escala_pantalla);

    fuente_dibujar_texto(&FUENTE_LARGE,
                         cartel_x + (cartel_ancho - fuente_ancho_texto(&FUENTE_LARGE, "PAUSA")) / 2,
                         texto_y_pausa,
                         "PAUSA", BORDE);

    fuente_dibujar_texto(&FUENTE_LARGE,
                         cartel_x + (cartel_ancho - fuente_ancho_texto(&FUENTE_LARGE, "ENTER PARA CONTINUAR")) / 2,
                         texto_y_enter,
                         "ENTER PARA CONTINUAR", BORDE);
}
