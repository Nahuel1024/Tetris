#ifndef PANTALLA_H_INCLUDED
#define PANTALLA_H_INCLUDED
#define ANCHO_CGA 320
#define ALTO_CGA 200
#define ANCHO_VGA 640
#define ALTO_VGA 480
#define TAM_ESCALA 2
#define FILAS 22
#define COLUMNAS 10


void iniciar_pantalla(int reso);
void dibujar_matriz(int ini_x, int ini_y);
void dibujar_pieza(int pieza[4][4], int pos_x, int pos_y, int ini_x, int ini_y);
void dibujar(int pieza[4][4], int pos_x, int pos_y);
void dibujar_rectangulo(int x, int y, int ancho, int alto, int color);
void dibujar_cuadrado(int x,int y,int color,int tam);
#endif // PANTALLA_H_INCLUDED
