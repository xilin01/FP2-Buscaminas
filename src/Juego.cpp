#include "Juego.h"

void inicializar(tJuego& juego) {
	juego.num_jugadas = 0;
	juego.num_descubiertas = 0;
	juego.num_minas = 0;
	juego.mina_explotada = false;
	inicializar(juego.tablero);
}

void inicializar(tJuego& juego, const int& nfils, const int& ncols) {
	inicializar(juego);
	inicializar(juego.tablero, nfils, ncols);
}

int dame_num_jugadas(const tJuego& juego) {
	return juego.num_jugadas;
}

int dame_num_filas(const tJuego& juego) {
	return num_filas(juego.tablero);
}

int dame_num_columnas(const tJuego& juego) {
	return num_columnas(juego.tablero);
}

int dame_num_minas(const tJuego& juego) {
	return juego.num_minas;
}

bool contiene_mina(const tJuego& juego, const int& fila, const int& columna) {
	return es_mina(dame_celda(juego.tablero, fila, columna));
}

bool es_visible(const tJuego& juego, const int& fila, const int& columna) {
	return es_visible(dame_celda(juego.tablero, fila, columna));
}

bool esta_marcada(const tJuego& juego, const int& fila, const int& columna) {
	return esta_marcada(dame_celda(juego.tablero, fila, columna));
}

bool esta_vacia(const tJuego& juego, const int& fila, const int& columna) {
	return esta_vacia(dame_celda(juego.tablero, fila, columna));
}

bool contiene_numero(const tJuego& juego, const int& fila, const int& columna) {
	return contiene_numero(dame_celda(juego.tablero, fila, columna));
}

int dame_numero(const tJuego& juego, const int& fila, const int& columna) {
	return dame_numero(dame_celda(juego.tablero, fila, columna));
}

bool esta_completo(const tJuego& juego) {
	return (juego.num_descubiertas + juego.num_minas == (num_filas(juego.tablero) * num_columnas(juego.tablero)));
}

bool mina_explotada(const tJuego& juego) {
	return juego.mina_explotada;
}

bool esta_terminado(const tJuego& juego) {
	return (esta_completo(juego) || mina_explotada(juego));
}

void poner_mina(tJuego& juego, const int& fila, const int& columna) {
	if (es_valida(juego.tablero, fila, columna) && !contiene_mina(juego, fila, columna)) {
		tCelda celdaAyuda = dame_celda(juego.tablero, fila, columna);

		poner_mina(celdaAyuda);
		poner_celda(juego.tablero, fila, columna, celdaAyuda);
		juego.num_minas += 1;
		for (int i = fila - 1; i <= fila + 1; i++) {
			for (int j = columna - 1; j <= columna + 1; j++) {
				if (es_valida(juego.tablero, i, j) && !contiene_mina(juego, i, j) && (i != fila || j != columna)) {
					celdaAyuda = dame_celda(juego.tablero, i, j);
					poner_numero(celdaAyuda, dame_numero(celdaAyuda) + 1); // num = 0 si esta vacia
					poner_celda(juego.tablero, i, j, celdaAyuda);
				}
			}
		}
	}
}

void marcar_desmarcar(tJuego& juego, const int& fila, const int& columna) {
	if (es_valida(juego.tablero, fila, columna)) {
		tCelda celdaAyuda = dame_celda(juego.tablero, fila, columna);
		if (esta_marcada(celdaAyuda)) {
			desmarcar_celda(celdaAyuda);
		}
		else if(!es_visible(celdaAyuda)) {
			marcar_celda(celdaAyuda);
		}
		poner_celda(juego.tablero, fila, columna, celdaAyuda);
	}
}

void ocultar(tJuego& juego, const int& fila, const int& columna) {
	if (es_valida(juego.tablero, fila, columna) && es_visible(juego, fila, columna)) {
		tCelda celdaAyuda = dame_celda(juego.tablero, fila, columna);
		ocultar_celda(celdaAyuda);
		poner_celda(juego.tablero, fila, columna, celdaAyuda);
		juego.num_descubiertas -= 1;
	}
}

void juega(tJuego& juego, const int& fila, const int& columna, tListaPosiciones& lista_pos) {
	if (es_valida(juego.tablero, fila, columna) && !es_visible(juego, fila, columna) && !esta_marcada(juego, fila, columna)) {
		tCelda celdaAyuda = dame_celda(juego.tablero, fila, columna);

		descubrir_celda(celdaAyuda);
		poner_celda(juego.tablero, fila, columna, celdaAyuda);
		if (longitud(lista_pos) == 0) {
			juego.num_jugadas += 1;
		}
		juego.num_descubiertas += 1;
		if (es_mina(celdaAyuda)) {
			juego.mina_explotada = true;
		}
		else {
			insertar_final(lista_pos, fila, columna); // insertamos si no es una mina
			if (esta_vacia(celdaAyuda)) {
				for (int i = fila - 1; i <= fila + 1; i++) {
					for (int j = columna - 1; j <= columna + 1; j++) {
						if (es_valida(juego.tablero, i, j) && !es_visible(juego, i, j) && !esta_marcada(juego, i, j) && (i != fila || j != columna)) {
							juega(juego, i, j, lista_pos);
						}
					}
				}
			}
		}
	}
}

int calcula_nivel(const tJuego& juego) { // redondeo incluido

return (double(dame_num_filas(juego) * dame_num_columnas(juego)) / dame_num_minas(juego) + 0.5); // double devuelto como int
}

tJuego crear_juego(const int& num_fils, const int& num_cols, const int& num_minas) {
	tJuego juego;
	int contador = 0, fila, columna;

	inicializar(juego, num_fils, num_cols);
	srand(time(nullptr));
	while (contador < num_minas) {
		fila = rand() % num_fils;
		columna = rand() % num_cols;
		if (!contiene_mina(juego, fila, columna)) {
			poner_mina(juego, fila, columna); 
			contador++;
		}
	}
	
return juego;
}