#ifndef PANTALLA_INICIO_H_INCLUDED
#define PANTALLA_INICIO_H_INCLUDED

#include "fuentes.h"
#include "pantalla_inicio.h"
#include "fuentes.h"
#include "primitivas.h"
#include "menu.h"
#include "layout.h"

//BASE DE LA CONSOLA
#define ANCHO_CONSOLA 192
#define ALTO_CONSOLA 90
#define COLOR_CONSOLA 10
#define OFFSET 30

//FONDO CIRCULAR DE BOTONES DE LA CONSOLA
#define ALTO_CIRCULO_CONSOLA 24
#define ANCHO_CIRCULO_CONSOLA 30
#define COLOR_CIRCULO 13

//BOTONES
#define ALTO_BOTONES 8
#define ANCHO_BOTONES 8
#define ANCHO_LIMITE_BOTONES 18 //dentro de esos 18x18 van a estar los botones entran 9, pero se pintan o no.
#define ALTO_LIMITE_BOTONES 18
#define X0_LIMITE_INI 3
#define Y0_LIMITE_INI 3

//BOTON CRUZ
#define ANCHO_BOTON_CRUZ 8
#define ALTO_BOTON_CRUZ 24

//COLORES DE CADA BOTON
#define BOTON_ROJO 6
#define BOTON_VERDE 3
#define BOTON_CELESTE 0
#define BOTON_AMARILLO 1

//PANTALLA DE LA CONSOLA
#define ALTO_PANTALLA 60
#define ANCHO_PANTALLA 100

#define COLOR_PANTALLA 12
#define COLOR_SOMBRA 11
#define BLOQUE 2

// Los X0 e Y0 se sacan haciendo la resta entre anchos y altos, dividido 2.
//Por ejemplo, con X0_LIMITE_INI hice el ANCHO DEL FONDO CIRCULAR (ANCHO_CIRCULO_CONSOLA)
//de los botones MENOS el ANCHO DEL LIMITE DE LOS BOTONES (ANCHO_LIMITE_BOTONES), todo eso /2.
//Con esos parametros dibujo centrado.

void dibujar_pantalla(const t_layout *layout, const int seleccion_actual, int reso, t_letra *fuente); //va a llamar a las funciones de dibujo de la consola en orden
void dibujar_circulo(const t_layout *layout, int pos_ini_x, int pos_ini_y, int ancho, int alto, int color);
void dibujar_boton_cruz(const t_layout *layout, int x, int y, int x0, int y0);
void dibujar_botones(const t_layout *layout, int x, int y, int x0, int y0);



#endif // PANTALLA_INICIO_H_INCLUDED
