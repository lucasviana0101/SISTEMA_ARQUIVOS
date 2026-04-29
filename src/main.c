#include "main.h"
#include <stdio.h>
#include <string.h>

Nodo raiz = (Nodo){.esq = NULL,
                   .dir = NULL,
                   .centro = NULL,
                   .pai = NULL,
                   .h = 0,
                   .is_pasta = false};

Nodo *corrente = &raiz;
// Utils
void copiarStr(char dest[], char orig[], int ini, int fim) {
  int i = 0, tam = strlen(orig);
  while (i + ini < tam && i < fim - ini && orig[i + ini] != '\0' &&
         orig[i + ini] != '\n') {
    dest[i] = orig[i + ini];
    i++;
  }
  dest[i] = '\0';
}

// Arvore
Nodo *criarNodo(char nome[], bool pasta) {
  Nodo *p = (Nodo *)malloc(sizeof(Nodo));

  copiarStr(p->nome, nome, 0, NOME_ARQUIVO_TAM);

  p->is_pasta = pasta;
  p->centro = NULL;
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

void listar(Nodo *p) {
  int i;
  if (p) {
    listar(p->dir);
    printf("%s", p->nome);

    if (p->is_pasta)
      putc('-', stdout);

    putc('\n', stdout);

    listar(p->esq);
  }
}

Nodo *inserirNodo(Nodo *raiz, char nome[], bool is_pasta) {
  if (!raiz) {
    raiz = criarNodo(nome, is_pasta);
  } else {
    if (strcmp(nome, raiz->nome) <= 0) {
      raiz->esq = inserirNodo(raiz->esq, nome, is_pasta);
      raiz->esq->pai = raiz;
    } else {
      raiz->dir = inserirNodo(raiz->dir, nome, is_pasta);
      raiz->dir->pai = raiz;
    }
  }

  return raiz;
}

Nodo *buscar(Nodo *raiz, char nome[]) {
  if (raiz) {
    if (strcmp(nome, raiz->nome) == 0) {
      return raiz;
    } else if (strcmp(nome, raiz->nome) < 0) {
      return buscar(raiz->esq, nome);
    } else
      return buscar(raiz->dir, nome);
  } else
    return NULL;
}

Nodo *excluir(Nodo *raiz, int v) {}

int obter_comando(char comando[], char argumento[]) {
  char str[NOME_ARQUIVO_TAM + 3];
  fflush(stdin);
  fgets(str, NOME_ARQUIVO_TAM + 3, stdin);

  copiarStr(comando, str, 0, 2);
  copiarStr(argumento, str, 2, NOME_ARQUIVO_TAM + 3);
}

void mostrar_caminho() {};

int main() {
  mostrar_caminho();

  char cmd[3], argt[NOME_ARQUIVO_TAM];
  do {
    int a = obter_comando(cmd, argt);

    if (strcmp(cmd, "ls") == 0) {
      listar(corrente);
    } else if (strcmp(cmd, "ma") == 0) {
      inserirNodo(corrente, argt, false);
    } else if (strcmp(cmd, "mp") == 0) {
      inserirNodo(corrente, argt, true);
    } else if (strcmp(cmd, "cd") == 0) {
      Nodo *pasta = buscar(corrente, argt);

      if (pasta && pasta->is_pasta)
        corrente = pasta;

    } else if (strcmp(cmd, "rm") == 0) {
      // TODO
    }
  } while (strcmp(cmd, "ex") != 0);
  return 0;
}