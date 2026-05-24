//#include "funciones.h" /// Consultar al profe por qué la carpeta no puede ser llamada debajo de "paletacolor.h"
#include "GBT/gbt.h"
#include "juego.h"
#include "paletacolor.h"
#include "pantalla.h"
#include "movimientos.h"
#include "nombre.h"
#include <stdbool.h>

#define RESO 1

int main()
{
    /// 1. Inicializamos los subsistemas de la librería gráfica y las variables principales.
    if(gbt_iniciar() != 0)
        return -1;
    t_tablero tablero;
    tablero_inicializar(&tablero, CANTIDAD_FILAS, CANTIDAD_COLUMNAS);
    t_tetromino tetromino;

    /// 2. Cargamos nuestra paleta de colores personalizada (definida en paletacolor.c)
    /// Usamos el formato 888 porque nuestros colores están en hexadecimal RGB (0-255).
    gbt_aplicar_paleta(paleta, CANT_COLORES, GBT_FORMATO_888);

    /// 3. Creamos la ventana con la resolución definida por la constante RESO (0 = CGA) y semilla generadora de piezas aleatorias.
    iniciar_pantalla(RESO);

    char nombre_jugador[NOMBRE_MAX_CHARS + 1];
    pedir_nombre(nombre_jugador);

    srand(time(NULL));

    /// 4. Elegimos una pieza al azar (0 a 6) para empezar.
    tetromino_insertar(&tablero, &tetromino);

    /// 5. Bucle principal del juego (se ejecuta hasta ocupar el espacio de spawn de tetrominos).
    while(!game_over(&tablero))
    {
        /// 5.1. Lógica de pieza "en el aire" (el ciclo do-while).
        do
        {
            /// 5.1.1. Lógica de caida.
            while(tetromino_cayendo(&tablero, &tetromino))
            {
                dibujar(&tablero, &tetromino);
                tablero_mostrar(&tablero, &tetromino);
                int resp_temp_caida = temporizador_movimientos_caida(&tablero, &tetromino, TIEMPO_ESPERA_SEGUNDOS);
                if(resp_temp_caida == SALIR)
                    return resp_temp_caida;
                else if(tetromino_cayendo(&tablero, &tetromino)) /// Verificar que luego de hacer movimientos siga en el aire antes de desplazar...
                    tetromino_desplazar(&tetromino);
            }
            dibujar(&tablero, &tetromino);


            /// 5.1.2. Lógica de tolerancia.
            int res_temp_tol = temporizador_movimientos_tolerancia(&tablero, &tetromino, TIEMPO_ESPERA_SEGUNDOS / (double)2);
            if (res_temp_tol == SALIR)
                return res_temp_tol;
        }while(tetromino_cayendo(&tablero, &tetromino));

        /// 5.2. Lógica de fijar pieza en el tablero.
        tablero_actualizar(&tablero, &tetromino);
        dibujar(&tablero, &tetromino);
        tablero_mostrar(&tablero, &tetromino);

        /// 5.3. Lógica de eliminación de filas.
        tablero_actualizar_fila_cuspide(&tablero);
        if(tablero_revisar_filas_completas(&tablero) > 0)
        {
            dibujar(&tablero, &tetromino);
            tablero_mostrar(&tablero, &tetromino);
        }

        /// 5.4. Insertar nueva pieza (tetromino).
        tetromino_insertar(&tablero, &tetromino);
    }
    tablero_actualizar(&tablero, &tetromino);
    dibujar(&tablero, &tetromino);
    tablero_mostrar(&tablero, &tetromino);

    printf("Nombre del jugador: %s\n\n", nombre_jugador);

    /// 6. Cerramos la librería gráfica y liberamos memoria antes de salir.
    gbt_cerrar();
    return 0;
}
