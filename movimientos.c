/**
 * @file movimientos.c
 * @brief Implementacion de movimientos y temporizadores.
 *
 * Los temporizadores ya no llaman a dibujar() completo. En cada movimiento
 * redibujan solo fondo + tablero + pieza, evitando redibujar el HUD que
 * no cambia durante el desplazamiento lateral ni la rotacion.
 */

#include "movimientos.h"
#include "juego.h"

/* ========================================================================== */
/* MOVIMIENTOS BASICOS                                                        */
/* ========================================================================== */

void mover_derecha(const t_tablero *tablero, t_tetromino *tetromino)
{
    t_coordenadas coordenadas_mino;

    for(int i = 0; i < CANTIDAD_MINOS; i++)
    {
        coordenadas_inicializar(&coordenadas_mino,
                                tetromino->mino[i].coordenadas.fila,
                                tetromino->mino[i].coordenadas.columna);
        if(coordenadas_mino.columna + 1 == CANTIDAD_COLUMNAS ||
           tablero->celda[coordenadas_mino.fila][coordenadas_mino.columna + 1].ocupado)
            return;
    }

    for(int i = 0; i < CANTIDAD_MINOS; i++)
        tetromino->mino[i].coordenadas.columna++;
}

void mover_izquierda(const t_tablero *tablero, t_tetromino *tetromino)
{
    t_coordenadas coordenadas_mino;

    for(int i = 0; i < CANTIDAD_MINOS; i++)
    {
        coordenadas_inicializar(&coordenadas_mino,
                                tetromino->mino[i].coordenadas.fila,
                                tetromino->mino[i].coordenadas.columna);
        if(tetromino->mino[i].coordenadas.columna - 1 < 0 ||
           tablero->celda[coordenadas_mino.fila][coordenadas_mino.columna - 1].ocupado)
            return;
    }

    for(int i = 0; i < CANTIDAD_MINOS; i++)
        tetromino->mino[i].coordenadas.columna--;
}

bool girar(const t_tablero *tablero, t_tetromino *tetromino)
{
    if(tetromino->pieza == 'O')
        return false;

    unsigned nueva_fila, nueva_columna, fila_actual, columna_actual, i;

    const unsigned
    fila_pivote    = tetromino->mino[MINO_PIVOTE].coordenadas.fila,
    columna_pivote = tetromino->mino[MINO_PIVOTE].coordenadas.columna;

    t_coordenadas nuevas_coordenadas[CANTIDAD_MINOS - 1], auxiliar;
    t_coordenadas *puntero = nuevas_coordenadas;

    for(i = 0; i < CANTIDAD_MINOS; i++)
    {
        if(i != MINO_PIVOTE)
        {
            fila_actual    = tetromino->mino[i].coordenadas.fila;
            columna_actual = tetromino->mino[i].coordenadas.columna;
            nueva_fila     = fila_pivote    + (columna_actual - columna_pivote);
            nueva_columna  = columna_pivote - (fila_actual    - fila_pivote);
            coordenadas_inicializar(&auxiliar, nueva_fila, nueva_columna);
            if(!coordenadas_dentro_del_tablero(tablero, &auxiliar) ||
               !coordenadas_libres(tablero, &auxiliar))
                return false;
            memcpy(puntero, &auxiliar, sizeof(t_coordenadas));
            puntero++;
        }
    }

    puntero = nuevas_coordenadas;
    for(i = 0; i < CANTIDAD_MINOS; i++)
    {
        if(i != MINO_PIVOTE)
        {
            memcpy(&tetromino->mino[i].coordenadas, puntero, sizeof(t_coordenadas));
            puntero++;
        }
    }

    return true;
}

/* ========================================================================== */
/* HELPER INTERNO: REDIBUJO PARCIAL                                           */
/* ========================================================================== */

/**
 * @brief Redibuja solo fondo + tablero + pieza sin tocar el HUD.
 *
 * Se usa dentro de los temporizadores despues de cada movimiento lateral
 * o rotacion, donde el HUD no cambia y redibujar completo seria costoso.
 */
static void redibujar_movimiento(const t_layout *layout,
                                  const t_tablero *tablero,
                                  const t_tetromino *tetromino)
{
    dibujar_tablero(layout, tablero);
    dibujar_pieza(layout, tetromino);
    gbt_volcar_backbuffer();
}

/* ========================================================================== */
/* TEMPORIZADORES                                                             */
/* ========================================================================== */

