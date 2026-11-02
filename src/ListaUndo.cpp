#include "ListaUndo.h"

void inicializar(tListaUndo& lista_undo) {
	lista_undo.cont = 0;
}

void insertar_final(tListaUndo& lista_undo, const tListaPosiciones& lista_pos) { // funciona aunque salga la advertencia C6386
	if (lista_undo.cont == MAX_UNDO) {
		destruye(*lista_undo.lista[0]);
		delete lista_undo.lista[0];
		for (int i = 0; i < MAX_UNDO - 1; i++) { // bucle por si se aumenta MAX_UNDO
			lista_undo.lista[i] = lista_undo.lista[i + 1];
		}
		lista_undo.cont--;
	}
	lista_undo.lista[lista_undo.cont++] = new tListaPosiciones(lista_pos);
}

tListaPosiciones ultimos_movimientos(tListaUndo& lista_undo) {
	tListaPosiciones listaPosiciones;

	listaPosiciones.cont = 0;
	if (0 < lista_undo.cont) {
		listaPosiciones = *lista_undo.lista[lista_undo.cont - 1];
	}
	
return listaPosiciones;
}

void eliminar_ultimo(tListaUndo& lista_undo) {
	if (0 < lista_undo.cont) {
		destruye(*lista_undo.lista[--lista_undo.cont]);
		delete lista_undo.lista[lista_undo.cont];
	}
}

void destruye(tListaUndo& lista_undo) {
	int contador = lista_undo.cont;

	for (int i = 0; i < contador; i++) {
		eliminar_ultimo(lista_undo);
	}
}