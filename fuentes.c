#include "fuentes.h"
#include <string.h>
#include "pantalla_inicio.h"
#include "menu.h"
#include "primitivas.h"
#include <stdlib.h>

void fuente_inicializar(t_letra *fuente)
{

    //fuente 8x8

    fuente->caracter='A';

    fuente->fuente8_8[0] = 0x00;
    fuente->fuente8_8[1] = 0x18;
    fuente->fuente8_8[2] = 0x24;
    fuente->fuente8_8[3] = 0x3C;
    fuente->fuente8_8[4] = 0x24;
    fuente->fuente8_8[5] = 0x24;
    fuente->fuente8_8[6] = 0x24;
    fuente->fuente8_8[7] = 0x00;


    (fuente + 1)->caracter='B';

    (fuente + 1)->fuente8_8[0] = 0x00;
    (fuente + 1)->fuente8_8[1] = 0x18;
    (fuente + 1)->fuente8_8[2] = 0x24;
    (fuente + 1)->fuente8_8[3] = 0x38;
    (fuente + 1)->fuente8_8[4] = 0x24;
    (fuente + 1)->fuente8_8[5] = 0x24;
    (fuente + 1)->fuente8_8[6] = 0x38;
    (fuente + 1)->fuente8_8[7] = 0x00;


    (fuente + 2)->caracter = 'C';

    (fuente + 2)->fuente8_8[0] = 0x00;
    (fuente + 2)->fuente8_8[1] = 0x1C;
    (fuente + 2)->fuente8_8[2] = 0x20;
    (fuente + 2)->fuente8_8[3] = 0x20;
    (fuente + 2)->fuente8_8[4] = 0x20;
    (fuente + 2)->fuente8_8[5] = 0x20;
    (fuente + 2)->fuente8_8[6] = 0x1C;
    (fuente + 2)->fuente8_8[7] = 0x00;


    (fuente + 3)->caracter = 'D';

    (fuente + 3)->fuente8_8[0] = 0x00;
    (fuente + 3)->fuente8_8[1] = 0x38;
    (fuente + 3)->fuente8_8[2] = 0x24;
    (fuente + 3)->fuente8_8[3] = 0x24;
    (fuente + 3)->fuente8_8[4] = 0x24;
    (fuente + 3)->fuente8_8[5] = 0x24;
    (fuente + 3)->fuente8_8[6] = 0x38;
    (fuente + 3)->fuente8_8[7] = 0x00;


    (fuente + 4)->caracter = 'E';

    (fuente + 4)->fuente8_8[0] = 0x00;
    (fuente + 4)->fuente8_8[1] = 0x3C;
    (fuente + 4)->fuente8_8[2] = 0x20;
    (fuente + 4)->fuente8_8[3] = 0x38;
    (fuente + 4)->fuente8_8[4] = 0x20;
    (fuente + 4)->fuente8_8[5] = 0x20;
    (fuente + 4)->fuente8_8[6] = 0x3C;
    (fuente + 4)->fuente8_8[7] = 0x00;


    (fuente + 5)->caracter = 'F';

    (fuente + 5)->fuente8_8[0] = 0x00;
    (fuente + 5)->fuente8_8[1] = 0x3C;
    (fuente + 5)->fuente8_8[2] = 0x20;
    (fuente + 5)->fuente8_8[3] = 0x28;
    (fuente + 5)->fuente8_8[4] = 0x20;
    (fuente + 5)->fuente8_8[5] = 0x20;
    (fuente + 5)->fuente8_8[6] = 0x20;
    (fuente + 5)->fuente8_8[7] = 0x00;


    (fuente + 6)->caracter = 'G';

    (fuente + 6)->fuente8_8[0] = 0x00;
    (fuente + 6)->fuente8_8[1] = 0x18;
    (fuente + 6)->fuente8_8[2] = 0x24;
    (fuente + 6)->fuente8_8[3] = 0x20;
    (fuente + 6)->fuente8_8[4] = 0x2C;
    (fuente + 6)->fuente8_8[5] = 0x24;
    (fuente + 6)->fuente8_8[6] = 0x18;
    (fuente + 6)->fuente8_8[7] = 0x00;


    (fuente + 7)->caracter = 'H';

    (fuente + 7)->fuente8_8[0] = 0x00;
    (fuente + 7)->fuente8_8[1] = 0x24;
    (fuente + 7)->fuente8_8[2] = 0x24;
    (fuente + 7)->fuente8_8[3] = 0x3C;
    (fuente + 7)->fuente8_8[4] = 0x24;
    (fuente + 7)->fuente8_8[5] = 0x24;
    (fuente + 7)->fuente8_8[6] = 0x24;
    (fuente + 7)->fuente8_8[7] = 0x00;


    (fuente + 8)->caracter = 'I';

    (fuente + 8)->fuente8_8[0] = 0x00;
    (fuente + 8)->fuente8_8[1] = 0x38;
    (fuente + 8)->fuente8_8[2] = 0x10;
    (fuente + 8)->fuente8_8[3] = 0x10;
    (fuente + 8)->fuente8_8[4] = 0x10;
    (fuente + 8)->fuente8_8[5] = 0x10;
    (fuente + 8)->fuente8_8[6] = 0x38;
    (fuente + 8)->fuente8_8[7] = 0x00;


    (fuente + 9)->caracter = 'J';

    (fuente + 9)->fuente8_8[0] = 0x00;
    (fuente + 9)->fuente8_8[1] = 0x18;
    (fuente + 9)->fuente8_8[2] = 0x04;
    (fuente + 9)->fuente8_8[3] = 0x04;
    (fuente + 9)->fuente8_8[4] = 0x04;
    (fuente + 9)->fuente8_8[5] = 0x24;
    (fuente + 9)->fuente8_8[6] = 0x18;
    (fuente + 9)->fuente8_8[7] = 0x00;


    (fuente + 10)->caracter = 'K';

    (fuente + 10)->fuente8_8[0] = 0x00;
    (fuente + 10)->fuente8_8[1] = 0x24;
    (fuente + 10)->fuente8_8[2] = 0x28;
    (fuente + 10)->fuente8_8[3] = 0x30;
    (fuente + 10)->fuente8_8[4] = 0x28;
    (fuente + 10)->fuente8_8[5] = 0x24;
    (fuente + 10)->fuente8_8[6] = 0x24;
    (fuente + 10)->fuente8_8[7] = 0x00;


    (fuente + 11)->caracter = 'L';

    (fuente + 11)->fuente8_8[0] = 0x00;
    (fuente + 11)->fuente8_8[1] = 0x20;
    (fuente + 11)->fuente8_8[2] = 0x20;
    (fuente + 11)->fuente8_8[3] = 0x20;
    (fuente + 11)->fuente8_8[4] = 0x20;
    (fuente + 11)->fuente8_8[5] = 0x20;
    (fuente + 11)->fuente8_8[6] = 0x3C;
    (fuente + 11)->fuente8_8[7] = 0x00;


    (fuente + 12)->caracter = 'M';

    (fuente + 12)->fuente8_8[0] = 0x00;
    (fuente + 12)->fuente8_8[1] = 0x6C;
    (fuente + 12)->fuente8_8[2] = 0x54;
    (fuente + 12)->fuente8_8[3] = 0x54;
    (fuente + 12)->fuente8_8[4] = 0x44;
    (fuente + 12)->fuente8_8[5] = 0x44;
    (fuente + 12)->fuente8_8[6] = 0x44;
    (fuente + 12)->fuente8_8[7] = 0x00;


    (fuente + 13)->caracter = 'N';

    (fuente + 13)->fuente8_8[0] = 0x00;
    (fuente + 13)->fuente8_8[1] = 0x44;
    (fuente + 13)->fuente8_8[2] = 0x64;
    (fuente + 13)->fuente8_8[3] = 0x54;
    (fuente + 13)->fuente8_8[4] = 0x4C;
    (fuente + 13)->fuente8_8[5] = 0x44;
    (fuente + 13)->fuente8_8[6] = 0x44;
    (fuente + 13)->fuente8_8[7] = 0x00;


    (fuente + 14)->caracter = 'O';

    (fuente + 14)->fuente8_8[0] = 0x00;
    (fuente + 14)->fuente8_8[1] = 0x18;
    (fuente + 14)->fuente8_8[2] = 0x24;
    (fuente + 14)->fuente8_8[3] = 0x24;
    (fuente + 14)->fuente8_8[4] = 0x24;
    (fuente + 14)->fuente8_8[5] = 0x24;
    (fuente + 14)->fuente8_8[6] = 0x18;
    (fuente + 14)->fuente8_8[7] = 0x00;


    (fuente + 15)->caracter = 'P';

    (fuente + 15)->fuente8_8[0] = 0x00;
    (fuente + 15)->fuente8_8[1] = 0x18;
    (fuente + 15)->fuente8_8[2] = 0x24;
    (fuente + 15)->fuente8_8[3] = 0x24;
    (fuente + 15)->fuente8_8[4] = 0x38;
    (fuente + 15)->fuente8_8[5] = 0x20;
    (fuente + 15)->fuente8_8[6] = 0x20;
    (fuente + 15)->fuente8_8[7] = 0x00;


    (fuente + 16)->caracter = 'Q';

    (fuente + 16)->fuente8_8[0] = 0x00;
    (fuente + 16)->fuente8_8[1] = 0x38;
    (fuente + 16)->fuente8_8[2] = 0x44;
    (fuente + 16)->fuente8_8[3] = 0x44;
    (fuente + 16)->fuente8_8[4] = 0x44;
    (fuente + 16)->fuente8_8[5] = 0x48;
    (fuente + 16)->fuente8_8[6] = 0x34;
    (fuente + 16)->fuente8_8[7] = 0x00;


    (fuente + 17)->caracter = 'R';

    (fuente + 17)->fuente8_8[0] = 0x00;
    (fuente + 17)->fuente8_8[1] = 0x18;
    (fuente + 17)->fuente8_8[2] = 0x24;
    (fuente + 17)->fuente8_8[3] = 0x24;
    (fuente + 17)->fuente8_8[4] = 0x38;
    (fuente + 17)->fuente8_8[5] = 0x24;
    (fuente + 17)->fuente8_8[6] = 0x24;
    (fuente + 17)->fuente8_8[7] = 0x00;


    (fuente + 18)->caracter = 'S';

    (fuente + 18)->fuente8_8[0] = 0x00;
    (fuente + 18)->fuente8_8[1] = 0x1C;
    (fuente + 18)->fuente8_8[2] = 0x20;
    (fuente + 18)->fuente8_8[3] = 0x3C;
    (fuente + 18)->fuente8_8[4] = 0x04;
    (fuente + 18)->fuente8_8[5] = 0x04;
    (fuente + 18)->fuente8_8[6] = 0x38;
    (fuente + 18)->fuente8_8[7] = 0x00;


    (fuente + 19)->caracter = 'T';

    (fuente + 19)->fuente8_8[0] = 0x00;
    (fuente + 19)->fuente8_8[1] = 0x3E;
    (fuente + 19)->fuente8_8[2] = 0x08;
    (fuente + 19)->fuente8_8[3] = 0x08;
    (fuente + 19)->fuente8_8[4] = 0x08;
    (fuente + 19)->fuente8_8[5] = 0x08;
    (fuente + 19)->fuente8_8[6] = 0x08;
    (fuente + 19)->fuente8_8[7] = 0x00;


    (fuente + 20)->caracter = 'U';

    (fuente + 20)->fuente8_8[0] = 0x00;
    (fuente + 20)->fuente8_8[1] = 0x24;
    (fuente + 20)->fuente8_8[2] = 0x24;
    (fuente + 20)->fuente8_8[3] = 0x24;
    (fuente + 20)->fuente8_8[4] = 0x24;
    (fuente + 20)->fuente8_8[5] = 0x24;
    (fuente + 20)->fuente8_8[6] = 0x18;
    (fuente + 20)->fuente8_8[7] = 0x00;


    (fuente + 21)->caracter = 'V';

    (fuente + 21)->fuente8_8[0] = 0x00;
    (fuente + 21)->fuente8_8[1] = 0x44;
    (fuente + 21)->fuente8_8[2] = 0x44;
    (fuente + 21)->fuente8_8[3] = 0x44;
    (fuente + 21)->fuente8_8[4] = 0x44;
    (fuente + 21)->fuente8_8[5] = 0x28;
    (fuente + 21)->fuente8_8[6] = 0x10;
    (fuente + 21)->fuente8_8[7] = 0x00;


    (fuente + 22)->caracter = 'W';

    (fuente + 22)->fuente8_8[0] = 0x00;
    (fuente + 22)->fuente8_8[1] = 0x44;
    (fuente + 22)->fuente8_8[2] = 0x44;
    (fuente + 22)->fuente8_8[3] = 0x44;
    (fuente + 22)->fuente8_8[4] = 0x54;
    (fuente + 22)->fuente8_8[5] = 0x54;
    (fuente + 22)->fuente8_8[6] = 0x6C;
    (fuente + 22)->fuente8_8[7] = 0x00;


    (fuente + 23)->caracter = 'X';

    (fuente + 23)->fuente8_8[0] = 0x00;
    (fuente + 23)->fuente8_8[1] = 0x44;
    (fuente + 23)->fuente8_8[2] = 0x28;
    (fuente + 23)->fuente8_8[3] = 0x10;
    (fuente + 23)->fuente8_8[4] = 0x10;
    (fuente + 23)->fuente8_8[5] = 0x28;
    (fuente + 23)->fuente8_8[6] = 0x44;
    (fuente + 23)->fuente8_8[7] = 0x00;


    (fuente + 24)->caracter = 'Y';

    (fuente + 24)->fuente8_8[0] = 0x00;
    (fuente + 24)->fuente8_8[1] = 0x44;
    (fuente + 24)->fuente8_8[2] = 0x28;
    (fuente + 24)->fuente8_8[3] = 0x10;
    (fuente + 24)->fuente8_8[4] = 0x10;
    (fuente + 24)->fuente8_8[5] = 0x10;
    (fuente + 24)->fuente8_8[6] = 0x10;
    (fuente + 24)->fuente8_8[7] = 0x00;


    (fuente + 25)->caracter = 'Z';

    (fuente + 25)->fuente8_8[0] = 0x00;
    (fuente + 25)->fuente8_8[1] = 0x3C;
    (fuente + 25)->fuente8_8[2] = 0x04;
    (fuente + 25)->fuente8_8[3] = 0x08;
    (fuente + 25)->fuente8_8[4] = 0x10;
    (fuente + 25)->fuente8_8[5] = 0x20;
    (fuente + 25)->fuente8_8[6] = 0x3C;
    (fuente + 25)->fuente8_8[7] = 0x00;


    (fuente + 26)->caracter = '0';

    (fuente + 26)->fuente8_8[0] = 0x00;
    (fuente + 26)->fuente8_8[1] = 0x38;
    (fuente + 26)->fuente8_8[2] = 0x44;
    (fuente + 26)->fuente8_8[3] = 0x64;
    (fuente + 26)->fuente8_8[4] = 0x54;
    (fuente + 26)->fuente8_8[5] = 0x4C;
    (fuente + 26)->fuente8_8[6] = 0x38;
    (fuente + 26)->fuente8_8[7] = 0x00;


    (fuente + 27)->caracter = '1';

    (fuente + 27)->fuente8_8[0] = 0x00;
    (fuente + 27)->fuente8_8[1] = 0x18;
    (fuente + 27)->fuente8_8[2] = 0x08;
    (fuente + 27)->fuente8_8[3] = 0x08;
    (fuente + 27)->fuente8_8[4] = 0x08;
    (fuente + 27)->fuente8_8[5] = 0x08;
    (fuente + 27)->fuente8_8[6] = 0x08;
    (fuente + 27)->fuente8_8[7] = 0x00;


    (fuente + 28)->caracter = '2';

    (fuente + 28)->fuente8_8[0] = 0x00;
    (fuente + 28)->fuente8_8[1] = 0x38;
    (fuente + 28)->fuente8_8[2] = 0x44;
    (fuente + 28)->fuente8_8[3] = 0x08;
    (fuente + 28)->fuente8_8[4] = 0x10;
    (fuente + 28)->fuente8_8[5] = 0x20;
    (fuente + 28)->fuente8_8[6] = 0x7C;
    (fuente + 28)->fuente8_8[7] = 0x00;


    (fuente + 29)->caracter = '3';

    (fuente + 29)->fuente8_8[0] = 0x00;
    (fuente + 29)->fuente8_8[1] = 0x38;
    (fuente + 29)->fuente8_8[2] = 0x04;
    (fuente + 29)->fuente8_8[3] = 0x18;
    (fuente + 29)->fuente8_8[4] = 0x04;
    (fuente + 29)->fuente8_8[5] = 0x04;
    (fuente + 29)->fuente8_8[6] = 0x38;
    (fuente + 29)->fuente8_8[7] = 0x00;


    (fuente + 30)->caracter = '4';

    (fuente + 30)->fuente8_8[0] = 0x00;
    (fuente + 30)->fuente8_8[1] = 0x24;
    (fuente + 30)->fuente8_8[2] = 0x24;
    (fuente + 30)->fuente8_8[3] = 0x3C;
    (fuente + 30)->fuente8_8[4] = 0x04;
    (fuente + 30)->fuente8_8[5] = 0x04;
    (fuente + 30)->fuente8_8[6] = 0x04;
    (fuente + 30)->fuente8_8[7] = 0x00;


    (fuente + 31)->caracter = '5';

    (fuente + 31)->fuente8_8[0] = 0x00;
    (fuente + 31)->fuente8_8[1] = 0x38;
    (fuente + 31)->fuente8_8[2] = 0x40;
    (fuente + 31)->fuente8_8[3] = 0x70;
    (fuente + 31)->fuente8_8[4] = 0x08;
    (fuente + 31)->fuente8_8[5] = 0x08;
    (fuente + 31)->fuente8_8[6] = 0x70;
    (fuente + 31)->fuente8_8[7] = 0x00;


    (fuente + 32)->caracter = '6';

    (fuente + 32)->fuente8_8[0] = 0x00;
    (fuente + 32)->fuente8_8[1] = 0x38;
    (fuente + 32)->fuente8_8[2] = 0x40;
    (fuente + 32)->fuente8_8[3] = 0x70;
    (fuente + 32)->fuente8_8[4] = 0x48;
    (fuente + 32)->fuente8_8[5] = 0x48;
    (fuente + 32)->fuente8_8[6] = 0x38;
    (fuente + 32)->fuente8_8[7] = 0x00;


    (fuente + 33)->caracter = '7';

    (fuente + 33)->fuente8_8[0] = 0x00;
    (fuente + 33)->fuente8_8[1] = 0x70;
    (fuente + 33)->fuente8_8[2] = 0x08;
    (fuente + 33)->fuente8_8[3] = 0x10;
    (fuente + 33)->fuente8_8[4] = 0x20;
    (fuente + 33)->fuente8_8[5] = 0x20;
    (fuente + 33)->fuente8_8[6] = 0x20;
    (fuente + 33)->fuente8_8[7] = 0x00;


    (fuente + 34)->caracter = '8';

    (fuente + 34)->fuente8_8[0] = 0x00;
    (fuente + 34)->fuente8_8[1] = 0x38;
    (fuente + 34)->fuente8_8[2] = 0x44;
    (fuente + 34)->fuente8_8[3] = 0x38;
    (fuente + 34)->fuente8_8[4] = 0x44;
    (fuente + 34)->fuente8_8[5] = 0x44;
    (fuente + 34)->fuente8_8[6] = 0x38;
    (fuente + 34)->fuente8_8[7] = 0x00;


    (fuente + 35)->caracter = '9';

    (fuente + 35)->fuente8_8[0] = 0x00;
    (fuente + 35)->fuente8_8[1] = 0x30;
    (fuente + 35)->fuente8_8[2] = 0x48;
    (fuente + 35)->fuente8_8[3] = 0x78;
    (fuente + 35)->fuente8_8[4] = 0x08;
    (fuente + 35)->fuente8_8[5] = 0x48;
    (fuente + 35)->fuente8_8[6] = 0x30;
    (fuente + 35)->fuente8_8[7] = 0x00;

    (fuente + 36)->caracter = '!';

    (fuente + 36)->fuente8_8[0] = 0x00;
    (fuente + 36)->fuente8_8[1] = 0x20;
    (fuente + 36)->fuente8_8[2] = 0x20;
    (fuente + 36)->fuente8_8[3] = 0x20;
    (fuente + 36)->fuente8_8[4] = 0x20;
    (fuente + 36)->fuente8_8[5] = 0x00;
    (fuente + 36)->fuente8_8[6] = 0x20;
    (fuente + 36)->fuente8_8[7] = 0x00;


    (fuente + 37)->caracter = ':';

    (fuente + 37)->fuente8_8[0] = 0x00;
    (fuente + 37)->fuente8_8[1] = 0x10;
    (fuente + 37)->fuente8_8[2] = 0x10;
    (fuente + 37)->fuente8_8[3] = 0x00;
    (fuente + 37)->fuente8_8[4] = 0x00;
    (fuente + 37)->fuente8_8[5] = 0x10;
    (fuente + 37)->fuente8_8[6] = 0x10;
    (fuente + 37)->fuente8_8[7] = 0x00;

    convertir_fuente8_16(fuente, CANT_CARAC);
}
void convertir_fuente8_16(t_letra *fuente, int cant_c)
{
    for(int i=0; i< cant_c; i++)
    {
        for(int j=0; j<CANT_F_FUENTEC; j++)
        {
            (fuente+i)->fuente8_16[j * 2]= (fuente+i)->fuente8_8[j];

            (fuente+i)->fuente8_16[j * 2 + 1]= (fuente+i)->fuente8_8[j];
        }
    }
}

