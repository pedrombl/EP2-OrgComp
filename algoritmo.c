#include "quadrado.h"
#include "algoritmo.h"
#include <stdio.h>
#include <stdlib.h>


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
		(*novo_i) = i+1;
		(*novo_j) = 0;
	}
}

void posicao_anterior(int i, int j, const int N, int *novo_i, int *novo_j) {
	j--;
	if(j >= 0) {
		(*novo_i) = i;
		(*novo_j) = j;
	}
	else {
		(*novo_i) = i-1;
		(*novo_j) = N-1;
	}
}


int testar_posicoes_com_um_quadrado(const int i, const int j, 
																		const int i_novo, const int j_novo,
																		PilhaQuadrado *pilha,
																		QuadradoPosicionado *posicionado, 
																		QuadradoPosicionado *tabuleiro[][MAXNUMBER],
																		const int N) {
	do {
		if(posicao_valida(i, j, tabuleiro, posicionado, N) &&
			 resolver(i_novo, j_novo, pilha->prox, tabuleiro, N)) {
			apagar_pilha(pilha);
			return TRUE;
		}
	} while(rotacionar(posicionado));
	return FALSE;
}

int testar_com_quadrados_sobrando(const int i, const int j,
																	const int i_novo, const int j_novo,
																	PilhaQuadrado *pilha,
																	QuadradoPosicionado *tabuleiro[][MAXNUMBER],
																	const int N) {
	int x =0;
	int quadrados_sobrando = N*N - (i*N + j);
	QuadradoPosicionado *posicionado;	
	do {
		posicionado = nova_posicao(pilha->quadrado, GRAU_0);
		tabuleiro[i][j] = posicionado;

		if(testar_posicoes_com_um_quadrado(i, j, i_novo, j_novo, pilha, posicionado, tabuleiro, N))
			return TRUE;

		free(posicionado);
		pilha = trocar_quadrado(pilha);
		x++;
	} while(x<quadrados_sobrando);
	return FALSE;
}

int resolver(const int i, const int j, 
						PilhaQuadrado *pilha_antiga,
						QuadradoPosicionado *tabuleiro[][MAXNUMBER],
						const int N)
{

	int i_novo, j_novo;
	PilhaQuadrado *pilha;
	
	printf("posicao atual: %d %d\n", i, j);
	if(i == N)
		return TRUE;

	pilha = copiar_pilha(pilha_antiga);
	proxima_posicao(i, j, N, &i_novo, &j_novo);	
	
	return testar_com_quadrados_sobrando(i, j, i_novo, j_novo, pilha, tabuleiro, N);
}

int achar_posicao_correta(const int i, const int j,
													QuadradoPosicionado *tabuleiro[][MAXNUMBER],
													QuadradoPosicionado *posicionado,
													const int N) {

	do {
		if(posicao_valida(i, j, tabuleiro, posicionado, N)) {
			printf("certo!!\n");			
			return TRUE;
		}
	} while(rotacionar(posicionado));
	printf("errado!!\n");	
	return FALSE;
}

int achar_peca_correta(const int i, const int j, 
											 PilhaQuadrado *atual, 
											 QuadradoPosicionado *tabuleiro[][MAXNUMBER],
											 const int N, int qtdes[]) {
	const int x=(i*N) + j;
	int total = N*N;
	int q = qtdes[x];
	QuadradoPosicionado *posicionado;
	printf("x: %d q: %d, qtdes[x]:%d\n", x, q, qtdes[x]);
	for(q++; q <= (total-x) ; q++)	{
		posicionado = nova_posicao(atual->quadrado, GRAU_0);
		tabuleiro[i][j] = posicionado;
		if(achar_posicao_correta(i, j, tabuleiro, posicionado, N)) {
			printf("certo!\n");
			qtdes[x] = q;
			return TRUE;
		}
		free(posicionado);
		atual = trocar_quadrado(atual);
		printf("%d\n", q);
	}
	qtdes[x] = q;
	printf("errado!\n");
	return FALSE;

}

void zerar_vetor_a_partir(int qtdes[], const int pos, const int N) {
	int i = pos, total = N*N;
	for(i = pos; i<total; i++) {
		qtdes[i] = 0;
	}
}

int resolver_sequencialmente(PilhaQuadrado *pilha, QuadradoPosicionado *tabuleiro[][MAXNUMBER], const int N) {
	int i=0, j=0;
	int proximo, x=0;
	int qtdes[MAXNUMBER*MAXNUMBER];
	PilhaQuadrado *index[MAXNUMBER];
	PilhaQuadrado *atual = pilha;
	
	zerar_vetor_a_partir(qtdes, 0, N);
	while(atual != NULL && x >= 0) {
		proximo = FALSE;
		printf("%d %d\n", i, j);		
		if(achar_peca_correta(i, j, atual, tabuleiro, N, qtdes)) {
			printf("certo\n");
			index[x] = atual;
			atual = atual->prox;
			x++;
			proxima_posicao(i, j, N, &i, &j);
		}
		else {
			printf("errado\n");
			zerar_vetor_a_partir(qtdes, x, N);
			x--;
			if(x<0)
				break;
			index[x]->prox = atual;
			atual = index[x];
			posicao_anterior(i, j, N, &i, &j);
		}
	}
	if(x<0)
		return FALSE;
	return TRUE;
}



