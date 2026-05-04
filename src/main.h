#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CARACTERES_ESPECIAIS                                                   \
  (char[]) {                                                                   \
    '<', '>', ':', '\"', '/', '\\', '|', '-', '?', '*', 32, '\n', '\t'         \
  }

#define NOME_ARQUIVO_TAM 32

#define MAX(a, b) (a >= b) ? a : b
typedef struct nodo Nodo;

enum tipo_nodo {
  T_ARQUIVO,
  T_PASTA,
};

typedef struct {
  char nome[NOME_ARQUIVO_TAM];
  enum tipo_nodo tipo;
  int h;
  Nodo *esq;
  Nodo *dir;
} Arquivo;

typedef struct diretorio {
  Arquivo base;
  Nodo *filho;
  struct diretorio *pai;
} Pasta;

struct nodo {
  union {
    Arquivo base;
    Pasta pasta;
  };
};

Nodo *criarNodo(char nome[], enum tipo_nodo tipo);
Nodo *buscar(Nodo *raiz, char nome[]);
void listar(Nodo *p);
Nodo *inserirNodo(Nodo *raiz, char nome[], enum tipo_nodo tipo, Pasta *pai);
Nodo *remover(Nodo *raiz, char nome[], int itrc);
int calcular_altura(Nodo *raiz);
int fb(Nodo *p);
Nodo *rotEsq(Nodo *raiz);
Nodo *rotDir(Nodo *raiz);
Nodo *rotEsqDir(Nodo *raiz);
Nodo *rotDirEsq(Nodo *raiz);
Nodo *balancear(Nodo *raiz);
