#include "GBT/gbt.h"
#include "juego.h"
#include "paletacolor.h"
#include "pantalla.h"
#include "movimientos.h"
#include "fuente.h"
#include "cola_tetrominos.h"
#include <stdbool.h>

#define RESO 0

int main()
{
    /// 1. Inicializamos los subsistemas de la libreria grafica.
    if(gbt_iniciar() != 0)
        return -1;

    t_tablero tablero;
    tablero_inicializar(&tablero, CANTIDAD_FILAS, CANTIDAD_COLUMNAS);

    /// 2. Paleta de colores y ventana.
    gbt_aplicar_paleta(paleta, CANT_COLORES, GBT_FORMATO_888);
    iniciar_pantalla(RESO);
    srand(time(NULL));

    /// 3. Inicializamos la cola con el tetromino actual (en spawn) y el siguiente (preview).
    t_cola_tetrominos cola;
    cola_tetrominos_inicializar(&cola, &tablero);

    /// 4. Bucle principal del juego.
    while(!game_over(&tablero))
    {
        t_tetromino *actual    = cola_tetrominos_actual(&cola);
        t_tetromino *siguiente = cola_tetrominos_siguiente(&cola);

        do
        {
            /// 4.1. Logica de caida.
            while(tetromino_cayendo(&tablero, actual))
            {
                gbt_procesar_entrada();

                /// 4.1.1. Logica de pausa.
                if(gbt_tecla_presionada(GBTK_p))
                {
                    while(1)
                    {
                        gbt_procesar_entrada();
                        dibujar(&tablero, actual, siguiente);
                        dibujar_cartel_pausa();
                        gbt_volcar_backbuffer();

                        if(gbt_tecla_presionada(GBTK_ENTER))
                            break;
                    }
                }

                dibujar(&tablero, actual, siguiente);
                tablero_mostrar(&tablero, actual);

                int resp = temporizador_movimientos_caida(&tablero, actual, TIEMPO_ESPERA_SEGUNDOS);
                if(resp == SALIR)
                {
                    cola_tetrominos_destruir(&cola);
                    return resp;
                }

                if(tetromino_cayendo(&tablero, actual))
                    tetromino_desplazar(actual);
            }

            dibujar(&tablero, actual, siguiente);

            /// 4.1.2. Logica de tolerancia (lock delay).
            int res_tol = temporizador_movimientos_tolerancia(&tablero, actual,
                                                              TIEMPO_ESPERA_SEGUNDOS / (double)2);
            if(res_tol == SALIR)
            {
                cola_tetrominos_destruir(&cola);
                return res_tol;
            }
        }
        while(tetromino_cayendo(&tablero, actual));

        /// 4.2. Fijar pieza en el tablero.
        tablero_actualizar(&tablero, actual);
        dibujar(&tablero, actual, siguiente);
        tablero_mostrar(&tablero, actual);

        /// 4.3. Eliminacion de filas completas.
        tablero_actualizar_fila_cuspide(&tablero);
        tablero_revisar_filas_completas(&tablero);

        /// 4.4. Avanzar cola: siguiente → actual, genera nuevo siguiente.
        cola_tetrominos_avanzar(&cola, &tablero);
        actual    = cola_tetrominos_actual(&cola);
        siguiente = cola_tetrominos_siguiente(&cola);
    }

    /// 5. Game over: mostrar estado final.
    tablero_actualizar(&tablero, cola_tetrominos_actual(&cola));
    dibujar(&tablero, cola_tetrominos_actual(&cola), cola_tetrominos_siguiente(&cola));
    tablero_mostrar(&tablero, cola_tetrominos_actual(&cola));

    /// 6. Liberar recursos y cerrar.
    cola_tetrominos_destruir(&cola);
    gbt_cerrar();
    return 0;
}
