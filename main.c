/*
Apellido: Rosas, Nahuel
DNI: 42656246
Usuario: Nahuel1024
Entrega: Si
Apellido: Echevarria, Valentina
DNI: 46695673
Usuario: valenechevarriaa
Entrega:Si
Apellido:
DNI:
Usuario:
Entrega:
*/
#include <stdio.h>
#include "GBT/gbt.h"
#include "pantalla.h"
#include "paletacolor.h"
#include "tetromino.h"
#include "../tda_menu_sl/menu.h"
#define ESTADO_MENU_INI 0
#define ESTADO_JUGAR 1
#define ESTADO_MODO 2 //deluxe o clasico
#define ESTADO_SALIR 3 //este puede estar al principio o al momento de pausar o cuando termina.
#define ESTADO_PAUSA 4 //dentro del juego
#define ESTADO_GAMEOVER 5 //cuando termina el juego

int main()
{
    if(gbt_iniciar() != 0)
        return -1;
    gbt_aplicar_paleta(paleta, CANT_COLORES, GBT_FORMATO_888); //Aplica la paleta de colores que definimos en paletacolor.h

    iniciar_pantalla(RESO);  //Iniciar la pantalla en la RESOLUCION QUE ENVIAMOS POR PARAMETRO POR EL MOMENTO

    t_menu menu;

    int estado=ESTADO_MENU_INI;

    menu_inicializar(&menu, CANT_OPCIONES_MENU);

    menu_dibujar(menu.seleccion_actual);

    while(estado==0)
    {
        gbt_procesar_entrada();

        if(menu_actualizar(&menu) == BOTON_1)
        {
            estado=ESTADO_JUGAR;
        }

        menu_dibujar(menu.seleccion_actual);

        gbt_esperar(10);
    }

    int tetromino;
    int pos_x = 0;
    int pos_y = 3;
    tetromino = rand() % 7;
    while(1)
    {
        gbt_procesar_entrada();
        if(pos_x == FILAS - 1)
        {
          pos_x= 0;
          tetromino = rand() % 7;
        }
        else
        {
        dibujar(tetrominos[tetromino], pos_x, pos_y); // DIBUJA EL TETROMINO1 EN LA POS_X 0 Y POS_Y 3 (creo que esto es mejor buscar el centro).
        pos_x++; //Aumento el valor de pos_x entonces cuando vuelve al while, dibuja una fila para abajo. //la misma pieza la va bajando.
        }

        gbt_esperar(200);
    }

    gbt_cerrar();
    return 0;
}
