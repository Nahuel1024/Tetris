#ifndef FUENTES_H_INCLUDED
#define FUENTES_H_INCLUDED

#include "layout.h"
#define CANT_F_FUENTEC 8
#define CANT_C_FUENTES 8
#define CANT_F_FUENTEG 16
#define CANT_CARAC 38 ///abecedario,num 0-9, ! y :}
#define FUENTE_8_8 0
#define FUENTE_8_16 1
#define ESPACIO 1
#define COLOR_TEXTO_BOTON 13

typedef struct
{
    char caracter;

    unsigned char fuente8_8[CANT_F_FUENTEC];

    unsigned char fuente8_16[CANT_F_FUENTEG];

} t_letra;

void fuente_inicializar(t_letra *fuente);
void convertir_fuente8_16(t_letra *fuente, int cant_c);
void dibujar_caracter(const t_layout *layout, t_letra *fuente, int x, int y, char caracter, int color, int tipo_de_fuente);
int buscar_letra(t_letra *fuente, char caracter);
void dibujar_fuente(const t_layout *layout, t_letra *fuente, int x, int y, char *texto, int tipo_de_fuente);
#endif // FUENTES_H_INCLUDED
