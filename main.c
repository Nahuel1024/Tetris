#include "funciones.h"
/*
Apellido: Rosas, Nahuel
DNI: 42656246
Usuario: Nahuel1024
Entrega: Sí
Apellido: Ruiz, Alex Uriel
DNI: 46189430
Usuario: alexur15
Entrega: Sí
Apellido:
DNI:
Usuario:
Entrega:
*/
//#include "GBT/gbt.h"
//#include "pantalla.h"
//#define RESO 0 //   1 Iniciar VGA, 0 Inicia CGA

int main()
{
/* -------------------------------------------------------------------------- */
/* VARIABLES                                      */
/* -------------------------------------------------------------------------- */
    t_tablero tablero;
    t_tetromino tetromino;

/* -------------------------------------------------------------------------- */
/* LÓGICA DEL JUEGO                               */
/* -------------------------------------------------------------------------- */
    tablero_inicializar(&tablero);
    tetromino_insertar(&tetromino);

    while(1)
    {
        tablero_mostrar(&tablero, &tetromino);
        tetromino_desplazar(&tetromino);
        Sleep(TIEMPO_ESPERA);
    }

    return OK;
}
