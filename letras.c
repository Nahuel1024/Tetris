#include "letras.h"
#include "GBT/gbt.h"
//LETRAS 8X8

static unsigned char letra_A[8] =
{
    0x3C,
    0x66,
    0xC3,
    0xFF,
    0xC3,
    0xC3,
    0xC3,
    0x00
};

static unsigned char letra_C[8] =
{
    0x3C,
    0x66,
    0xC0,
    0xC0,
    0xC0,
    0x66,
    0x3C,
    0x00
};
static unsigned char letra_U[8] =
{
    0xC6,
    0xC6,
    0xC6,
    0xC6,
    0xC6,
    0xC6,
    0x7C,
    0x00
};

static unsigned char letra_E[8] =
{
    0xFE,
    0xC0,
    0xC0,
    0xFC,
    0xC0,
    0xC0,
    0xFE,
    0x00
};

static unsigned char letra_G[8] =
{
    0x3C,
    0x66,
    0xC0,
    0xCF,
    0xC3,
    0x66,
    0x3C,
    0x00
};

static unsigned char letra_I[8] =
{
    0x7E,
    0x18,
    0x18,
    0x18,
    0x18,
    0x18,
    0x7E,
    0x00
};

static unsigned char letra_M[8] =
{
    0xC3,
    0xE7,
    0xFF,
    0xDB,
    0xC3,
    0xC3,
    0xC3,
    0x00
};

static unsigned char letra_N[8] =
{
    0xC3,
    0xE3,
    0xF3,
    0xDB,
    0xCF,
    0xC7,
    0xC3,
    0x00
};

static unsigned char letra_O[8] =
{
    0x3C,
    0x66,
    0xC3,
    0xC3,
    0xC3,
    0x66,
    0x3C,
    0x00
};

static unsigned char letra_P[8] =
{
    0xFC,
    0xC6,
    0xC6,
    0xFC,
    0xC0,
    0xC0,
    0xC0,
    0x00
};

static unsigned char letra_R[8] =
{
    0xFC,
    0xC6,
    0xC6,
    0xFC,
    0xD8,
    0xCC,
    0xC6,
    0x00
};

static unsigned char letra_S[8] =
{
    0x7E,
    0xC0,
    0xC0,
    0x7C,
    0x06,
    0x06,
    0xFC,
    0x00
};

static unsigned char letra_T[8] =
{
    0xFF,
    0x18,
    0x18,
    0x18,
    0x18,
    0x18,
    0x18,
    0x00
};

static unsigned char letra_X[8] =
{
    0xC3,
    0x66,
    0x3C,
    0x18,
    0x3C,
    0x66,
    0xC3,
    0x00
};

//NUMEROS

static unsigned char numero_0[8] =
{
    0x3C,
    0x66,
    0xCE,
    0xD6,
    0xE6,
    0x66,
    0x3C,
    0x00
};

static unsigned char numero_1[8] =
{
    0x18,
    0x38,
    0x18,
    0x18,
    0x18,
    0x18,
    0x7E,
    0x00
};

static unsigned char numero_2[8] =
{
    0x3C,
    0x66,
    0x06,
    0x1C,
    0x30,
    0x60,
    0x7E,
    0x00
};

static unsigned char numero_3[8] =
{
    0x3C,
    0x66,
    0x06,
    0x1C,
    0x06,
    0x66,
    0x3C,
    0x00
};

static unsigned char numero_4[8] =
{
    0x0C,
    0x1C,
    0x3C,
    0x6C,
    0xFE,
    0x0C,
    0x0C,
    0x00
};

static unsigned char numero_5[8] =
{
    0x7E,
    0x60,
    0x7C,
    0x06,
    0x06,
    0x66,
    0x3C,
    0x00
};

static unsigned char numero_6[8] =
{
    0x3C,
    0x60,
    0x7C,
    0x66,
    0x66,
    0x66,
    0x3C,
    0x00
};

static unsigned char numero_7[8] =
{
    0x7E,
    0x06,
    0x0C,
    0x18,
    0x30,
    0x30,
    0x30,
    0x00
};

static unsigned char numero_8[8] =
{
    0x3C,
    0x66,
    0x66,
    0x3C,
    0x66,
    0x66,
    0x3C,
    0x00
};

static unsigned char numero_9[8] =
{
    0x3C,
    0x66,
    0x66,
    0x3E,
    0x06,
    0x0C,
    0x38,
    0x00
};

//DIBUJA BITMAP

static void dibujar_bitmap(int x,int y,unsigned char bitmap[8],int color)
{
    for(int fila = 0; fila < 8; fila++)
    {
        for(int col = 0; col < 8; col++)
        {
            if(bitmap[fila] & (1 << (7 - col)))
            {
                gbt_dibujar_pixel(x + col,y + fila,color);
            }
        }
    }
}

//DIBUJA UNA LETRA

void dibujar_letra(int x, int y, char c, int color)
{
    switch(c)
    {
        case 'A': dibujar_bitmap(x,y,letra_A,color); break;
        case 'C': dibujar_bitmap(x,y,letra_C,color); break;
        case 'E': dibujar_bitmap(x,y,letra_E,color); break;
        case 'G': dibujar_bitmap(x,y,letra_G,color); break;
        case 'I': dibujar_bitmap(x,y,letra_I,color); break;
        case 'M': dibujar_bitmap(x,y,letra_M,color); break;
        case 'N': dibujar_bitmap(x,y,letra_N,color); break;
        case 'O': dibujar_bitmap(x,y,letra_O,color); break;
        case 'U': dibujar_bitmap(x,y,letra_U,color); break;
        case 'P': dibujar_bitmap(x,y,letra_P,color); break;
        case 'R': dibujar_bitmap(x,y,letra_R,color); break;
        case 'S': dibujar_bitmap(x,y,letra_S,color); break;
        case 'T': dibujar_bitmap(x,y,letra_T,color); break;
        case 'X': dibujar_bitmap(x,y,letra_X,color); break;
        case '0': dibujar_bitmap(x,y,numero_0,color); break;
        case '1': dibujar_bitmap(x,y,numero_1,color); break;
        case '2': dibujar_bitmap(x,y,numero_2,color); break;
        case '3': dibujar_bitmap(x,y,numero_3,color); break;
        case '4': dibujar_bitmap(x,y,numero_4,color); break;
        case '5': dibujar_bitmap(x,y,numero_5,color); break;
        case '6': dibujar_bitmap(x,y,numero_6,color); break;
        case '7': dibujar_bitmap(x,y,numero_7,color); break;
        case '8': dibujar_bitmap(x,y,numero_8,color); break;
        case '9': dibujar_bitmap(x,y,numero_9,color); break;
        case ' ':
            break;
    }
}

//DIBUJA TEXTO
void dibujar_texto(int x,int y,const char *texto,int color)
{
    while(*texto)
    {
        dibujar_letra(x, y, *texto, color);

        x += 10;

        texto++;
    }
}
