#include "GBT/gbt.h"
#include "juego.h"
#include "paletacolor.h"
#include "pantalla.h"
#include "movimientos.h"
#include "fuente.h"
#include "nombre.h"
#include <stdbool.h>

#define RESO 1

int main()
{
    /// 1. Inicializamos los subsistemas de la libreria grafica y las variables principales.
    if(gbt_iniciar() != 0)
        return -1;

    t_tablero tablero;
    tablero_inicializar(&tablero, CANTIDAD_FILAS, CANTIDAD_COLUMNAS);
    t_tetromino tetromino;

    /// 2. Cargamos nuestra paleta de colores personalizada (definida en paletacolor.c).
    /// Usamos el formato 888 porque nuestros colores estan en hexadecimal RGB (0-255).
    gbt_aplicar_paleta(paleta, CANT_COLORES, GBT_FORMATO_888);

    /// 3. Creamos la ventana segun la resolucion definida por RESO (0 = CGA)
    /// e inicializamos la semilla generadora de piezas aleatorias.
    iniciar_pantalla(RESO);
    srand(time(NULL));

    /// 4. Solicitamos el nombre del usuario por interfaz gr�fica.
    char nombre_usuario[NOMBRE_MAX_CHARS + 1];
    pedir_nombre(nombre_usuario);

    /// 5. Bucle principal del juego (se ejecuta hasta ocupar el espacio de spawn).
    tetromino_insertar(&tablero, &tetromino);

    while(!game_over(&tablero))
    {
        /// 5.1. Logica de pieza en el aire.
        do
        {
            /// 5.1.1. Logica de caida.
            while(tetromino_cayendo(&tablero, &tetromino))
            {
                dibujar(&tablero, &tetromino);
                tablero_mostrar(&tablero, &tetromino);

                int resp_temp_caida = temporizador_movimientos_caida(&tablero, &tetromino, TIEMPO_ESPERA_SEGUNDOS);
                if(resp_temp_caida == SALIR)
                    return resp_temp_caida;

                if(tetromino_cayendo(&tablero, &tetromino))
                    tetromino_desplazar(&tetromino);
            }

            dibujar(&tablero, &tetromino);

            /// 5.1.3. Logica de tolerancia (lock delay).
            int res_temp_tol = temporizador_movimientos_tolerancia(&tablero, &tetromino, TIEMPO_ESPERA_SEGUNDOS / (double)2);
            if(res_temp_tol == SALIR)
                return res_temp_tol;
        }
        while(tetromino_cayendo(&tablero, &tetromino));

        /// 5.2. Logica de fijar pieza en el tablero.
        tablero_actualizar(&tablero, &tetromino);
        dibujar(&tablero, &tetromino);
        tablero_mostrar(&tablero, &tetromino);

        /// 5.3. Logica de eliminacion de filas completas.
        tablero_actualizar_fila_cuspide(&tablero);
        if(tablero_revisar_filas_completas(&tablero) > 0)
        {
            dibujar(&tablero, &tetromino);
            tablero_mostrar(&tablero, &tetromino);
        }

        /// 5.4. Insertar nueva pieza.
        tetromino_insertar(&tablero, &tetromino);
    }

    /// 6. Game over: mostrar estado final del tablero.
    tablero_actualizar(&tablero, &tetromino);
    dibujar(&tablero, &tetromino);
    tablero_mostrar(&tablero, &tetromino);

    /// 7. Cerramos la libreria grafica y liberamos memoria.
    gbt_cerrar();
    return 0;
}
