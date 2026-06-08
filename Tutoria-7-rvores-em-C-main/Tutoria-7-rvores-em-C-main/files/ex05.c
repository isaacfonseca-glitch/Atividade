#include <stdio.h>
#include <stdlib.h>

/* Exercício 5 — Comparando busca sequencial e busca em árvore */

typedef struct No {
    int valor;
    struct No *esq;
    struct No *dir;
} No;

No *criarNo(int valor) {
    No *n = (No *)malloc(sizeof(No));
    n->valor = valor; n->esq = NULL; n->dir = NULL;
    return n;
}

No *inserir(No *raiz, int valor) {
    if (raiz == NULL) return criarNo(valor);
    if (valor < raiz->valor) raiz->esq = inserir(raiz->esq, valor);
    else if (valor > raiz->valor) raiz->dir = inserir(raiz->dir, valor);
    return raiz;
}

/* ── Busca sequencial no vetor ────────────────── */
int buscaSequencial(int vetor[], int tamanho, int alvo, int *comparacoes) {
    *comparacoes = 0;
    for (int i = 0; i < tamanho; i++) {
        (*comparacoes)++;
        if (vetor[i] == alvo) return 1;
    }
    return 0;
}

/* ── Busca na árvore ──────────────────────────── */
int buscaArvore(No *raiz, int alvo, int *comparacoes) {
    if (raiz == NULL) return 0;
    (*comparacoes)++;
    if (alvo == raiz->valor) return 1;
    if (alvo < raiz->valor)  return buscaArvore(raiz->esq, alvo, comparacoes);
    return                          buscaArvore(raiz->dir, alvo, comparacoes);
}

void liberar(No *raiz) {
    if (raiz == NULL) return;
    liberar(raiz->esq); liberar(raiz->dir); free(raiz);
}

int main(void) {
    int valores[] = {50, 30, 70, 20, 40, 60, 80, 10, 25, 35,
                     45, 55, 65, 75, 85, 5,  15, 90, 95, 100};
    int tam = sizeof(valores) / sizeof(valores[0]);

    /* Monta árvore com os mesmos valores */
    No *raiz = NULL;
    for (int i = 0; i < tam; i++)
        raiz = inserir(raiz, valores[i]);

    int alvo = 75;
    int cmp1 = 0, cmp2 = 0;

    printf("=== COMPARAÇÃO DE BUSCAS ===\n\n");
    printf("Valor buscado: %d\n\n", alvo);

    /* Busca sequencial */
    int r1 = buscaSequencial(valores, tam, alvo, &cmp1);
    printf("Busca sequencial:\n");
    printf("  %s\n", r1 ? "Encontrado." : "Não encontrado.");
    printf("  Comparações: %d\n\n", cmp1);

    /* Busca na árvore */
    int r2 = buscaArvore(raiz, alvo, &cmp2);
    printf("Busca na árvore:\n");
    printf("  %s\n", r2 ? "Encontrado." : "Não encontrado.");
    printf("  Comparações: %d\n\n", cmp2);

    printf("Resultado: a árvore usou %d comparação(ões) contra %d da busca sequencial.\n",
           cmp2, cmp1);

    liberar(raiz);
    return 0;
}
