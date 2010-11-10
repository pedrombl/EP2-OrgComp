#include "quadrado.h"
#include "algoritmo.h"
#include <stdio.h>
#include <stdlib.h>


int posicao_valida(const int i, const int j,
									 QuadradoPosicionado *tabuleiro[][MAXNUMBER],
									 QuadradoPosicionado *posicionado,
									 const int N)
{
	printf("posicao valida?\n");
	if(j != 0 && tabuleiro[i][j-1] == NULL)
		printf("ERROR posição do tabuleiro vazia\n");
	if(posicionado == NULL)
		printf("ERROR posicionado null\n");
	if(posicionado->quadrado == NULL)
		printf("ERROR quadrado no posicionado null\n");


	return !((i == 0 && cor_de_cima(posicionado) != 0) ||
				   (j == 0 && cor_da_esquerda(posicionado) != 0) || 
				   (i == N-1 && cor_de_baixo(posicionado) != 0) ||
				   (j == N-1 && cor_da_direita(posicionado) != 0) ||
				   (i != 0 && cor_de_baixo(tabuleiro[i-1][j]) != cor_de_cima(posicionado)) ||
				   (j != 0 && cor_da_direita(tabuleiro[i][j-1]) != cor_da_esquerda(posicionado)));
}

void proxima_posicao(int i, int j, const int N, int *novo_i, int *novo_j) {
	j++;
	if(j < N) {
		(*novo_i) = i;
		(*novo_j) = j;
	}
	else {
		(*novo_i) = i+1;
		(*novo_j) = 0;
	}
	printf("novos i e j: %d %d\n", *novo_i, *novo_j);
}


int resolver(const int i, const int j, 
						PilhaQuadrado *pilha_antiga,
						QuadradoPosicionado *tabuleiro[][MAXNUMBER],
						const int N)
{

	QuadradoPosicionado *posicionado;
	int i_novo, j_novo;
	int quadrados_sobrando = N*N - (i*N + j);
	int x=0;
	PilhaQuadrado *pilha;
	
	printf("posicao atual: %d %d\n", i, j);
	printf("quadrados sobrando: %d - %d\n", quadrados_sobrando, contar_pilha(pilha_antiga));
	if(i == N)
		return TRUE;

	pilha = copiar_pilha(pilha_antiga);
	printf("copia: %d\n", contar_pilha(pilha));
	proxima_posicao(i, j, N, &i_novo, &j_novo);	
	do {
		printf("entrou no do 1\n");
		posicionado = nova_posicao(pilha->quadrado, GRAU_0);
		printf("novo quadrado posicionado\n");
		tabuleiro[i][j] = posicionado;
		do {
			printf("entrou no do 2\n");
			if(posicao_valida(i, j, tabuleiro, posicionado, N) &&
				 resolver(i_novo, j_novo, pilha->prox, tabuleiro, N)) {
				apagar_pilha(pilha);
				return TRUE;
			}
			printf("continuou\n");
		} while(rotacionar(posicionado));
		printf("não com essa peça\n");
		free(posicionado);
		printf("peça liberada do tabuleiro\n");
		pilha = trocar_quadrado(pilha);
		printf("trocando_quadrados");
		x++;
	} while(x<quadrados_sobrando);

	printf("retornando FALSE\n");
	return FALSE;

}



