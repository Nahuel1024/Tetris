#include "../Tetris/include/GBT/gbt_entrada.h"
#include "../Tetris/include/GBT/gbt_graficos.h"
#include "../Tetris/paletacolor.h"
#include "menu.h"
#include "../Tetris/pantalla.h"
#include "fuentes.h"
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
void menu_dibujar(const t_layout *layout, const int seleccion_actual, int x, int y, t_letra *fuente)
{
    int color_1=COLOR_BOTON_PREDETERMINADO;
    int color_2=COLOR_BOTON_PREDETERMINADO;
    int color_3=COLOR_BOTON_PREDETERMINADO;

    if(seleccion_actual == BOTON_1)
        color_1=COLOR_BOTON_SELECCIONADO;

    if(seleccion_actual == BOTON_2)
        color_2=COLOR_BOTON_SELECCIONADO;

    if(seleccion_actual == BOTON_3)
        color_3=COLOR_BOTON_SELECCIONADO;

    dibujar_rectangulo(x, y, ANCHO_BOTON, ALTO_BOTON,color_1);
    dibujar_fuente(layout, fuente, x, y, "JUGAR", FUENTE_8_8);

    dibujar_rectangulo(x, y + SEPARACION_BOTONES, ANCHO_BOTON, ALTO_BOTON, color_2);
    dibujar_fuente(layout, fuente, x, y + SEPARACION_BOTONES, "AJUSTES", FUENTE_8_8);

    dibujar_rectangulo(x , y + SEPARACION_BOTONES*2, ANCHO_BOTON, ALTO_BOTON, color_3);
    dibujar_fuente(layout, fuente, x, y + SEPARACION_BOTONES*2, "SALIR", FUENTE_8_8);

}