void dibujar_fuente(const t_layout *layout, t_letra *fuente, int x, int y, char *texto, int tipo_de_fuente)
{

    int i=0;
    int cant_caracteres=strlen(texto);
    int ancho_letra= CANT_C_FUENTES * BLOQUE;
    int ancho_caracter= ancho_letra + ESPACIO;
    int ancho_texto= (cant_caracteres * ancho_caracter) - ESPACIO;
    int alto_texto;

    if(tipo_de_fuente == FUENTE_8_8)
    {
        alto_texto = CANT_F_FUENTEC * BLOQUE;
    }

    if(tipo_de_fuente == FUENTE_8_16)
    {
        alto_texto= CANT_F_FUENTEG * BLOQUE;
    }

    int x0_texto= x + (ANCHO_BOTON - ancho_texto)/2;

    int y0_texto= y + (ALTO_BOTON - alto_texto)/2;

    while(*(texto+i)!= '\0')
    {
        dibujar_caracter(layout, fuente, x0_texto+i*ancho_caracter, y0_texto, *(texto+i), COLOR_TEXTO_BOTON, tipo_de_fuente);
        i++;
    }
}
void dibujar_caracter(const t_layout *layout, t_letra *fuente, int x, int y, char caracter, int color, int tipo_de_fuente)
{
    int i=0;
    int j=0;
    int cant_filas_fuente;

    int pos= buscar_letra(fuente, caracter);

    if(pos==-1)
        exit(1);

    if(tipo_de_fuente==FUENTE_8_8)
    {
        cant_filas_fuente=CANT_F_FUENTEC;
    }
    else
    {
        cant_filas_fuente=CANT_F_FUENTEG;
    }

    while(i < cant_filas_fuente)
    {
        j=0;

        while(j < CANT_C_FUENTES)
        {
            if(cant_filas_fuente == CANT_F_FUENTEC)
            {
                if((fuente+pos)->fuente8_8[i] & 1 << (7-j))
                {
                    dibujar_rectangulo(layout, x + j*BLOQUE, y + i*BLOQUE, BLOQUE, BLOQUE, color);
                }
            }
            else
            {
                if((fuente+pos)->fuente8_16[i] & 1 << (7-j))
                {
                    dibujar_rectangulo(layout, x + j*BLOQUE, y + i*BLOQUE, BLOQUE, BLOQUE, color);
                }
            }

            j++;
        }

        i++;
    }

}
int buscar_letra(t_letra *fuente, char caracter)
{
    int i = 0;

    while(i < CANT_CARAC)
    {
        if((fuente+i)->caracter == caracter)
            return i;

        i++;
    }

    return -1;
}
