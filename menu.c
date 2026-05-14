#include "../Tetris/include/GBT/gbt_entrada.h"
#include "../Tetris/include/GBT/gbt_graficos.h"
#include "../Tetris/paletacolor.h"
#include "menu.h"
#include "../Tetris/pantalla.h"
//#include <stdbool.h>
#include <stdio.h>

void menu_inicializar(t_menu *menu, const int opcion)
{
    menu->seleccion_actual=1;//empieza en boton jugar
    menu->opcion_elegida=0;
    menu->cantidad_opciones=opcion;
}
int menu_actualizar(t_menu *menu)
{

    if(gbt_tecla_presionada(GBTK_ABAJO)==1)
    {

        menu->seleccion_actual++;

        if(menu->seleccion_actual > menu->cantidad_opciones)
            menu->seleccion_actual=1;

    }

    if(gbt_tecla_presionada(GBTK_ARRIBA)==1)
    {
        if(menu->seleccion_actual==2 || menu->seleccion_actual==3)
            menu->seleccion_actual--;
    }

    if(gbt_tecla_presionada(GBTK_ENTER)==1)
    {
        menu->opcion_elegida=menu->seleccion_actual;
    }

    return menu->opcion_elegida;
}
void menu_dibujar(const int seleccion_actual)
{
    int ancho_sistema;
    int alto_sistema;

    if(RESO == 0)
    {
        ancho_sistema = ANCHO_CGA;
        alto_sistema = ALTO_CGA;
    }
    else
    {
        ancho_sistema = ANCHO_VGA;
        alto_sistema = ALTO_VGA;
    }
    gbt_borrar_backbuffer(0); // fondo negro

    int x= (ancho_sistema-ANCHO_BOTON)/2; //posicion en x en la que va a empezar a dibujar el boton
    int y= (alto_sistema-ALTO_BOTON)/2;   //posicion en y en la que va a empezar a dibujar el boton

    int color_1=10;
    int color_2=10;
    int color_3=10;

    if(seleccion_actual == BOTON_1)
        color_1=13;

    if(seleccion_actual == BOTON_2)
        color_2=13;

    if(seleccion_actual == BOTON_3)
        color_3=13;

    dibujar_rectangulo(x, y, ANCHO_BOTON, ALTO_BOTON,color_1);
    dibujar_rectangulo(x, y + SEPARACION_BOTONES, ANCHO_BOTON, ALTO_BOTON, color_2);
    dibujar_rectangulo(x , y+SEPARACION_BOTONES*2, ANCHO_BOTON, ALTO_BOTON, color_3);

    gbt_volcar_backbuffer();// Vuelca los píxeles del backbuffer en la ventana.

}
