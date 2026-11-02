#include "Celda.h"

void inicializar(tCelda& celda) {
	celda.estado = VACIA;
	celda.visible = false;
	celda.marcada = false;
	celda.numero = 0;
}

tEstado dame_estado(const tCelda& celda) {
	return celda.estado;
}

int dame_numero(const tCelda& celda) {
	return celda.numero;
}

bool es_visible(const tCelda& celda) {
	return celda.visible;
}

bool es_mina(const tCelda& celda) {
	return celda.estado == MINA;
}

bool esta_vacia(const tCelda& celda) {
	return celda.estado == VACIA;
}

bool contiene_numero(const tCelda& celda) {
	return celda.estado == NUMERO;
}

bool esta_marcada(const tCelda& celda) {
	return celda.marcada;
}

void descubrir_celda(tCelda& celda) {
	celda.visible = true;
}

void ocultar_celda(tCelda& celda) {
	celda.visible = false;
}

void poner_mina(tCelda& celda) {
	celda.estado = MINA;
}

void marcar_celda(tCelda& celda) {
	celda.marcada = true;
}

void desmarcar_celda(tCelda& celda) {
	celda.marcada = false;
}

void poner_numero(tCelda& celda, const int& num) {
	celda.numero = num;
	celda.estado = NUMERO;
}