#include <stdio.h>
#include "quadrado.h"
#include "algoritmo.h"

int ler_entrada(Quadrado *quadrados[MAXNUMBER]) {
	int N, i, total;
	int a, b, c, d;
	scanf("%d", &N);
	total = N*N;
	for(i=0;i<total;i++) {
		scanf("%d %d %d %d", &a, &b, &c, &d);
		quadrados[i] = novo_quadrado(a, b, c, d);
	}
	return N;
}

void imprimir_saida(Quadrado *quadrados[MAXNUMBER], int N) {
	int i;
	for(i=0;i<N*N;i++) {
		printf("%d %d %d %d\n", quadrados[i]->cima, quadrados[i]->direita, quadrados[i]->baixo, quadrados[i]->esquerda);
	}
}	

void imprimir_resultado(QuadradoPosicionado *tabuleiro[MAXNUMBER][MAXNUMBER], const int N) {
	int i, j;
	for(i=0;i<N;i++) {
		for(j=0;j<N;j++) {
			printf("-%d- ", cor_de_cima(tabuleiro[i][j]));
		}
		printf("\n");
		for(j=0;j<N;j++) {
			printf("%d-%d ", cor_da_esquerda(tabuleiro[i][j]), cor_da_direita(tabuleiro[i][j]));
		}
		printf("\n");
		for(j=0;j<N;j++) {
			printf("-%d- ", cor_de_baixo(tabuleiro[i][j]));
		}
		printf("\n\n");
	}
}

int main() {
	Quadrado *quadrados[MAXNUMBER];
	QuadradoPosicionado *tabuleiro[MAXNUMBER][MAXNUMBER];
	int N;
	N = ler_entrada(quadrados);
	printf("---------------\n");
	imprimir_saida(quadrados, N);
	printf("------------resultado\n");
	if(resolver(0, 0, quadrados, tabuleiro, N)) {
		printf("resolvido!\n");
		imprimir_resultado(tabuleiro, N);
	}
	else
		printf("não foi possivel resolver o problema\n");
	return 0;
}
