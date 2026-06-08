# Tutoria 7 — Árvores Binárias de Busca

**Aluno:** Isaac de Lima 
 
## Exercícios concluídos

| Exercício | Descrição | Status |
|-----------|-----------|--------|
| 01 | Cadastro de alunos com BST | ✅ |
| 02 | Contagem de nós, folhas, altura | ✅ |
| 03 | Menor e maior valor | ✅ |
| 04 | Remoção (três casos) | ✅ |
| 05 | Comparação busca sequencial × árvore | ✅ |



## Como compilar e executar

```bash
# Exercício 1
gcc exercicio-01/ex01.c -o ex01 && ./ex01

# Exercício 2
gcc exercicio-02/ex02.c -o ex02 && ./ex02

# Exercício 3
gcc exercicio-03/ex03.c -o ex03 && ./ex03

# Exercício 4
gcc exercicio-04/ex04.c -o ex04 && ./ex04

# Exercício 5
gcc exercicio-05/ex05.c -o ex05 && ./ex05
```



## Respostas teóricas

### Exercício 3 — Por que não percorre a árvore inteira?

Na BST, os valores seguem uma ordem: menores à esquerda, maiores à direita.
O menor valor SEMPRE está no nó mais à esquerda e o maior no mais à direita.
Então basta descer por um único caminho — não precisa visitar todos os nós.

### Exercício 5 — Perguntas

**Qual busca fez menos comparações?**  
A busca na árvore, pois descarta metade dos nós a cada comparação.

**A árvore sempre será melhor?**  
Não. Se os valores forem inseridos já em ordem crescente ou decrescente,
a árvore vira uma lista encadeada (degenerada) e a busca fica O(n),
igual à busca sequencial.

**O que acontece com valores inseridos em ordem?**  
A árvore fica desbalanceada — todos os nós só têm filho direito (ou esquerdo),
formando uma linha em vez de uma árvore. A altura vira n.

**Como uma árvore balanceada ajudaria?**  
Árvores como AVL ou Rubro-Negra rebalanceiam automaticamente após cada
inserção, garantindo altura O(log n) e busca eficiente em qualquer caso.


## Principais dificuldades

- Entender o Caso C da remoção (dois filhos) e o uso do sucessor in-order.
- Implementar as contagens recursivas sem contar nós errados.
