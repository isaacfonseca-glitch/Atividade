#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Exercício 1 — Cadastro de alunos com árvore binária de busca */

typedef struct Aluno {
    int matricula;
    char nome[50];
    float nota;
} Aluno;

typedef struct No {
    Aluno aluno;
    struct No *esq;
    struct No *dir;
} No;

/* ── Criar nó ─────────────────────────────────── */
No *criarNo(int matricula, const char *nome, float nota) {
    No *novo = (No *)malloc(sizeof(No));
    novo->aluno.matricula = matricula;
    strncpy(novo->aluno.nome, nome, 49);
    novo->aluno.nota = nota;
    novo->esq = NULL;
    novo->dir = NULL;
    return novo;
}

/* ── Inserir ──────────────────────────────────── */
No *inserir(No *raiz, int matricula, const char *nome, float nota) {
    if (raiz == NULL)
        return criarNo(matricula, nome, nota);
    if (matricula < raiz->aluno.matricula)
        raiz->esq = inserir(raiz->esq, matricula, nome, nota);
    else if (matricula > raiz->aluno.matricula)
        raiz->dir = inserir(raiz->dir, matricula, nome, nota);
    else
        printf("Matrícula %d já existe.\n", matricula);
    return raiz;
}

/* ── Buscar ───────────────────────────────────── */
No *buscar(No *raiz, int matricula) {
    if (raiz == NULL || raiz->aluno.matricula == matricula)
        return raiz;
    if (matricula < raiz->aluno.matricula)
        return buscar(raiz->esq, matricula);
    return buscar(raiz->dir, matricula);
}

/* ── Em ordem (matrícula crescente) ──────────── */
void emOrdem(No *raiz) {
    if (raiz == NULL) return;
    emOrdem(raiz->esq);
    printf("%-6d - %-20s - Nota: %.1f\n",
           raiz->aluno.matricula,
           raiz->aluno.nome,
           raiz->aluno.nota);
    emOrdem(raiz->dir);
}

/* ── Liberar ──────────────────────────────────── */
void liberar(No *raiz) {
    if (raiz == NULL) return;
    liberar(raiz->esq);
    liberar(raiz->dir);
    free(raiz);
}

/* ── Main ─────────────────────────────────────── */
int main(void) {
    No *raiz = NULL;

    printf("=== CADASTRO DE ALUNOS ===\n\n");

    // Inserções
    printf("Inserindo aluno 102 - Ana\n");
    raiz = inserir(raiz, 102, "Ana", 9.0f);

    printf("Inserindo aluno 55  - Bruno\n");
    raiz = inserir(raiz, 55, "Bruno", 8.5f);

    printf("Inserindo aluno 180 - Carla\n");
    raiz = inserir(raiz, 180, "Carla", 7.5f);

    printf("Inserindo aluno 77  - Diego\n");
    raiz = inserir(raiz, 77, "Diego", 6.0f);

    printf("Inserindo aluno 210 - Eva\n");
    raiz = inserir(raiz, 210, "Eva", 9.5f);

    // Listar em ordem
    printf("\nAlunos em ordem crescente de matrícula:\n");
    printf("%-6s   %-20s   %s\n", "Mat.", "Nome", "Nota");
    printf("--------------------------------------\n");
    emOrdem(raiz);

    // Buscar existente
    printf("\nBuscar matrícula 102:\n");
    No *resultado = buscar(raiz, 102);
    if (resultado)
        printf("Aluno encontrado: %s (Nota: %.1f)\n",
               resultado->aluno.nome, resultado->aluno.nota);
    else
        printf("Matrícula não encontrada.\n");

    // Buscar inexistente
    printf("\nBuscar matrícula 999:\n");
    resultado = buscar(raiz, 999);
    if (resultado)
        printf("Aluno encontrado: %s\n", resultado->aluno.nome);
    else
        printf("Matrícula 999 não encontrada.\n");

    liberar(raiz);
    return 0;
}
