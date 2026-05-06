#ifndef PANTALLA_H_INCLUDED
#define PANTALLA_H_INCLUDED

// Constantes de resoluciones de pantalla
#define ANCHO_CGA 320
#define ALTO_CGA 200
#define ANCHO_VGA 640
#define ALTO_VGA 480

// Factor de escala visual para que la ventana no se vea minúscula en monitores modernos
#define TAM_ESCALA 2

// Dimensiones de la matriz del juego (22 filas x 10 columnas)
// Nota: En el Tetris clásico, las 2 primeras filas suelen estar ocultas (zona de spawn).
#define FILAS 22
#define COLUMNAS 10

// Prototipos de funciones:
// Crea la ventana del juego según la resolución elegida.
void iniciar_pantalla(int reso);

// Recorre la matriz lógica del tablero y dibuja los bloques fijos.
void dibujar_matriz(int ini_x, int ini_y);

// Dibuja la pieza que está cayendo actualmente en su posición correspondiente.
void dibujar_pieza(int pieza[4][4], int pos_x, int pos_y, int ini_x, int ini_y);

// Orquestador principal de dibujo: limpia la pantalla, dibuja el fondo, tablero y pieza.
void dibujar(int pieza[4][4], int pos_x, int pos_y);

// Dibuja un rectángulo sólido píxel a píxel (usado para el fondo del tablero).
void dibujar_rectangulo(int x, int y, int ancho, int alto, int color);

// Dibuja un cuadrado de tamaño 'tam' (usado para cada celda/bloque individual).
void dibujar_cuadrado(int x,int y,int color,int tam);

#endif // PANTALLA_H_INCLUDED
