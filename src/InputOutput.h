#pragma once
#include "Juego.h"
#include "colors.h"
#include "ListaJuegos.h"
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

const char CHAR_MINA = '*'; // mina
const int N_HUECOS = 2; // huecos a dejar en el formato de las celdas

void mostrar_cabecera();
void pedir_pos(int& fila, int& columna);
void mostrar_resultado(const tJuego& juego);
void mostrar_juego_consola(const tJuego& juego);
bool carga_juego(tJuego& juego); // en desuso
std::istream& operator>>(std::istream& in, tJuego& juego);
bool cargar_juegos(tListaJuegos& lista_juegos);
void mostrar_juegos(const tListaJuegos& lista_juegos);
bool guardar_juegos(const tListaJuegos& lista_juegos);