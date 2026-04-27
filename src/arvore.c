#include <stdio.h>
#include <stdlib.h>

typedef struct nodo {
  int valor;
  struct nodo *esq;
  struct nodo *dir;
  struct nodo *pai;
  int h;
} Nodo;

Nodo *criarNodo(int v);
Nodo *buscar(Nodo *raiz, int v);
void mostrarArvore(Nodo *p, int nivel);
Nodo *inserirNodo(Nodo *raiz, int v);
Nodo *excluir(Nodo *raiz, int v);
int fb(Nodo *p);
Nodo *rotEsq(Nodo *raiz);
Nodo *rotDir(Nodo *raiz);
Nodo *rotEsqDir(Nodo *raiz);
Nodo *rotDirEsq(Nodo *raiz);
Nodo *balancear(Nodo *raiz);

Nodo *criarNodo(int v) {
  Nodo *p = (Nodo *)malloc(sizeof(Nodo));
  p->valor = v;
  p->esq = NULL;
  p->dir = NULL;
  p->pai = NULL;
  p->h = 0;
  return p;
}

int fb(Nodo *p) { // fun��o de balanceamento
                  // completar
}

Nodo *rotDir(Nodo *raiz) {
  // completar
}

Nodo *rotEsq(Nodo *raiz) {
  // completar
}

Nodo *rotEsqDir(Nodo *raiz) {
  // completar
}

Nodo *rotDirEsq(Nodo *raiz) {
  // completar
}

Nodo *balancear(Nodo *raiz) {
  // completar
}

void mostraArvore(Nodo *p, int nivel) {
  int i;
  if (p) {
    mostraArvore(p->dir, nivel + 1);
    printf("\n");
    for (i = 0; i < nivel; i++)
      printf("\t");
    printf("%i [%i|%i]\n", p->valor, p->h, fb(p));
    mostraArvore(p->esq, nivel + 1);
  }
}

Nodo *inserirNodo(Nodo *raiz, int v) {
  if (!raiz) {
    raiz = criarNodo(v);
  } else {
    if (v <= raiz->valor) {
      raiz->esq = inserirNodo(raiz->esq, v);
      raiz->esq->pai = raiz;
    } else {
      raiz->dir = inserirNodo(raiz->dir, v);
      raiz->dir->pai = raiz;
    }
  }

  return raiz;
}

Nodo *buscar(Nodo *raiz, int v) {
  if (raiz) {
    if (v == raiz->valor) {
      return raiz;
    } else if (v < raiz->valor) {
      return buscar(raiz->esq, v);
    } else
      return buscar(raiz->dir, v);
  } else
    return NULL;
}

Nodo *excluir(Nodo *raiz, int v) {
  // completar
}
