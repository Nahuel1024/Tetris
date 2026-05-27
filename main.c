#include "GBT/gbt.h"
#include "juego.h"
#include "paletacolor.h"
#include "pagina_juego.h"
#include "pagina_menu.h"
#include "movimientos.h"
#include "fuente.h"
#include "cola_tetrominos.h"
#include "nombre.h"
#include <stdbool.h>

#define RES_CGA 0
#define RES_VGA 1

int main(int argc, char *argv[])
{
    /// 1. Resolucion por argumento
    int resolucion = RES_VGA;
    if(argc >= 2)
    {
        if(strcmp(argv[1], "CGA") == 0)
            resolucion = RES_CGA;
        else if(strcmp(argv[1], "VGA") == 0)
            resolucion = RES_VGA;
        else
        {
            printf("Modo invalido. Use CGA o VGA\n");
            return ERR_ARGUMENTO;
        }
    }

    if(gbt_iniciar() != 0)
        return ERR_ARGUMENTO;

    t_tablero tablero;
    tablero_inicializar(&tablero, CANTIDAD_FILAS, CANTIDAD_COLUMNAS);

    gbt_aplicar_paleta(paleta, CANT_COLORES, GBT_FORMATO_888);
    srand(time(NULL));

    t_layout layout;
    iniciar_pantalla(&layout, resolucion, &tablero);

    /// 2. Menu principal
    t_menu menu;
    pagina_menu_inicializar(&menu);

    int opcion = 0;
    while(opcion == 0)
    {
        gbt_borrar_backbuffer(0);

        /// Centrado horizontal del bloque de botones
        int menu_x = (layout.ancho_sistema
                      - (int)(MENU_BOTON_ANCHO_BASE * layout.escala_pantalla)) / 2;
        int menu_y = (layout.margen_y
                      + (layout.alto_visible
                         - (int)((MENU_BOTON_ALTO_BASE * 3 + MENU_SEPARACION_BASE * 2)
                                 * layout.escala_pantalla))) / 2;

        pagina_menu_dibujar(&layout, &menu, menu_x, menu_y);
        gbt_volcar_backbuffer();

        gbt_procesar_entrada();
        opcion = pagina_menu_actualizar(&menu);
    }

    if(opcion == MENU_BOTON_SALIR)
    {
        gbt_cerrar();
        return 0;
    }

    /// MENU_BOTON_AJUSTES: pendiente de implementar, por ahora cae al juego
    /// MENU_BOTON_JUGAR: continua al bucle principal

    /// 3. Ingreso de nombre
    char usuario[NOMBRE_MAX_CHARS + 1];
    pedir_nombre(&layout, usuario);

    /// 4. Cola de tetrominos
    t_cola_tetrominos cola;
    cola_tetrominos_inicializar(&cola, &tablero);

    /// 5. Bucle principal del juego
    while(!game_over(&tablero))
    {
        t_tetromino *actual    = cola_tetrominos_actual(&cola);
        t_tetromino *siguiente = cola_tetrominos_siguiente(&cola);

        do
        {
            while(tetromino_cayendo(&tablero, actual))
            {
                dibujar_juego(&layout, &tablero, actual, siguiente);
                tablero_mostrar(&tablero, actual);

                gbt_procesar_entrada();

                int resp = temporizador_movimientos_caida(
                               &layout, &tablero, actual, siguiente,
                               TIEMPO_ESPERA_SEGUNDOS);

                if(resp == SALIR)
                {
                    cola_tetrominos_destruir(&cola);
                    return resp;
                }

                if(tetromino_cayendo(&tablero, actual))
                    tetromino_desplazar(actual);
            }

            dibujar_juego(&layout, &tablero, actual, siguiente);

            int res_tol = temporizador_movimientos_tolerancia(
                              &layout, &tablero, actual, siguiente,
                              TIEMPO_ESPERA_SEGUNDOS / (double)2);
            if(res_tol == SALIR)
            {
                cola_tetrominos_destruir(&cola);
                return res_tol;
            }
        }
        while(tetromino_cayendo(&tablero, actual));

        tablero_actualizar(&tablero, actual);
        dibujar_juego(&layout, &tablero, actual, siguiente);
        tablero_mostrar(&tablero, actual);

        tablero_actualizar_fila_cuspide(&tablero);
        if(tablero_revisar_filas_completas(&tablero) > 0)
        {
            dibujar_juego(&layout, &tablero, actual, siguiente);
            tablero_mostrar(&tablero, actual);
        }

        cola_tetrominos_avanzar(&cola, &tablero);
    }

    /// 6. Game over
tablero_actualizar(&tablero,
                   cola_tetrominos_actual(&cola));

dibujar_juego(&layout,
              &tablero,
              cola_tetrominos_actual(&cola),
              cola_tetrominos_siguiente(&cola));

/// Cartel de game over
dibujar_cartel_game_over(&layout);

gbt_volcar_backbuffer();

/// Espera input
while(1)
{
    gbt_procesar_entrada();
    /// Reiniciar juego
    if(gbt_tecla_presionada(GBTK_ENTER))
    {
        cola_tetrominos_destruir(&cola);

        main(argc, argv);

        return 0;
    }
    /// Salir del juego
    if(gbt_tecla_presionada(GBTK_ESCAPE))
    {
        cola_tetrominos_destruir(&cola);

        gbt_cerrar();

        return 0;
    }
}
}
