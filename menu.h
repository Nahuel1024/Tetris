#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED

#include "fuentes.h"
#include "layout.h"
#define COLOR_BOTON_PREDETERMINADO 14
#define COLOR_BOTON_SELECCIONADO 6
#define CANT_OPCIONES_MENU 3 //cantidad de opciones/botones que va a haber
#define BOTON_1 1     //JUGAR
#define BOTON_2 2    //MODO deluxe o clasico
#define BOTON_3 3   //SALIR este puede estar al principio o al momento de pausar o cuando termina.
#define ANCHO_BOTON 140
#define ALTO_BOTON 15
#define SEPARACION_BOTONES 20   // los botones van a tener las mismas caracteristicas,
                                //solo va a cambiar Y asi pueden verse separados.
typedef struct
{
    int seleccion_actual;
    int opcion_elegida;
    int cantidad_opciones;
}t_menu;

void menu_inicializar(t_menu *menu, const int opcion);//prepara el menu. seleccion incial, estados internos,
                        //colores, etc. EJEMPLO: seleccion_actual=0;

int menu_actualizar(t_menu *menu); //esta debe captar si la persona elije una de las opciones
                        //si lo hace, se actualiza el estado en el main, y pasaria a las
                        //funciones de dibujo del tablero y las de la logica de juego
                        //Esta procesa la logica del menu. lee el teclado, mueve
                        //seleccion, detecta enter. EJEMPLO: if flecha abajo selec++;
                        //esta opcion va a devolver la opcion elegidda.

void menu_dibujar(const t_layout *layout, const int seleccion_actual, int x, int y, t_letra *fuente);  //renderiza el menu en pantalla. dibuja fondo, botones,
                                                //seleccion actual, titulo, etc.

#endif // MENU_H_INCLUDED
