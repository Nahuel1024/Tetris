//#include "funciones.h" /// Consultar al profe por qué la carpeta no puede ser llamada debajo de "paletacolor.h"

#include "GBT/gbt.h"
#include "juego.h"
#include "paletacolor.h"
#include "pantalla.h"

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

    /// 3. Creamos la ventana con la resolución definida por la constante RESO (0 = CGA).
    iniciar_pantalla(RESO);

    srand(time(NULL));

    /// 4. Elegimos una pieza al azar (0 a 6) para empezar.
    tetromino_insertar(&tablero, &tetromino);

    bool b = false;
    /// 5. Bucle principal del juego (se ejecuta hasta ocupar el espacio de spawn de tetrominos).
    while(!game_over(&tablero))
    {
        while(tetromino_cayendo(&tablero, &tetromino))
        {
            dibujar(&tablero, &tetromino);
            if(b == false)
            {
                //Sleep(4000);
                b = true;
            }
            gbt_esperar(TIEMPO_ESPERA);
            tablero_mostrar(&tablero, &tetromino);
            tetromino_desplazar(&tetromino);
        }
        tablero_actualizar(&tablero, &tetromino);
        dibujar(&tablero, &tetromino);
        gbt_esperar(TIEMPO_ESPERA);
        tablero_mostrar(&tablero, &tetromino);
        tetromino_insertar(&tablero, &tetromino);
    }
    tablero_actualizar(&tablero, &tetromino);
    dibujar(&tablero, &tetromino);
    gbt_esperar(TIEMPO_ESPERA);
    tablero_mostrar(&tablero, &tetromino);

    /// 6. Cerramos la librería gráfica y liberamos memoria antes de salir.
    gbt_cerrar();
    return 0;
}
