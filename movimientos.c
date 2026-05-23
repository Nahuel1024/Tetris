#include "movimientos.h"

void mover_derecha(const t_tablero *tablero, t_tetromino *tetromino)
{
    t_coordenadas coordenadas_mino;

    for (int i = 0; i < CANTIDAD_MINOS; i++)
    {
        coordenadas_inicializar(&coordenadas_mino, tetromino->mino[i].coordenadas.fila, tetromino->mino[i].coordenadas.columna);
        if (coordenadas_mino.columna + 1 == CANTIDAD_COLUMNAS ||
                tablero->celda[coordenadas_mino.fila][coordenadas_mino.columna + 1].ocupado) //Verificamos si algun bloque dibujado del tetromino se sale de nuestro rango de tablero a la derecha
            return; //Si se sale, no realiza el movimiento
    }

    for (int i = 0; i < CANTIDAD_MINOS; i++) // Si el movimiento se puede realizar, desplaza todos los bloques una columna a la derecha
    {
        tetromino->mino[i].coordenadas.columna++;
    }
}

void mover_izquierda(const t_tablero *tablero, t_tetromino *tetromino) //Funciona de la misma forma pero ahora verifica con la COLUMNA = 0
{
    t_coordenadas coordenadas_mino;

    for (int i = 0; i < CANTIDAD_MINOS; i++)
    {
        coordenadas_inicializar(&coordenadas_mino, tetromino->mino[i].coordenadas.fila, tetromino->mino[i].coordenadas.columna);
        if (tetromino->mino[i].coordenadas.columna - 1 < 0 ||
                tablero->celda[coordenadas_mino.fila][coordenadas_mino.columna - 1].ocupado)
            return;
    }

    for (int i = 0; i < CANTIDAD_MINOS; i++)
    {
        tetromino->mino[i].coordenadas.columna--;
    }
}

bool girar(const t_tablero *tablero, t_tetromino *tetromino)
{
    if(tetromino->pieza == 'O')
        return false;

    unsigned nueva_fila, nueva_columna, fila_actual, columna_actual, i;

    const unsigned
    fila_pivote =  tetromino->mino[MINO_PIVOTE].coordenadas.fila,
    columna_pivote = tetromino->mino[MINO_PIVOTE].coordenadas.columna;

    t_coordenadas nuevas_coordenadas[CANTIDAD_MINOS - 1], auxiliar;
    t_coordenadas *puntero_a_coordenadas = nuevas_coordenadas;

    /// El mino pivote será el tercero (el único que no rota)
    for(i = 0; i < CANTIDAD_MINOS; i++)
    {
        if(i != MINO_PIVOTE)
        {
            fila_actual = tetromino->mino[i].coordenadas.fila;
            columna_actual = tetromino->mino[i].coordenadas.columna;
            nueva_fila = fila_pivote + (columna_actual - columna_pivote);
            nueva_columna = columna_pivote - (fila_actual - fila_pivote);
            coordenadas_inicializar(&auxiliar, nueva_fila, nueva_columna);
            if(!coordenadas_dentro_del_tablero(tablero, &auxiliar) ||
                    !coordenadas_libres(tablero, &auxiliar))
                return false;
            memcpy(puntero_a_coordenadas, &auxiliar, sizeof(t_coordenadas));
            puntero_a_coordenadas++;
        }
    }

    puntero_a_coordenadas = nuevas_coordenadas;

    for(i = 0; i < CANTIDAD_MINOS; i++)
    {
        if(i != MINO_PIVOTE)
        {
            memcpy(&tetromino->mino[i].coordenadas, puntero_a_coordenadas, sizeof(t_coordenadas));
            puntero_a_coordenadas++;
        }
    }

    return true;
}

int temporizador_movimientos_caida(t_tablero *tablero, t_tetromino *tetromino, double tiempo_caida)
{
    tGBT_Temporizador *caida = NULL;
    caida = gbt_temporizador_crear(tiempo_caida);

    while(!gbt_temporizador_consumir(caida))
    {
        gbt_procesar_entrada();

        if(gbt_tecla_presionada(GBTK_DERECHA) || gbt_tecla_sostenida(GBTK_DERECHA))
        {
            mover_derecha(tablero, tetromino);
            dibujar(tablero, tetromino);
            tablero_mostrar(tablero, tetromino);
        }

        else if(gbt_tecla_presionada(GBTK_IZQUIERDA) || gbt_tecla_sostenida(GBTK_IZQUIERDA))
        {
            mover_izquierda(tablero, tetromino);
            dibujar(tablero, tetromino);
            tablero_mostrar(tablero, tetromino);
        }

        else if(gbt_tecla_presionada(GBTK_ARRIBA))
        {
            girar(tablero, tetromino);
            dibujar(tablero, tetromino);
            tablero_mostrar(tablero, tetromino);
        }

        else if(gbt_tecla_presionada(GBTK_ABAJO) || gbt_tecla_sostenida(GBTK_ABAJO))
        {
            gbt_temporizador_destruir(caida);
            return FORZAR_DESCENSO;
        }


        else if(gbt_tecla_presionada(GBTK_ESCAPE))
        {
            gbt_temporizador_destruir(caida);
            return SALIR;
        }

        gbt_esperar(100);
    }

    gbt_temporizador_destruir(caida);
    return CAIDA;
}

int temporizador_movimientos_tolerancia(t_tablero *tablero, t_tetromino *tetromino, double tiempo_tolerancia)
{
    tGBT_Temporizador *tolerancia = NULL;
    tolerancia = gbt_temporizador_crear(tiempo_tolerancia);

    while(!gbt_temporizador_consumir(tolerancia))
    {
        gbt_procesar_entrada();

        if(gbt_tecla_presionada(GBTK_DERECHA) || gbt_tecla_sostenida(GBTK_DERECHA))
        {
            mover_derecha(tablero, tetromino);
            dibujar(tablero, tetromino);
            tablero_mostrar(tablero, tetromino);
            if(tetromino_cayendo(tablero, tetromino))
            {
                gbt_temporizador_destruir(tolerancia);
                return CAIDA;
            }
        }

        else if(gbt_tecla_presionada(GBTK_IZQUIERDA) || gbt_tecla_sostenida(GBTK_IZQUIERDA))
        {
            mover_izquierda(tablero, tetromino);
            dibujar(tablero, tetromino);
            tablero_mostrar(tablero, tetromino);
            if(tetromino_cayendo(tablero, tetromino))
            {
                gbt_temporizador_destruir(tolerancia);
                return CAIDA;
            }
        }

        else if(gbt_tecla_presionada(GBTK_ARRIBA))
        {
            girar(tablero, tetromino);
            dibujar(tablero, tetromino);
            tablero_mostrar(tablero, tetromino);
            if(tetromino_cayendo(tablero, tetromino))
            {
                gbt_temporizador_destruir(tolerancia);
                return CAIDA;
            }
        }

        else if(gbt_tecla_presionada(GBTK_ESCAPE))
        {
            gbt_temporizador_destruir(tolerancia);
            return SALIR;
        }

        gbt_esperar(100);
    }

    gbt_temporizador_destruir(tolerancia);
    return FIJADO;
}
