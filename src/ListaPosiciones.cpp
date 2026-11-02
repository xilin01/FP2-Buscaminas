#include "ListaPosiciones.h"

void inicializar_listaPosiciones(tListaPosiciones& lista_pos) {
	lista_pos.capacidad = MAX_LISTA;
	lista_pos.cont = 0;
	lista_pos.lista = new tPosicion[MAX_LISTA];
}

void redimensionamiento(tListaPosiciones& lista_pos) { 
	tPosicion* aux = new tPosicion[++lista_pos.capacidad];

	for (int i = 0; i < lista_pos.cont; i++) {
		aux[i] = lista_pos.lista[i];
	}
	delete[] lista_pos.lista;
	lista_pos.lista = aux;
}

void insertar_final(tListaPosiciones& lista_pos, const int& x, const int& y) {
	if (lista_pos.cont == lista_pos.capacidad) {
		redimensionamiento(lista_pos);
	}
	lista_pos.lista[lista_pos.cont].posx = x;
	lista_pos.lista[lista_pos.cont++].posy = y;
}

int longitud(const tListaPosiciones& lista_pos) {

return lista_pos.cont;
}

int dame_posX(const tListaPosiciones& lista_pos, const int& i) {

return lista_pos.lista[i].posx;
}

int dame_posY(const tListaPosiciones& lista_pos, const int& i) {

return lista_pos.lista[i].posy;
}

void destruye(tListaPosiciones& lista_posiciones) {
	delete[] lista_posiciones.lista;
	lista_posiciones.cont = 0;
	lista_posiciones.capacidad = 0;
}