#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CARACTERES_ESPECIAIS                                                   \
  (char[]) {                                                                   \
    '<', '>', ':', '\"', '/', '\\', '|', '-', '?', '*', 32, '\n', '\t'         \
  }

#define NOME_ARQUIVO_TAM 32

typedef struct nodo {
  char nome[NOME_ARQUIVO_TAM];
  bool is_pasta;
  struct nodo *esq;
  struct nodo *dir;
  struct nodo *centro; // EXCLUSIVO PARA DIRETORIOS
  struct nodo *pai;
  int h;
} Nodo;

Nodo *criarNodo(char nome[], bool is_pasta);
Nodo *buscar(Nodo *raiz, char nome[]);
void listar(Nodo *p);
Nodo *inserirNodo(Nodo *raiz, char nome[], bool is_pasta);
Nodo *excluir(Nodo *raiz, int v);
int fb(Nodo *p);
Nodo *rotEsq(Nodo *raiz);
Nodo *rotDir(Nodo *raiz);
Nodo *rotEsqDir(Nodo *raiz);
Nodo *rotDirEsq(Nodo *raiz);
Nodo *balancear(Nodo *raiz);
