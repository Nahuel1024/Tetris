#include "pantallainicio.h"
#include "pantalla.h"
#include "letras.h"
#include "paletacolor.h"
#define ANCHO_PANEL_IZQ      160
#define ALTO_PANEL_IZQ       220
#define ANCHO_PANEL_DER      160
#define ALTO_PANEL_DER       220
#define COLOR_FONDO_HUD      8
#define COLOR_BORDE          14
#define COLOR_TEXTO          15
#define COLOR_TITULO         13

static void dibujar_borde(int x,int y,int ancho,int alto,int color)
{
    for(int i = 0; i < ancho; i++)
    {
        gbt_dibujar_pixel(x + i,y,color); //Borde Superior
    }
    for(int i = 0; i < ancho; i++)
    {
        gbt_dibujar_pixel(x + i,y + alto - 1,color); //Borde Inferior
    }
    for(int i = 0; i < alto; i++)
    {
        gbt_dibujar_pixel(x,y + i,color); //Borde Izquierda
    }
    for(int i = 0; i < alto; i++)
    {
        gbt_dibujar_pixel(x + ancho - 1,y + i,color); //Borde Derecha
    }
}
static void dibujar_panel(int x,int y,int ancho,int alto)  //Dibuja Paneles
{
    dibujar_rectangulo(x,y,ancho,alto,COLOR_FONDO_HUD);
    dibujar_borde(x,y,ancho,alto,COLOR_BORDE);
}
static int centrar_texto(int ancho_panel,int cantidad_letras)
{
    return (ancho_panel - (cantidad_letras * 10)) / 2; //Centra el texto
}
void dibujar_hud(int margen_horizontal,int margen_vertical,int ancho_tablero) //Dibujamos el hud de la pantalla de juego
{
    int x_panel_izq =margen_horizontal - ANCHO_PANEL_IZQ - 30;
    int y_panel_izq =margen_vertical;
    int x_panel_der =margen_horizontal + ancho_tablero + 30;
    int y_panel_der =margen_vertical;
    dibujar_panel(x_panel_izq,y_panel_izq,ANCHO_PANEL_IZQ,ALTO_PANEL_IZQ); //1. PANEL IZQUIERDO
    dibujar_texto(x_panel_izq +centrar_texto(ANCHO_PANEL_IZQ, 6),y_panel_izq + 15,"PUNTOS",COLOR_TITULO); // 2. Titulos de panel izquierdo
    dibujar_rectangulo(x_panel_izq + 10,y_panel_izq + 30,ANCHO_PANEL_IZQ - 20,2,COLOR_BORDE); // 3. Dibuja una linea estetica al titulo
    dibujar_texto(x_panel_izq + 35,y_panel_izq + 60,"0001250",COLOR_TEXTO); // 4. Dibujar el puntaje
    dibujar_texto(x_panel_izq + 15,y_panel_izq + 100,"PROXIMO TETRO",COLOR_TITULO); // 5. Dibujamos promixo titulo
    dibujar_rectangulo(x_panel_izq + 10,y_panel_izq + 114,ANCHO_PANEL_IZQ - 20,2,COLOR_BORDE); // 6.Dibuja una linea estetica al titulo
    int base_x = x_panel_izq + 60;
    int base_y = y_panel_izq + 150;
    /* PIEZA T */
    dibujar_cuadrado(base_x,base_y,2,TAM_CELDA);       //7. Hay que dibujar el proximo tetromino

    dibujar_cuadrado(base_x + TAM_CELDA,base_y,2,TAM_CELDA);

    dibujar_cuadrado(base_x + TAM_CELDA * 2,base_y,2,TAM_CELDA);

    dibujar_cuadrado(base_x + TAM_CELDA, base_y + TAM_CELDA,2,TAM_CELDA);

    dibujar_panel(x_panel_der,y_panel_der,ANCHO_PANEL_DER,ALTO_PANEL_DER); // 1. Dibuja panel derecho

    dibujar_texto(x_panel_der + centrar_texto(ANCHO_PANEL_DER, 10),y_panel_der + 15,"TETROMINOS",COLOR_TITULO); // 2. Dibuja titulo en el panel derecho

    dibujar_rectangulo(x_panel_der + 10,y_panel_der + 30,ANCHO_PANEL_DER - 20,2,COLOR_BORDE); // 3. Dibuja una linea estetica al titulo
               //4. Tenemos que dibujar cada tetromino y un contador con la cantidad de veces que fueron saliendo cada uno
}
