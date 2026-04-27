/*
Apellido: Rosas, Nahuel
DNI: 42656246
Usuario: Nahuel1024
Entrega: Sí
Apellido:
DNI:
Usuario:
Entrega:
Apellido:
DNI:
Usuario:
Entrega:
*/
#include "GBT/gbt.h"
#include "pantalla.h"
#define RESO 0 //   1 Iniciar VGA, 0 Inicia CGA

int main()
{
    if(gbt_iniciar() != 0)
        return -1;

    iniciar_pantalla(RESO); // 0 CGA, 1 VGA. Se puede cambiar

    while(1)
    {
        gbt_procesar_entrada();

        dibujar();

        // después vamos a meter lógica acá

        gbt_esperar(16);
    }

    gbt_cerrar();
    return 0;
}
