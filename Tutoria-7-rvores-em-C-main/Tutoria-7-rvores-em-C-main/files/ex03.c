#include <stdio.h>
#include <stdlib.h>

/* Exercício 3 — Menor e maior valor da árvore */

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

/* ── Menor valor (mais à esquerda) ───────────── */
int menorValor(No *raiz) {
    if (raiz == NULL) { printf("Árvore vazia.\n"); return -1; }
    while (raiz->esq != NULL)
        raiz = raiz->esq;
    return raiz->valor;
}

/* ── Maior valor (mais à direita) ────────────── */
int maiorValor(No *raiz) {
    if (raiz == NULL) { printf("Árvore vazia.\n"); return -1; }
    while (raiz->dir != NULL)
        raiz = raiz->dir;
    return raiz->valor;
}

void liberar(No *raiz) {
    if (raiz == NULL) return;
    liberar(raiz->esq); liberar(raiz->dir); free(raiz);
}

int main(void) {
    No *raiz = NULL;

    int vals[] = {50, 30, 70, 20, 40, 60, 80, 10, 25, 90};
    int n = sizeof(vals) / sizeof(vals[0]);

    printf("=== MENOR E MAIOR VALOR ===\n\nValores inseridos: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", vals[i]);
        raiz = inserir(raiz, vals[i]);
    }
    printf("\n\n");

    printf("Menor valor da árvore: %d\n", menorValor(raiz));
    printf("Maior valor da árvore: %d\n", maiorValor(raiz));

    liberar(raiz);
    return 0;
}
