#include <stdio.h>
#include "GBT/gbt.h"

int main()
{
    if (gbt_iniciar() != 0) {
        printf("Error al iniciar la ventana\n");
        return -1;
    }

    if (gbt_crear_ventana("Creo ventana", 320, 200, 2) != 0) {
        printf("Error al crear ventana\n");
        return -1;
    }

    while (1) {
        gbt_procesar_entrada();
        gbt_volcar_backbuffer();
    }

    return 0;
}
