#pragma once
#include "Tablero.h"
#include "ListaPosiciones.h"
#include <cstdlib>
#include <ctime>

typedef struct {
	tTablero tablero;
	int num_jugadas;
	bool mina_explotada;
	int num_minas;
	int num_descubiertas;
} tJuego;

void inicializar(tJuego& juego);
void inicializar(tJuego& juego, const int& nfils, const int& ncols);
int dame_num_jugadas(const tJuego& juego);
int dame_num_filas(const tJuego& juego);
int dame_num_columnas(const tJuego& juego);
int dame_num_minas(const tJuego& juego);
bool contiene_mina(const tJuego& juego, const int& fila, const int& columna);
bool es_visible(const tJuego& juego, const int& fila, const int& columna);
bool esta_marcada(const tJuego& juego, const int& fila, const int& columna);
bool esta_vacia(const tJuego& juego, const int& fila, const int& columna);
bool contiene_numero(const tJuego& juego, const int& fila, const int& columna);
int dame_numero(const tJuego& juego, const int& fila, const int& columna);
bool esta_completo(const tJuego& juego);
bool mina_explotada(const tJuego& juego);
bool esta_terminado(const tJuego& juego);
void poner_mina(tJuego& juego, const int& fila, const int& columna);
void marcar_desmarcar(tJuego& juego, const int& fila, const int& columna);
void ocultar(tJuego& juego, const int& fila, const int& columna);
void juega(tJuego& juego, const int& fila, const int& columna, tListaPosiciones &lista_pos);
int calcula_nivel(const tJuego& juego);
tJuego crear_juego(const int& num_fils, const int& num_cols, const int& num_minas);