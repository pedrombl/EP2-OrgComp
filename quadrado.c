#include "quadrado.h"
#include <stdlib.h>

Quadrado *novo_quadrado(int cima, int direita, int baixo, int esquerda) {
	Quadrado *quadrado = malloc(sizeof(Quadrado));
	quadrado->cima = cima;
	quadrado->direita = direita;
	quadrado->baixo = baixo;
	quadrado->esquerda = esquerda;
	return quadrado;
}

QuadradoPosicionado *nova_posicao(Quadrado *quadrado, int rotacao) {
	QuadradoPosicionado *posicionado = malloc(sizeof(QuadradoPosicionado));
	posicionado->quadrado = quadrado;
	posicionado->rotacao = rotacao;
	return posicionado;
}

int cor_de_cima(QuadradoPosicionado *posicionado) {
	int cor = -1;
	switch(posicionado->rotacao) {
		case GRAU_0:
			cor = posicionado->quadrado->cima;
			break;
		case GRAU_90:
			cor = posicionado->quadrado->esquerda;
			break;
		case GRAU_180:
			cor = posicionado->quadrado->baixo;
			break;
		case GRAU_270:
			cor = posicionado->quadrado->direita;
			break;
	}
	return cor;
}

int cor_da_direita(QuadradoPosicionado *posicionado) {
	int cor = -1;
	switch(posicionado->rotacao) {
		case GRAU_0:
			cor = posicionado->quadrado->direita;
			break;
		case GRAU_90:
			cor = posicionado->quadrado->cima;
			break;
		case GRAU_180:
			cor = posicionado->quadrado->esquerda;
			break;
		case GRAU_270:
			cor = posicionado->quadrado->baixo;
			break;
	}
	return cor;
}

int cor_de_baixo(QuadradoPosicionado *posicionado) {
	int cor = -1;
	switch(posicionado->rotacao) {
		case GRAU_0:
			cor = posicionado->quadrado->baixo;
			break;
		case GRAU_90:
			cor = posicionado->quadrado->direita;
			break;
		case GRAU_180:
			cor = posicionado->quadrado->cima;
			break;
		case GRAU_270:
			cor = posicionado->quadrado->esquerda;
			break;
	}
	return cor;
}

int cor_da_esquerda(QuadradoPosicionado *posicionado) {
	int cor=-1;
	switch(posicionado->rotacao) {
		case GRAU_0:
			cor = posicionado->quadrado->esquerda;
			break;
		case GRAU_90:
			cor = posicionado->quadrado->baixo;
			break;
		case GRAU_180:
			cor = posicionado->quadrado->direita;
			break;
		case GRAU_270:
			cor = posicionado->quadrado->cima;
			break;
	}
	return cor;
}

int rotacionar(QuadradoPosicionado *posicionado) {
	if(++(posicionado->rotacao) == 4) {
		posicionado->rotacao = 0;
		return FALSE;
	}
	return TRUE;
}
