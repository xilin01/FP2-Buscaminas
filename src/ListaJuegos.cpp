#include "ListaJuegos.h"

void inicializar(tListaJuegos& lista_juegos) {
	lista_juegos.capacidad = MAX_JUEGOS;
	lista_juegos.cont = 0;
	lista_juegos.lista = new tPtrJuego[MAX_JUEGOS];
}

void destruye(tListaJuegos& lista_juegos) {
	for (int i = 0; i < lista_juegos.cont; i++) {
		delete lista_juegos.lista[i];
	}
	delete[] lista_juegos.lista;
	lista_juegos.cont = 0;
	lista_juegos.capacidad = 0;
}

int busqueda(const tListaJuegos& lista_juegos, const tJuego& juego) {
	int i = 0, pos = -1, nivel = calcula_nivel(juego);
	bool encontrado = false;

	while ((i < lista_juegos.cont) && (!encontrado)) {
		if (nivel <= calcula_nivel(*lista_juegos.lista[i])) {
			encontrado = true;
			pos = i;
		}
		else {
			i++;
		}
	}

return pos;
}

void redimensionamiento(tListaJuegos& lista_juegos) {
	tPtrJuego* aux = new tPtrJuego[++lista_juegos.capacidad];
	
	for (int i = 0; i < lista_juegos.cont; i++) {
		aux[i] = lista_juegos.lista[i];
	}
	delete[] lista_juegos.lista;
	lista_juegos.lista = aux;
}

int insertar(tListaJuegos& lista_juegos, const tJuego& juego) {
	if (lista_juegos.cont == lista_juegos.capacidad) {
		redimensionamiento(lista_juegos);
	}

	int pos = busqueda(lista_juegos, juego);

	if (pos == -1) {
		lista_juegos.lista[lista_juegos.cont] = new tJuego(juego);
		pos = lista_juegos.cont;
	}
	else {
		for (int i = lista_juegos.cont; i > pos; i--) {
			lista_juegos.lista[i] = lista_juegos.lista[i - 1];
		}
		lista_juegos.lista[pos] = new tJuego(juego);
	}
	lista_juegos.cont++;

return pos;
}

int numero_juegos(const tListaJuegos& lista_juegos) {

return lista_juegos.cont;
}

bool es_vacia(const tListaJuegos& lista_juegos) {

return (lista_juegos.cont == 0);
}

tJuego dame_juego(const tListaJuegos& lista_juegos, const int& pos) {

return *lista_juegos.lista[pos];
}

void eliminar(tListaJuegos& lista_juegos, const int& pos) {
	delete lista_juegos.lista[pos];
	for (int i = pos; i < lista_juegos.cont - 1; i++) {
		lista_juegos.lista[i] = lista_juegos.lista[i + 1];
	}
	lista_juegos.cont--;
}