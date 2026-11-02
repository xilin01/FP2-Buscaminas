#pragma once
#include "Celda.h"

const int MAX_FILS = 30;
const int MAX_COLS = 30;

typedef struct {
	int nFils, nCols;
	tCelda datos[MAX_FILS][MAX_COLS];
} tTablero;

void inicializar(tTablero& tablero);
void inicializar(tTablero& tablero, const int& nfils, const int& ncols);
int num_filas(const tTablero& tablero);
int num_columnas(const tTablero& tablero);
tCelda dame_celda(const tTablero& tablero, const int& fila, const int& columna);
bool es_valida(const tTablero& tablero, const int& fila, const int& columna);
void poner_celda(tTablero& tablero, const int& fila, const int& columna, const tCelda& celda);