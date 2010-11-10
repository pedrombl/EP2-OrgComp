#include <stdio.h>
#include "quadrado.h"
#include "algoritmo.h"

PilhaQuadrado *ler_entrada(int *N) {
	PilhaQuadrado *pilha = NULL;
	int i, total;
	int a, b, c, d;
	scanf("%d", N);
	total = (*N)*(*N);
	for(i=0;i<total;i++) {
		scanf("%d %d %d %d", &a, &b, &c, &d);
		pilha = novo_quadrado_na_pilha(pilha, novo_quadrado(a, b, c, d));
	}
	return pilha;
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
	PilhaQuadrado *pilha;
	QuadradoPosicionado *tabuleiro[MAXNUMBER][MAXNUMBER];
	int N;

	pilha = ler_entrada(&N);
	printf("total de quadrados: %d\n", contar_pilha(pilha));
	printf("------------resultado\n");
	if(resolver(0, 0, pilha, tabuleiro, N)) {
		printf("resolvido!\n");
		imprimir_resultado(tabuleiro, N);
	}
	else
		printf("não foi possivel resolver o problema\n");
	return 0;
}
