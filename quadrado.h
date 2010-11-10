typedef struct quadrado_struct {
	int cima;
	int direita;
	int baixo;
	int esquerda;
} Quadrado;

typedef struct quadrado_posicionado_struct {
	Quadrado *quadrado;
	int rotacao;
} QuadradoPosicionado;

typedef struct pilha_quadrado_struct {
	Quadrado *quadrado;
	struct pilha_quadrado_struct *prox;
} PilhaQuadrado;

#define GRAU_0 0
#define GRAU_90 1
#define GRAU_180 2
#define GRAU_270 3
#define TRUE 1
#define FALSE 0
#define MAXNUMBER 16

Quadrado *novo_quadrado(int cima, int direita, int baixo, int esquerda);
QuadradoPosicionado *nova_posicao(Quadrado *quadrado, int rotacao);
int cor_de_cima(QuadradoPosicionado *posicionado);
int cor_da_direita(QuadradoPosicionado *posicionado);
int cor_de_baixo(QuadradoPosicionado *posicionado);
int cor_da_esquerda(QuadradoPosicionado *posicionado);
int rotacionar(QuadradoPosicionado *posicionado);
PilhaQuadrado *novo_quadrado_na_pilha(PilhaQuadrado *pilha, Quadrado *quadrado);
PilhaQuadrado *trocar_quadrado(PilhaQuadrado *pilha);
PilhaQuadrado *copiar_pilha(PilhaQuadrado *pilha);
void apagar_pilha(PilhaQuadrado *pilha);
