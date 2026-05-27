#include "GBT/gbt.h"
#include "juego.h"
#include "paletacolor.h"
#include "pagina_juego.h"
#include "pantalla_inicio.h"
#include "movimientos.h"
#include "menu.h"
#include "fuente.h"
#include "fuentes.h"
#include "cola_tetrominos.h"
#include "nombre.h"
#include <stdbool.h>

#define RESO 1
#define ESTADO_MENU_INI 0
#define ESTADO_JUGAR 1

int main()
{
    if(gbt_iniciar() != 0)
        return -1;

    t_tablero tablero;
    tablero_inicializar(&tablero, CANTIDAD_FILAS, CANTIDAD_COLUMNAS);

    gbt_aplicar_paleta(paleta, CANT_COLORES, GBT_FORMATO_888);
    srand(time(NULL));

    /// Layout calculado una sola vez luego de crear la ventana
    t_layout layout;
    iniciar_pantalla(&layout, RESO, &tablero);

    /// PANTALLA PRINCIPAL

    t_letra fuente[CANT_CARAC];
    fuente_inicializar(fuente);

    t_menu menu;

    int estado=ESTADO_MENU_INI;

    menu_inicializar(&menu, CANT_OPCIONES_MENU);

    dibujar_pantalla(&layout, menu.seleccion_actual, RESO, fuente);


    while(estado==0)
    {
        gbt_procesar_entrada();

        if(menu_actualizar(&menu) == BOTON_1)
        {
            estado=ESTADO_JUGAR;
        }

        dibujar_pantalla(&layout, menu.seleccion_actual, RESO, fuente);

        gbt_esperar(10);
    }

    char usuario[NOMBRE_MAX_CHARS + 1];
    pedir_nombre(&layout, usuario);

    t_cola_tetrominos cola;
    cola_tetrominos_inicializar(&cola, &tablero);

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

    tablero_actualizar(&tablero, cola_tetrominos_actual(&cola));
    dibujar_juego(&layout, &tablero,
                  cola_tetrominos_actual(&cola),
                  cola_tetrominos_siguiente(&cola));
    tablero_mostrar(&tablero, cola_tetrominos_actual(&cola));

    cola_tetrominos_destruir(&cola);
    gbt_cerrar();
    return 0;
}
