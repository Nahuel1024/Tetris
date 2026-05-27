#include "fuentes.h"
#include "pantalla_inicio.h"
#include "fuentes.h"
#include "primitivas.h"
#include "menu.h"
#include "layout.h"

void dibujar_pantalla(const t_layout *layout, const int seleccion_actual, int reso, t_letra *fuente)
{
    int ancho_sistema;
    int alto_sistema;

    if(reso == 0)
    {
        ancho_sistema = ANCHO_CGA;
        alto_sistema = ALTO_CGA;
    }
    else
    {
        ancho_sistema = ANCHO_VGA;
        alto_sistema = ALTO_VGA;
    }

    gbt_borrar_backbuffer(BORDE); // fondo negro

    int x= (ancho_sistema-ANCHO_CONSOLA)/2; //posicion en x en la que va a empezar a dibujar
    int y= (alto_sistema-ALTO_CONSOLA)/2 - OFFSET;   //posicion en y en la que va a empezar a dibujar

    int X0_PANTALLA=(ANCHO_CONSOLA-ANCHO_PANTALLA)/2;
    int Y0_PANTALLA=(ALTO_CONSOLA-ALTO_PANTALLA)/2;

    int X0_CIRCULOB1_CONSOLA= (X0_PANTALLA-ANCHO_CIRCULO_CONSOLA)/2;
    int X0_CIRCULOB2_CONSOLA =ANCHO_CONSOLA- X0_CIRCULOB1_CONSOLA- ANCHO_CIRCULO_CONSOLA;
    int Y0_CIRCULOB_CONSOLA= Y0_PANTALLA +(ALTO_PANTALLA-ALTO_CIRCULO_CONSOLA)/2;
    /* -------------------------
       CUERPO PRINCIPAL
    ------------------------- */

    dibujar_rectangulo(layout,x, y, ANCHO_CONSOLA, ALTO_CONSOLA,COLOR_CONSOLA);

    /* -------------------------
       ESQUINA SUPERIOR IZQUIERDA
    ------------------------- */

    int i;
    int j;

    i=0;

    while(i <= Y0_PANTALLA)
    {
        j = 0;

        while(j <= X0_CIRCULOB1_CONSOLA-i)
        {
            dibujar_rectangulo(layout, x + j, y + i, BLOQUE, BLOQUE, BORDE); //cada “pixel lógico” se vuelve un bloque visible
            j+= BLOQUE;
        }

        i+= BLOQUE;
    }

    /* -------------------------
       ESQUINA SUPERIOR DERECHA
    ------------------------- */

    i = 0;

    while(i <= Y0_PANTALLA)
    {
        j = X0_CIRCULOB2_CONSOLA + ANCHO_CIRCULO_CONSOLA-BLOQUE+ i;

        while(j <= ANCHO_CONSOLA)
        {
            dibujar_rectangulo(layout, x + j, y + i, BLOQUE, BLOQUE, BORDE);

            j += BLOQUE;
        }
        i += BLOQUE;
    }
    /* -------------------------
       ESQUINA INFERIOR IZQUIERDA
    ------------------------- */

    i= ALTO_CONSOLA - BLOQUE;
    int acum=0;

    while(i >= Y0_PANTALLA+ALTO_PANTALLA)
    {
        j=0;

        while(j <= X0_CIRCULOB1_CONSOLA - acum)
        {
            dibujar_rectangulo(layout,x + j, y + i, BLOQUE, BLOQUE, BORDE);

            j+= BLOQUE;

        }

        acum+= BLOQUE;
        i-= BLOQUE;
    }

    /* -------------------------
       ESQUINA INFERIOR DERECHA
    ------------------------- */
    i = ALTO_CONSOLA;
    acum = 0;

    while(i >= Y0_PANTALLA + ALTO_PANTALLA)
    {
        j = X0_CIRCULOB2_CONSOLA + ANCHO_CIRCULO_CONSOLA-BLOQUE+acum;

        while(j <= ANCHO_CONSOLA)
        {
            dibujar_rectangulo(layout,x + j, y + i, BLOQUE, BLOQUE, BORDE);
            j += BLOQUE;
        }

        acum += BLOQUE;
        i -= BLOQUE;
    }

    /* -------------------------
       PANTALLA
    ------------------------- */

    dibujar_rectangulo(layout, x+ X0_PANTALLA, y+ Y0_PANTALLA, ANCHO_PANTALLA, ALTO_PANTALLA, COLOR_PANTALLA);

    int cant_caracteres_pp= strlen("TETRIS");
    int ancho_letra_pp= CANT_C_FUENTES * BLOQUE;
    int ancho_caracter_pp= ancho_letra_pp + ESPACIO;
    int ancho_texto_pp= (cant_caracteres_pp * ancho_caracter_pp)- ESPACIO;
    int alto_texto= CANT_F_FUENTEG * BLOQUE;

    int x0_texto= x + X0_PANTALLA + (ANCHO_PANTALLA - ancho_texto_pp)/2;
    int y0_texto= y + Y0_PANTALLA + (ALTO_PANTALLA - alto_texto)/2;

    dibujar_caracter(layout, fuente, x0_texto, y0_texto, 'T', Z, FUENTE_8_16);
    dibujar_caracter(layout, fuente, x0_texto+ancho_caracter_pp, y0_texto, 'E', L, FUENTE_8_16);
    dibujar_caracter(layout, fuente, x0_texto+ancho_caracter_pp*2, y0_texto, 'T', O, FUENTE_8_16);
    dibujar_caracter(layout, fuente, x0_texto+ancho_caracter_pp*3, y0_texto, 'R', S, FUENTE_8_16);
    dibujar_caracter(layout, fuente, x0_texto+ancho_caracter_pp*4, y0_texto, 'I', J, FUENTE_8_16);
    dibujar_caracter(layout, fuente, x0_texto+ancho_caracter_pp*5, y0_texto, 'S', T, FUENTE_8_16);

    /* -------------------------
       BOTON IZQUIERDO
    ------------------------- */

    //dibujo primero el circulo gris de fondo

    dibujar_circulo(layout, x+X0_CIRCULOB1_CONSOLA, y+Y0_CIRCULOB_CONSOLA, ANCHO_CIRCULO_CONSOLA, ALTO_CIRCULO_CONSOLA,COLOR_CIRCULO);
    // Comentario: podria haber mandado "alto" tambien porque valen lo mismo!

    //dibujo los botones de colores

    dibujar_botones(layout,x, y, X0_CIRCULOB1_CONSOLA,Y0_CIRCULOB_CONSOLA);

    /* -------------------------
       BOTON DERECHO
    ------------------------- */

    //dibujo primero el circulo gris de fondo

    dibujar_circulo(layout, x+X0_CIRCULOB2_CONSOLA,y+Y0_CIRCULOB_CONSOLA, ANCHO_CIRCULO_CONSOLA, ALTO_CIRCULO_CONSOLA,COLOR_CIRCULO);
    //  Comentario: podria haber mandado "alto" tambien porque valen lo mismo!


    // dibujo el boton en forma de cruz o cruceta

    dibujar_boton_cruz(layout, x, y, X0_CIRCULOB2_CONSOLA, Y0_CIRCULOB_CONSOLA);

    int X0_BOTONES_MENU= (ancho_sistema -ANCHO_BOTON)/2;
    int Y0_BOTONES_MENU= y + ALTO_CONSOLA + SEPARACION_BOTONES;

    menu_dibujar(layout, seleccion_actual, X0_BOTONES_MENU, Y0_BOTONES_MENU, fuente);

    gbt_volcar_backbuffer();// Vuelca los píxeles del backbuffer en la ventana.

}
/*
void dibujar_sombras()
{

}
*/
void dibujar_circulo(const t_layout *layout, int pos_ini_x, int pos_ini_y, int ancho, int alto, int color)
{

    // fila superior
    dibujar_rectangulo(layout,pos_ini_x + BLOQUE*3, pos_ini_y, ancho-BLOQUE*6, BLOQUE*3, color);

    dibujar_rectangulo(layout,pos_ini_x + (BLOQUE*3-BLOQUE), pos_ini_y + BLOQUE, ancho - BLOQUE*4, BLOQUE*3, color);

    dibujar_rectangulo(layout,pos_ini_x + (BLOQUE*3-BLOQUE*2), pos_ini_y + BLOQUE*2, ancho - BLOQUE*2, BLOQUE*3, color);


    dibujar_rectangulo(layout,pos_ini_x, pos_ini_y + BLOQUE*3, ancho, BLOQUE*3, color);
    dibujar_rectangulo(layout,pos_ini_x, pos_ini_y + BLOQUE*4, ancho, BLOQUE*3, color);
    dibujar_rectangulo(layout,pos_ini_x, pos_ini_y + BLOQUE*5, ancho, BLOQUE*3, color);
    dibujar_rectangulo(layout,pos_ini_x, pos_ini_y + BLOQUE*6, ancho, BLOQUE*3, color);
    dibujar_rectangulo(layout,pos_ini_x, pos_ini_y + BLOQUE*7, ancho, BLOQUE*3, color);
    dibujar_rectangulo(layout,pos_ini_x, pos_ini_y + BLOQUE*8, ancho, BLOQUE*3, color);
    dibujar_rectangulo(layout,pos_ini_x, pos_ini_y + BLOQUE*9, ancho, BLOQUE*3, color);


    dibujar_rectangulo(layout,pos_ini_x + (BLOQUE*3-BLOQUE*2),pos_ini_y + BLOQUE*10, ancho - BLOQUE*2, BLOQUE*3, color);

    dibujar_rectangulo(layout,pos_ini_x + (BLOQUE*3-BLOQUE), pos_ini_y + BLOQUE*11 , ancho - BLOQUE*4, BLOQUE*3, color);

    dibujar_rectangulo(layout,pos_ini_x + BLOQUE*3, pos_ini_y + BLOQUE*12, ancho-BLOQUE*6, BLOQUE*3, color);

}
void dibujar_boton_cruz(const t_layout *layout, int x, int y, int x0, int y0)
{
    dibujar_rectangulo(layout,x+ x0 + X0_LIMITE_INI + ANCHO_BOTON_CRUZ, y+ y0 + Y0_LIMITE_INI, ANCHO_BOTON_CRUZ, ALTO_BOTON_CRUZ, BOTON_ROJO);
    dibujar_rectangulo(layout,x+ x0 + X0_LIMITE_INI, y+ y0 + ANCHO_BOTON_CRUZ+3, ALTO_BOTON_CRUZ, ANCHO_BOTON_CRUZ, BOTON_ROJO);
}
void dibujar_botones(const t_layout *layout, int x, int y, int x0,int y0) //ESTAN A LA DERECHA DE LA PANTALLA DE LA CONSOLA
{
    dibujar_rectangulo(layout,x+ x0 + X0_LIMITE_INI +ANCHO_BOTONES, y+ y0 + Y0_LIMITE_INI, ANCHO_BOTONES, ALTO_BOTONES, BOTON_ROJO);
    dibujar_rectangulo(layout,x+ x0 + X0_LIMITE_INI, y+ y0 + Y0_LIMITE_INI + ALTO_BOTONES, ANCHO_BOTONES, ALTO_BOTONES, BOTON_CELESTE);
    dibujar_rectangulo(layout,x+ x0 + X0_LIMITE_INI + ANCHO_BOTONES*2, y+ y0 + Y0_LIMITE_INI + ALTO_BOTONES, ANCHO_BOTONES, ALTO_BOTONES, BOTON_AMARILLO);
    dibujar_rectangulo(layout,x+ x0 + X0_LIMITE_INI + ANCHO_BOTONES, y+ y0 + Y0_LIMITE_INI + ALTO_BOTONES*2, ANCHO_BOTONES, ALTO_BOTONES, BOTON_VERDE);
}

/// esto en el caso de los botones se llama luego de menu_dibujar.
/// en el caso de dibujar el titulo, se llama luego de dibujar pantalla.
