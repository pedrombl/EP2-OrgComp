#include "quadrado.h"
#include <stdlib.h>
#include <stdio.h>

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
	if(quadrado == NULL)
		printf("ERROR quadrado null\n");
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
	printf("rotacionando\n");
	if(++(posicionado->rotacao) == 4) {
		posicionado->rotacao = 0;
		return FALSE;
	}
	return TRUE;
}


PilhaQuadrado *pegar_ultimo(PilhaQuadrado *pilha) {
	PilhaQuadrado *atual = pilha;
	printf("incio pegar_ultimo\n");
	while(atual->prox != NULL)
		atual = atual->prox;
	printf("fim pegar_ultimo\n");
	return atual;
}

PilhaQuadrado *novo_quadrado_na_pilha(PilhaQuadrado *pilha, Quadrado *quadrado) {
	PilhaQuadrado *ultimo, *novo = malloc(sizeof(PilhaQuadrado));
	novo->quadrado = quadrado;
	novo->prox = NULL;
	if(pilha == NULL)
		return novo;

	ultimo = pegar_ultimo(pilha);
	ultimo->prox = novo;
	return pilha;	
}

PilhaQuadrado *trocar_quadrado(PilhaQuadrado *pilha) {
	PilhaQuadrado *novo, *ultimo;
	printf("trocar_quadrado iniciado\n");
	novo = pilha->prox;
	if(novo == NULL)
		return pilha;
	
	ultimo = pegar_ultimo(novo);
	ultimo->prox = pilha;
	pilha->prox = NULL;
	printf("fim do trocar_quadrado\n");
	return novo;
}


PilhaQuadrado *copiar_pilha_unidade(PilhaQuadrado *pilhaUnidade) {
	PilhaQuadrado *novo = malloc(sizeof(PilhaQuadrado));
	novo->quadrado = pilhaUnidade->quadrado;
	novo->prox = NULL;
	return novo;
}

PilhaQuadrado *copiar_pilha(PilhaQuadrado *pilha) {
	PilhaQuadrado *nova_pilha=NULL, *ultimo, *atual;
	if(pilha == NULL)
		return NULL;
	
	nova_pilha = copiar_pilha_unidade(pilha);
	ultimo = nova_pilha;
	pilha = pilha->prox;
	while(pilha != NULL) {
		atual = copiar_pilha_unidade(pilha);
		ultimo->prox = atual;
		ultimo = atual;
		pilha = pilha->prox;
	}
	return nova_pilha;
}

void apagar_pilha(PilhaQuadrado *pilha) {
	PilhaQuadrado *proximo;
	while(pilha != NULL) {
		proximo = pilha->prox;
		free(pilha);
		pilha = proximo;
	}
}

int contar_pilha(PilhaQuadrado *pilha) {
	int i;
	for(i=0;pilha!=NULL;i++)
		pilha = pilha->prox;
	return i;
}
