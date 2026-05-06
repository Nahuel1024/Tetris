#include "GBT/gbt.h"
#include "pantalla.h"
#include "paletacolor.h"
#include "tetromino.h"
#define RESO 0

int main()
{
    /// 1. Inicializamos los subsistemas de la librería gráfica.
    /// Si falla (devuelve distinto de 0), cerramos el programa con error (-1).
    if(gbt_iniciar() != 0)
        return -1;

    /// 2. Cargamos nuestra paleta de colores personalizada (definida en paletacolor.c)
    /// Usamos el formato 888 porque nuestros colores están en hexadecimal RGB (0-255).
    gbt_aplicar_paleta(paleta, CANT_COLORES, GBT_FORMATO_888);

    /// 3. Creamos la ventana con la resolución definida por la constante RESO (0 = CGA).
    iniciar_pantalla(RESO);

    int tetromino;
    int pos_x = 0; // OJO: Lo estás usando para las FILAS (eje vertical Y)
    int pos_y = 3; // OJO: Lo estás usando para las COLUMNAS (eje horizontal X)

    /// 4. Elegimos una pieza al azar (0 a 6) para empezar.
    tetromino = rand() % 7;

    /// 5. Bucle principal del juego (se ejecuta infinitamente hasta que cerremos la ventana).
    while(1)
    {
        /// 5a. Actualizamos el estado de las teclas (necesario aunque aún no las uses).
        gbt_procesar_entrada();

        /// 5b. Lógica de caída: Si la pieza llegó al fondo (última fila visible)...
        if(pos_x == FILAS - 1)
        {
            pos_x = 0; // Reiniciamos la posición arriba de todo.
            tetromino = rand() % 7; // Generamos una nueva pieza aleatoria.
        }
        else
        {
            // Si no llegó al fondo, dibujamos la pantalla completa con la pieza actual.
            dibujar(tetrominos[tetromino], pos_x, pos_y);

            // Aumentamos pos_x (filas) para que en el próximo ciclo la pieza baje un casillero.
            pos_x++;
        }

        /// 5c. Esperamos 200 ms. Esto controla la velocidad de caída (5 "frames" por segundo).
        gbt_esperar(200);
    }

    /// 6. Cerramos la librería gráfica y liberamos memoria antes de salir.
    gbt_cerrar();
    return 0;
}
