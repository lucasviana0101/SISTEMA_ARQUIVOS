#include "main.h"
#include <stdio.h>
#include <string.h>

Nodo raiz = (Nodo){.esq = NULL,
                   .dir = NULL,
                   .centro = NULL,
                   .pai = NULL,
                   .h = 0,
                   .is_pasta = true,
                   .nome = ""};

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
    listar(p->esq);

    printf("%s", p->nome);

    if (p->is_pasta)
      putc('-', stdout);

    putc('\n', stdout);

    listar(p->dir);
  }
}

Nodo *inserirNodo(Nodo *no, char nome[], bool is_pasta) {
  if (!no) {
    no = criarNodo(nome, is_pasta);
    return no;
  }

  if (strcmp(nome, no->nome) <= 0) {
    no->esq = inserirNodo(no->esq, nome, is_pasta);
    no->esq->pai = no->pai;
  } else {
    no->dir = inserirNodo(no->dir, nome, is_pasta);
    no->dir->pai = no->pai;
  }

  return no;
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

void mostrar_prompt(Nodo *no, int itc) {
  if (no->pai != NULL)
    mostrar_prompt(no->pai, itc + 1);

  printf("%s-", no->nome);
  if (itc == 0)
    putc('>', stdout);
}

void prompt(char comando[], char argumento[]) {
  mostrar_prompt(corrente, 0);

  char str[NOME_ARQUIVO_TAM + 3];
  fflush(stdin);
  fgets(str, NOME_ARQUIVO_TAM + 3, stdin);

  copiarStr(comando, str, 0, 2);
  copiarStr(argumento, str, 3, NOME_ARQUIVO_TAM + 3);
}

int main() {

  char cmd[3], argt[NOME_ARQUIVO_TAM];
  do {
    prompt(cmd, argt);

    if (strcmp(cmd, "ls") == 0) {
      listar(corrente->centro);
    } else if (strcmp(cmd, "ma") == 0) {
      corrente->centro = inserirNodo(corrente->centro, argt, false);
      corrente->centro->pai = corrente;
    } else if (strcmp(cmd, "mp") == 0) {
      corrente->centro = inserirNodo(corrente->centro, argt, true);
      corrente->centro->pai = corrente;
    } else if (strcmp(cmd, "cd") == 0) {
      if (strcmp(argt, "..") == 0) {
        if (corrente->pai)
          corrente = corrente->pai;
        continue;
      }
      Nodo *pasta = buscar(corrente->centro, argt);

      if (pasta && pasta->is_pasta)
        corrente = pasta;

    } else if (strcmp(cmd, "rm") == 0) {
      // TODO
    }
  } while (strcmp(cmd, "ex") != 0);
  return 0;
}