#include "InputOutput.h"
using namespace std;

void colorNumero(int numero) {
    switch (numero)
    {
    case 1: cout << CYAN; break;
    case 2: cout << GREEN; break;
    case 3: cout << RED; break;
    case 4: cout << YELLOW; break;
    case 5: cout << DGREEN; break;
    case 6: cout << ROSE; break;
    case 7: cout << ORANGE; break;
    case 8: cout << WHITE; break;
    default:
        break;
    }
}

void mostrarCoutSeparadorMat(int huecoCelda, int nCols) {
    cout << "\t -+";
    for (int col = 0; col < nCols; ++col) {
        cout << setw(huecoCelda + 1) << setfill('-') << '+' << setfill(' ');
    }
    cout << endl;
}

void mostrarCeldaConsola(const tJuego& juego, int fila, int columna, int huecos) {
    if (!es_visible(juego, fila, columna) && !esta_marcada(juego, fila, columna)) {
        cout << BG_GRAY << GRAY << setw(huecos) << setfill(' ') << ' ' << RESET;
    }
    else {
        cout << BG_BLACK << BLACK;
        if (!esta_marcada(juego, fila, columna)) {
            if (contiene_mina(juego, fila, columna)) {
                cout << RED << setw(huecos) << setfill(' ') << CHAR_MINA << RESET;
            }
            else {
                if (esta_vacia(juego, fila, columna)) {
                    cout << setw(huecos) << setfill(' ') << ' ' << RESET;
                }
                else {
                    if (contiene_numero(juego, fila, columna)) {
                        int numero = dame_numero(juego, fila, columna);
                        colorNumero(numero);
                        cout << setw(huecos) << setfill(' ') << numero << RESET;
                    }
                    else {
                        cout << BG_RED << RED << setw(huecos) << setfill(' ') << ' ' << RESET;
                    }
                }
            }
        }
        else {
            cout << BG_ORANGE << ORANGE << setw(huecos) << setfill(' ') << ' ' << RESET;
        }
    }
}

void mostrar_tablero(const tJuego& juego) {
    // mostrar cabecera
    int ncols = dame_num_columnas(juego);
    int nfilas = dame_num_filas(juego);
    cout << "\t  |";
    for (int col = 0; col < ncols; col++) {
        cout << LBLUE << setw(N_HUECOS) << col << RESET << '|';
    }
    cout << endl;

    // mostrar separador
    mostrarCoutSeparadorMat(N_HUECOS, ncols);

    // mostrar tablero
    for (int f = 0; f < nfilas; f++) {
        // mostrar numero de fila
        cout << "\t" << LBLUE << setw(2) << f << RESET << '|';
        // mostrar la fila
        for (int c = 0; c < ncols; c++) {
            mostrarCeldaConsola(juego, f, c, N_HUECOS);
            cout << '|';
        }
        cout << endl;

        mostrarCoutSeparadorMat(N_HUECOS, ncols);
    }
    cout << endl;
}

void mostrar_cabecera() {
	cout << "Buscaminas" << endl;
	cout << "----------" << endl;
}

void pedir_pos(int& fila, int& columna) { 
    cout << "Fila y columna: ";
	cin >> fila >> columna;
}

void mostrar_resultado(const tJuego& juego) {
	if (mina_explotada(juego)) {
		cout << "Mina explotada. Fin del juego." << endl;
	}
	else if (esta_completo(juego)) {
		cout << "Enhorabuena, has ganado." << endl;
	}
	else {
		cout << "Vuelve a intentarlo luego, rendirse no es la solucion." << endl;
	}
}

void mostrar_juego_consola(const tJuego& juego) {
    cout << endl;
    cout << setw(18) << right << "Jugadas: " << dame_num_jugadas(juego) << endl;
    cout << setw(16) << right << "Minas: " << dame_num_minas(juego) << endl;
	mostrar_tablero(juego);
}

bool carga_juego(tJuego& juego) { // en desuso
	bool todoBien = true;
	string nombre;
	cout << "Dame el nombre del archivo: ";
	cin >> nombre;
	ifstream lectura;
	lectura.open(nombre);
	if (!lectura.is_open()) {
        cout << endl;
		cout << "Error al abrir el archivo de texto." << endl;
		todoBien = false;
	}
	else {
		lectura >> juego;
        lectura.close();
	}
	return todoBien;
}

istream& operator>>(istream& in, tJuego& juego) {
	int filas, columnas, nMinas, posx, posy;
	in >> filas >> columnas >> nMinas;
	inicializar(juego, filas, columnas);
	for (int i = 0; i < nMinas; i++) {
		in >> posx >> posy;
		poner_mina(juego, posx, posy);
	}
	return in;
}

bool cargar_juegos(tListaJuegos& lista_juegos) {
    ifstream in;
    string archivo;
    bool cargado = false;

    cout << "Nombre del fichero de juegos: ";
    cin >> archivo;
    in.open(archivo);
    if (in.is_open()) {
        cargado = true;
        
        int nJuegos;
        tJuego juego;

        in >> nJuegos;
        for (int i = 0; i < nJuegos; i++) {
            in >> juego;
            insertar(lista_juegos, juego); // no usamos el int que devuelve
        }
        in.close();
    }

return cargado;
}

void mostrar_juegos(const tListaJuegos& lista_juegos) {
    tJuego juego;

    cout << "Mostrando lista de juegos por orden de dificultad..." << endl;
    for (int i = 0; i < numero_juegos(lista_juegos); i++) {
        cout << "Juego " << i << ":" << endl;
        juego = dame_juego(lista_juegos, i);
        cout << setw(14) << "Dimension: " << dame_num_filas(juego) << " x " << dame_num_columnas(juego) << endl;
        cout << setw(10) << "Minas: " << dame_num_minas(juego) << endl;
    }
}

bool guardar_juegos(const tListaJuegos& lista_juegos) {
    ofstream out;
    string archivo;
    bool guardado = false;

    cout << "Nombre del fichero para guardar los juegos: ";
    cin >> archivo;
    cout << endl;
    out.open(archivo);
    if (out.is_open()) {
        guardado = true;

        tJuego juego;
        int minas, i, j;

        out << numero_juegos(lista_juegos) << endl;
        for (int n = 0; n < numero_juegos(lista_juegos); n++) {
            juego = dame_juego(lista_juegos, n);
            out << dame_num_filas(juego) << " " << dame_num_columnas(juego) << endl;
            out << dame_num_minas(juego) << endl;
            minas = 0;
            i = 0;
            while ((i < dame_num_filas(juego)) && (minas < dame_num_minas(juego))) { 
                j = 0;
                while ((j < dame_num_columnas(juego)) && (minas < dame_num_minas(juego))) {
                    if (contiene_mina(juego, i, j)) {
                        out << i << " " << j << endl;
                        minas++;
                    }
                    j++; // sumamos aunque hayamos encontrado todas las minas
                }
                i++; // sumamos aunque hayamos encontrado todas las minas
            }
        }
        out.close();
    }

return guardado;
}