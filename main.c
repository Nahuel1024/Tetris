#include "GBT/gbt.h"
#include "juego.h"
#include "paletacolor.h"
#include "pagina_juego.h"
#include "movimientos.h"
#include "fuente.h"
#include "cola_tetrominos.h"
#include "nombre.h"
#include <stdbool.h>

#define RES_CGA 0
#define RES_VGA 1

int main(int argc, char *argv[])
{
    /// Argumentos a main logica
    int resolucion = RES_VGA;
    if(argc >= 2)
    {
        if(strcmp(argv[1], "CGA") == 0) /// Si argv[1], segunda palabra que se escribe en cmd es CGA, cambia la resolucion a CGA y abre la ventana
            resolucion = RES_CGA;

        else if(strcmp(argv[1], "VGA") == 0) /// Si argv[1], segunda palabra que se escribe en cmd es VGA,cambia la resolucion a VGA y abre la ventana
            resolucion = RES_VGA;

        else
        {
            printf("Modo invalido. Use CGA o VGA\n"); /// Si argv[1], no es CGA 0 VGA , DEVUELVE -1
            return -1;
        }
    }
    if(gbt_iniciar() != 0)
        return -1;

    t_tablero tablero;
    tablero_inicializar(&tablero, CANTIDAD_FILAS, CANTIDAD_COLUMNAS);

    gbt_aplicar_paleta(paleta, CANT_COLORES, GBT_FORMATO_888);
    srand(time(NULL));

    /// Layout calculado una sola vez luego de crear la ventana
    t_layout layout;
    iniciar_pantalla(&layout, resolucion, &tablero);

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
