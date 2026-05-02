/*
Apellido: Rosas, Nahuel
DNI: 42656246
Usuario: Nahuel1024
Entrega: Sí
Apellido:
DNI:
Usuario:
Entrega:
Apellido:
DNI:
Usuario:
Entrega:
*/
#include "GBT/gbt.h"
#include "pantalla.h"
#include "paletacolor.h"

#define RESO 0
#define FILAS 22
#define COLUMNAS 10

int main()
{
    if(gbt_iniciar() != 0)
        return -1;
    gbt_aplicar_paleta(paleta, CANT_COLORES, GBT_FORMATO_888); //Aplica la paleta de colores que definimos en paletacolor.h

    iniciar_pantalla(RESO);  //Iniciar la pantalla en la RESOLUCION QUE ENVIAMOS POR PARAMETRO POR EL MOMENTO


    int tetromino1[4][4] =
    {
        {0,3,0,0},      // 3 es el color CIAN  el cual representa al tetromino I como dice en paletacolor.h
        {0,3,0,0},
        {0,3,0,0},
        {0,3,0,0}
    };
    int pos_x = 0;
    int pos_y = 3;
    while(1)
    {
        gbt_procesar_entrada();

        dibujar(tetromino1, pos_x, pos_y); // DIBUJA EL TETROMINO1 EN LA POS_X 0 Y POS_Y 3 (creo que esto es mejor buscar el centro).
        pos_x++; //Aumento el valor de pos_x entonces cuando vuelve al while, dibuja una fila para abajo.

        gbt_esperar(200);
    }

    gbt_cerrar();
    return 0;
}
