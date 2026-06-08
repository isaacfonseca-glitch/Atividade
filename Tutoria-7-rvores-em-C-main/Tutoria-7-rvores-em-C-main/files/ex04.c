#include <stdio.h>
#include <stdlib.h>

/* Exercício 4 — Remoção de nós (três casos) */

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

void emOrdem(No *raiz) {
    if (raiz == NULL) return;
    emOrdem(raiz->esq);
    printf("%d ", raiz->valor);
    emOrdem(raiz->dir);
}

/* Retorna o menor nó da subárvore (auxiliar) */
static No *menorNo(No *no) {
    while (no->esq != NULL) no = no->esq;
    return no;
}

/* ── Remover (três casos) ─────────────────────── */
No *remover(No *raiz, int valor) {
    if (raiz == NULL) {
        printf("Valor %d não encontrado.\n", valor);
        return NULL;
    }

    if (valor < raiz->valor) {
        raiz->esq = remover(raiz->esq, valor);

    } else if (valor > raiz->valor) {
        raiz->dir = remover(raiz->dir, valor);

    } else {
        /* Caso A: folha ou só filho direito */
        if (raiz->esq == NULL) {
            No *tmp = raiz->dir;
            free(raiz);
            return tmp;
        }
        /* Caso B: só filho esquerdo */
        if (raiz->dir == NULL) {
            No *tmp = raiz->esq;
            free(raiz);
            return tmp;
        }
        /* Caso C: dois filhos — substitui pelo sucessor */
        No *suc = menorNo(raiz->dir);
        raiz->valor = suc->valor;
        raiz->dir   = remover(raiz->dir, suc->valor);
    }
    return raiz;
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
     *     / \   / \
     *   20  40 60  80
     */
    int vals[] = {50, 30, 70, 20, 40, 60, 80};
    for (int i = 0; i < 7; i++)
        raiz = inserir(raiz, vals[i]);

    printf("=== REMOÇÃO DE NÓS ===\n\n");
    printf("Árvore inicial:    "); emOrdem(raiz); printf("\n\n");

    printf("Removendo 20 (folha — Caso A):\n");
    raiz = remover(raiz, 20);
    printf("Em ordem: "); emOrdem(raiz); printf("\n\n");

    printf("Removendo 30 (nó com filho — Caso B/C):\n");
    raiz = remover(raiz, 30);
    printf("Em ordem: "); emOrdem(raiz); printf("\n\n");

    printf("Removendo 50 (raiz com dois filhos — Caso C):\n");
    raiz = remover(raiz, 50);
    printf("Em ordem: "); emOrdem(raiz); printf("\n\n");

    liberar(raiz);
    return 0;
}
