#include <stdio.h>
#include <stdlib.h>

/* Exercício 2 — Contando elementos da árvore */

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

/* ── Contar todos os nós ──────────────────────── */
int contarNos(No *raiz) {
    if (raiz == NULL) return 0;
    return 1 + contarNos(raiz->esq) + contarNos(raiz->dir);
}

/* ── Contar folhas ────────────────────────────── */
int contarFolhas(No *raiz) {
    if (raiz == NULL) return 0;
    if (raiz->esq == NULL && raiz->dir == NULL) return 1;
    return contarFolhas(raiz->esq) + contarFolhas(raiz->dir);
}

/* ── Contar nós com dois filhos ───────────────── */
int contarNosComDoisFilhos(No *raiz) {
    if (raiz == NULL) return 0;
    int atual = (raiz->esq != NULL && raiz->dir != NULL) ? 1 : 0;
    return atual + contarNosComDoisFilhos(raiz->esq)
                 + contarNosComDoisFilhos(raiz->dir);
}

/* ── Altura da árvore ─────────────────────────── */
int altura(No *raiz) {
    if (raiz == NULL) return 0;
    int he = altura(raiz->esq);
    int hd = altura(raiz->dir);
    return 1 + (he > hd ? he : hd);
}

void liberar(No *raiz) {
    if (raiz == NULL) return;
    liberar(raiz->esq); liberar(raiz->dir); free(raiz);
}

int main(void) {
    No *raiz = NULL;

    /*
     *         50
     *        /  \
     *      30    70
     *     / \      \
     *   20  40      80
     */
    int vals[] = {50, 30, 70, 20, 40, 80};
    for (int i = 0; i < 6; i++)
        raiz = inserir(raiz, vals[i]);

    printf("=== CONTAGEM DE NÓS ===\n\n");
    printf("Total de nós:          %d\n", contarNos(raiz));
    printf("Total de folhas:       %d\n", contarFolhas(raiz));
    printf("Nós com dois filhos:   %d\n", contarNosComDoisFilhos(raiz));
    printf("Altura da árvore:      %d\n", altura(raiz));

    liberar(raiz);
    return 0;
}
