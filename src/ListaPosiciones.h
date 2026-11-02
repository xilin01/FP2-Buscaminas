#pragma once
#include "memoryleaks.h"

const int MAX_LISTA = 1;

typedef struct {
	int posx;
	int posy;
} tPosicion;

typedef struct {
	tPosicion* lista;
	int cont;
	int capacidad;
} tListaPosiciones;

void inicializar_listaPosiciones(tListaPosiciones& lista_pos);
void insertar_final(tListaPosiciones& lista_pos, const int& x, const int& y);
int longitud(const tListaPosiciones& lista_pos);
int dame_posX(const tListaPosiciones& lista_pos, const int& i);
int dame_posY(const tListaPosiciones& lista_pos, const int& i);
void destruye(tListaPosiciones& lista_posiciones);