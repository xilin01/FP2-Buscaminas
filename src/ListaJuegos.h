#pragma once
#include "Juego.h"
#include "memoryleaks.h"

const int MAX_JUEGOS = 1;

typedef tJuego* tPtrJuego;

typedef struct {
	tPtrJuego* lista;
	int cont;
	int capacidad;
} tListaJuegos;

void inicializar(tListaJuegos& lista_juegos);
void destruye(tListaJuegos& lista_juegos);
int insertar(tListaJuegos& lista_juegos, const tJuego& juego);
int numero_juegos(const tListaJuegos& lista_juegos);
bool es_vacia(const tListaJuegos& lista_juegos);
tJuego dame_juego(const tListaJuegos& lista_juegos, const int& pos);
void eliminar(tListaJuegos& lista_juegos, const int& pos);