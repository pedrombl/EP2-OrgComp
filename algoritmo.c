#include "quadrado.h"
#include "algoritmo.h"
#include <stdio.h>


int posicao_valida(const int i, const int j,
									 QuadradoPosicionado *tabuleiro[][MAXNUMBER],
									 QuadradoPosicionado *posicionado,
									 const int N)
{
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
		printf("mudou\n");
		(*novo_i) = i+1;
		(*novo_j) = 0;
	}
	printf("novos i e j: %d %d\n", *novo_i, *novo_j);
}


int resolver(const int i, const int j, 
						Quadrado *quadrados[],
						QuadradoPosicionado *tabuleiro[][MAXNUMBER],
						const int N)
{

	QuadradoPosicionado *posicionado;
	int i_novo, j_novo;
	
	printf("posicao atual: %d %d\n", i, j);
	if(i == N)
		return TRUE;
	
	posicionado = nova_posicao(quadrados[(i*N)+j], GRAU_0);
	tabuleiro[i][j] = posicionado;

	proxima_posicao(i, j, N, &i_novo, &j_novo);

	do {
		printf("entrou no do\n");
		if(posicao_valida(i, j, tabuleiro, posicionado, N) &&
			 resolver(i_novo, j_novo, quadrados, tabuleiro, N))
			return TRUE;			
	} while(rotacionar(posicionado));
	
	return FALSE;

}



