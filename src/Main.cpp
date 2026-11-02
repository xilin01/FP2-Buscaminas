// Xiang Lin y Mario Rosell
// Grupo 13

#include "InputOutput.h"
#include "ListaUndo.h"
#include <iostream>
using namespace std;

void juega(tJuego& juego, int fila, int columna, tListaUndo& lista_undo);
tJuego juego_aleatorio();

int main() {
#ifdef _MSC_VER
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

	tListaJuegos listaJuegos;

	inicializar(listaJuegos);
	mostrar_cabecera();
	if (cargar_juegos(listaJuegos)) {
		int pos; // insertamos el nuevo juego al inicio para darle utilidad al int que devuelve la funcion insertar de lista de juegos
		tJuego juego;

		if (es_vacia(listaJuegos)) {
			cout << "No hay juegos en el fichero, creando juego nuevo..." << endl;
			juego = juego_aleatorio();
			pos = insertar(listaJuegos, juego);
		}
		else {
			int opcion;

			do {
				cout << "Juego nuevo (opcion 1) o juego existente (opcion 2): ";
				cin >> opcion;
			} while (opcion < 1 || 2 < opcion);
			if (opcion == 1) {
				juego = juego_aleatorio();
				pos = insertar(listaJuegos, juego);
			}
			else {
				mostrar_juegos(listaJuegos);
				do {
					cout << "Selecciona la partida: ";
					cin >> pos;
				} while (pos < 0 || numero_juegos(listaJuegos) <= pos);
				juego = dame_juego(listaJuegos, pos);
			}
		}

		int fila, columna;
		tListaUndo listaUndo;

		inicializar(listaUndo);
		mostrar_juego_consola(juego);
		pedir_pos(fila, columna);
		while ((fila != -1 || columna != -1) && !esta_terminado(juego)) {
			juega(juego, fila, columna, listaUndo);
			mostrar_juego_consola(juego);
			if (!esta_terminado(juego)) {
				pedir_pos(fila, columna);
			}
		}
		destruye(listaUndo);
		cout << endl;
		mostrar_resultado(juego);
		cout << endl << endl;
		if (esta_terminado(juego)) {
			eliminar(listaJuegos, pos);
		}
		if (guardar_juegos(listaJuegos)) {
			cout << "La lista de juegos se ha guardado correctamente." << endl;
		}
		else {
			cout << "ERROR: no ha sido posible guardar la lista de juegos." << endl;
		}
		destruye(listaJuegos);
	}
	else {
		cout << endl;
		cout << "ERROR: no ha sido posible abrir el fichero de juegos." << endl;
	}

return 0;
}

void juega(tJuego& juego, int fila, int columna, tListaUndo& lista_undo) {
	if (fila == -2 && columna == -2) {
		cout << "MARCAR/DESMARCAR mina:" << endl;
		pedir_pos(fila, columna);
		marcar_desmarcar(juego, fila, columna);
	}
	else if (fila == -3 && columna == -3) {
		int longi = longitud(ultimos_movimientos(lista_undo));

		cout << "UNDO: realizar undo." << endl;
		for (int i = 0; i < longi; i++) {
			ocultar(juego, dame_posX(ultimos_movimientos(lista_undo), i), dame_posY(ultimos_movimientos(lista_undo), i));
		}
		eliminar_ultimo(lista_undo);
	}
	else if (0 <= fila && fila < dame_num_filas(juego) && 0 <= columna && columna < dame_num_columnas(juego)) {
		tListaPosiciones listaPosiciones;

		inicializar_listaPosiciones(listaPosiciones);
		juega(juego, fila, columna, listaPosiciones);
		if (longitud(listaPosiciones) != 0) {
			insertar_final(lista_undo, listaPosiciones);
		}
		else {
			destruye(listaPosiciones);
		}
	}
	else {
		cout << "ERROR: posicion invalida." << endl;
	}
}

tJuego juego_aleatorio() {
	int filas, columnas, nMinas, minas;

	do {
		cout << "Numero de filas (>=2) y columnas (>=2) del tablero: ";
		cin >> filas >> columnas;
	} while (filas < 2 || columnas < 2);
	nMinas = filas * columnas / 3; // condicion que imponemos
	do {
		cout << "Numero de minas (<" << nMinas << "): ";
		cin >> minas;
	} while (nMinas <= minas);

return crear_juego(filas, columnas, minas);
}