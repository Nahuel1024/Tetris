#include "GBT/gbt.h"
#include "juego.h"
#include "paletacolor.h"
#include "pagina_juego.h"
#include "pagina_menu.h"
#include "ajustes.h"
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

    /// 2. Ajustes con valores por defecto
    t_ajustes ajustes;
    ajustes_inicializar(&ajustes, resolucion, TIEMPO_ESPERA_SEGUNDOS);

    /// 3. Menu principal
    t_menu menu;
    pagina_menu_inicializar(&menu);

    int opcion = 0;
    while(opcion == 0)
    {
        gbt_borrar_backbuffer(0);

        int menu_x = (layout.ancho_sistema
                      - (int)(MENU_BOTON_ANCHO_BASE * layout.escala_pantalla)) / 2;
        int menu_y = layout.margen_y
                     + (layout.alto_visible
                        - (int)((MENU_BOTON_ALTO_BASE * 3 + MENU_SEPARACION_BASE * 2)
                                 * layout.escala_pantalla)) / 2;

        pagina_menu_dibujar(&layout, &menu, menu_x, menu_y);
        gbt_volcar_backbuffer();

        gbt_procesar_entrada();
        opcion = pagina_menu_actualizar(&menu);

        if(opcion == MENU_BOTON_AJUSTES)
        {
            int resultado = pagina_ajustes_ejecutar(&layout, &ajustes, &tablero);

            if(resultado == AJUSTES_APLICAR)
            {
                /// Si cambio la resolucion, actualizamos la variable local
                resolucion = ajustes.resolucion;
                /// layout ya fue recalculado dentro de pagina_ajustes_ejecutar
            }

            /// Volvemos al menu en cualquier caso
            opcion = 0;
            pagina_menu_inicializar(&menu);
        }

        if(opcion == MENU_BOTON_SALIR)
        {
            gbt_cerrar();
            return 0;
        }
    }

    /// 4. Ingreso de nombre
    char usuario[NOMBRE_MAX_CHARS + 1];
    pedir_nombre(&layout, usuario);

    /// 5. Cola de tetrominos
    t_cola_tetrominos cola;
    cola_tetrominos_inicializar(&cola, &tablero);

    /// 6. Bucle principal del juego
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
                               ajustes.velocidad);  ///< Velocidad desde ajustes

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
                              ajustes.velocidad / 2.0);  ///< Tolerancia = mitad de velocidad

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

    /// 7. Game over
    tablero_actualizar(&tablero, cola_tetrominos_actual(&cola));
    dibujar_juego(&layout, &tablero,
                  cola_tetrominos_actual(&cola),
                  cola_tetrominos_siguiente(&cola));
    tablero_mostrar(&tablero, cola_tetrominos_actual(&cola));

    cola_tetrominos_destruir(&cola);
    gbt_cerrar();
    return 0;
}
