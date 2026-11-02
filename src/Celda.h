#pragma once

typedef enum { NUMERO, VACIA, MINA } tEstado;

typedef struct {
	bool visible;
	tEstado estado;
	int numero;
	bool marcada;
} tCelda;

void inicializar(tCelda& celda);
tEstado dame_estado(const tCelda& celda);
int dame_numero(const tCelda& celda);
bool es_visible(const tCelda& celda);
bool es_mina(const tCelda& celda);
bool esta_vacia(const tCelda& celda);
bool contiene_numero(const tCelda& celda);
bool esta_marcada(const tCelda& celda);
void descubrir_celda(tCelda& celda);
void ocultar_celda(tCelda& celda);
void poner_mina(tCelda& celda);
void marcar_celda(tCelda& celda);
void desmarcar_celda(tCelda& celda);
void poner_numero(tCelda& celda, const int& num);