int temporizador_movimientos_caida(const t_layout *layout,
                                    t_tablero *tablero,
                                    t_tetromino *tetromino,
                                    const t_tetromino *siguiente,
                                    double tiempo_caida,
                                    int *descensos_manuales,
                                    const int *puntaje)
{
    tGBT_Temporizador *caida = gbt_temporizador_crear(tiempo_caida);

    while(!gbt_temporizador_consumir(caida))
    {
        gbt_esperar(TIEMPO_ESPERA_MILISEGUNDOS);
        gbt_procesar_entrada();

        if(gbt_tecla_presionada(GBTK_DERECHA) || gbt_tecla_sostenida(GBTK_DERECHA))
        {
            mover_derecha(tablero, tetromino);
            redibujar_movimiento(layout, tablero, tetromino);
            tablero_mostrar(tablero, tetromino);
        }
        else if(gbt_tecla_presionada(GBTK_IZQUIERDA) || gbt_tecla_sostenida(GBTK_IZQUIERDA))
        {
            mover_izquierda(tablero, tetromino);
            redibujar_movimiento(layout, tablero, tetromino);
            tablero_mostrar(tablero, tetromino);
        }
        else if(gbt_tecla_presionada(GBTK_ARRIBA))
        {
            girar(tablero, tetromino);
            redibujar_movimiento(layout, tablero, tetromino);
            tablero_mostrar(tablero, tetromino);
        }
        else if(gbt_tecla_presionada(GBTK_ABAJO) || gbt_tecla_sostenida(GBTK_ABAJO))
        {
            if(tetromino_cayendo(tablero, tetromino))
            {
                tetromino_desplazar(tetromino);
                redibujar_movimiento(layout, tablero, tetromino);
                tablero_mostrar(tablero, tetromino);
                (*descensos_manuales)++;
            }
            //gbt_temporizador_destruir(caida);
            //return FORZAR_DESCENSO;
        }
        else if(gbt_tecla_presionada(GBTK_ESCAPE))
        {
            gbt_temporizador_destruir(caida);
            return SALIR;
        }
        else if(gbt_tecla_presionada(GBTK_p))
        {
            gbt_temporizador_pausar(caida);

            dibujar_cartel_pausa(layout);
            gbt_volcar_backbuffer();

            while(1)
            {
                gbt_procesar_entrada();

                if(gbt_tecla_presionada(GBTK_ENTER))
                {
                    gbt_borrar_backbuffer(FONDO);
                    dibujar_juego(layout, tablero, tetromino, siguiente, *puntaje);
                    gbt_temporizador_reanudar(caida);
                    break;
                }
            }
        }
    }

    gbt_temporizador_destruir(caida);
    return CAIDA;
}

int temporizador_movimientos_tolerancia(const t_layout *layout,
                                         t_tablero *tablero,
                                         t_tetromino *tetromino,
                                         const t_tetromino *siguiente,
                                         double tiempo_tolerancia,
                                         const int *puntaje)
{
    tGBT_Temporizador *tolerancia = gbt_temporizador_crear(tiempo_tolerancia);

    while(!gbt_temporizador_consumir(tolerancia))
    {
        gbt_esperar(TIEMPO_ESPERA_MILISEGUNDOS);
        gbt_procesar_entrada();

        if(gbt_tecla_presionada(GBTK_DERECHA) || gbt_tecla_sostenida(GBTK_DERECHA))
        {
            mover_derecha(tablero, tetromino);
            redibujar_movimiento(layout, tablero, tetromino);
            tablero_mostrar(tablero, tetromino);
            if(tetromino_cayendo(tablero, tetromino))
            {
                gbt_temporizador_destruir(tolerancia);
                return CAIDA;
            }
            else
            {
                gbt_temporizador_destruir(tolerancia);
                tolerancia = gbt_temporizador_crear(tiempo_tolerancia);
            }
        }
        else if(gbt_tecla_presionada(GBTK_IZQUIERDA) || gbt_tecla_sostenida(GBTK_IZQUIERDA))
        {
            mover_izquierda(tablero, tetromino);
            redibujar_movimiento(layout, tablero, tetromino);
            tablero_mostrar(tablero, tetromino);
            if(tetromino_cayendo(tablero, tetromino))
            {
                gbt_temporizador_destruir(tolerancia);
                return CAIDA;
            }
            else
            {
                gbt_temporizador_destruir(tolerancia);
                tolerancia = gbt_temporizador_crear(tiempo_tolerancia);
            }
        }
        else if(gbt_tecla_presionada(GBTK_ARRIBA))
        {
            girar(tablero, tetromino);
            redibujar_movimiento(layout, tablero, tetromino);
            tablero_mostrar(tablero, tetromino);
            if(tetromino_cayendo(tablero, tetromino))
            {
                gbt_temporizador_destruir(tolerancia);
                return CAIDA;
            }
            else
            {
                gbt_temporizador_destruir(tolerancia);
                tolerancia = gbt_temporizador_crear(tiempo_tolerancia);
            }
        }
        else if(gbt_tecla_presionada(GBTK_ESCAPE))
        {
            gbt_temporizador_destruir(tolerancia);
            return SALIR;
        }
        else if(gbt_tecla_presionada(GBTK_p))
        {
            gbt_temporizador_pausar(tolerancia);

            dibujar_cartel_pausa(layout);
            gbt_volcar_backbuffer();

            while(1)
            {
                gbt_procesar_entrada();

                if(gbt_tecla_presionada(GBTK_ENTER))
                {
                    gbt_borrar_backbuffer(FONDO);
                    dibujar_juego(layout, tablero, tetromino, siguiente, *puntaje);
                    gbt_temporizador_reanudar(tolerancia);
                    break;
                }
            }
        }
    }

    gbt_temporizador_destruir(tolerancia);
    return FIJADO;
}
