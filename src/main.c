#include "main.h"
#include <stdio.h>
#include <string.h>

Pasta raiz = (Pasta){.base = {"", T_PASTA, 1, NULL, NULL}, NULL, NULL};

Pasta *corrente = &raiz;

// Utils
void copiarStr(char dest[], char orig[], int ini, int fim) {
  int i = 0;
  int contador_especiais = 0;
  int tam = strlen(orig);
  while (i + ini < tam && i < fim - ini && orig[i + ini] != '\0' &&
         orig[i + ini] != '\n') {
    if (strchr(CARACTERES_ESPECIAIS, orig[i + ini])) {
      contador_especiais++;
      i++;
      continue;
    }

    dest[i - contador_especiais] = orig[i + ini];
    i++;
  }
  dest[i] = '\0';
}

// Arvore
Nodo *criarNodo(char nome[], enum tipo_nodo tipo) {
  Nodo *p;
  if (tipo == T_PASTA)
    p = (Nodo *)calloc(1, sizeof(Pasta));
  else
    p = (Nodo *)calloc(1, sizeof(Arquivo));

  p->base.tipo = tipo;
  p->base.h = 1;

  copiarStr(p->base.nome, nome, 0, NOME_ARQUIVO_TAM);
  return p;
}

int calcular_altura(Nodo *raiz) {
  int esq_h = 0;
  int dir_h = 0;

  if (raiz->base.esq)
    esq_h = raiz->base.esq->base.h;

  if (raiz->base.dir)
    dir_h = raiz->base.dir->base.h;

  return ((esq_h >= dir_h) ? esq_h : dir_h) + 1;
}

int fb(Nodo *p) { // fun��o de balanceamento
  int esq_h = 0;
  int dir_h = 0;

  if (p->base.esq)
    esq_h = p->base.esq->base.h;

  if (p->base.dir)
    dir_h = p->base.dir->base.h;

  return esq_h - dir_h;
}

Nodo *rotDir(Nodo *pivo) {
  Nodo *a = pivo->base.esq;
  Nodo *b = a->base.dir;

  pivo->base.esq = b;
  a->base.dir = pivo;

  // Recalculando altura
  pivo->base.h = calcular_altura(pivo);
  a->base.h = calcular_altura(a);

  return a;
}

Nodo *rotEsq(Nodo *pivo) {
  Nodo *a = pivo->base.dir;
  Nodo *b = a->base.esq;

  pivo->base.dir = b;
  a->base.esq = pivo;

  // Recalculando altura
  pivo->base.h = calcular_altura(pivo);
  a->base.h = calcular_altura(a);

  return a;
}

Nodo *rotEsqDir(Nodo *pivo) {
  pivo->base.esq = rotEsq(pivo->base.esq);

  return rotDir(pivo);
}

Nodo *rotDirEsq(Nodo *pivo) {
  pivo->base.dir = rotDir(pivo->base.dir);

  return rotEsq(pivo);
}

Nodo *balancear(Nodo *pivo) {
  if (fb(pivo) > 1) {
    if (fb(pivo->base.esq) > 0)
      return rotDir(pivo);

    if (fb(pivo->base.esq) < 0)
      return rotEsqDir(pivo);

  } else if (fb(pivo) < -1) {
    if (fb(pivo->base.dir) < 0)
      return rotEsq(pivo);

    if (fb(pivo->base.dir) > 0)
      return rotDirEsq(pivo);
  }

  return pivo;
}

void listar(Nodo *p) {
  int i;
  if (p) {
    listar(p->base.esq);

    printf("%s", p->base.nome);

    if (p->base.tipo)
      putc('-', stdout);

    putc('\n', stdout);

    listar(p->base.dir);
  }
}

Nodo *inserirNodo(Nodo *no, char nome[], enum tipo_nodo tipo) {
  if (!no) {
    return criarNodo(nome, tipo);
  }

  if (strcmp(nome, no->base.nome) <= 0) {
    no->base.esq = inserirNodo(no->base.esq, nome, tipo);
    no->base.esq->base.pai = no;
    no->base.h = calcular_altura(no);
    return balancear(no->base.esq);
  } else {
    no->base.dir = inserirNodo(no->base.dir, nome, tipo);
    no->base.dir->base.pai = no;
    no->base.h = calcular_altura(no);
    return balancear(no->base.dir);
  }

  return NULL;
}

Nodo *buscar(Nodo *raiz, char nome[]) {
  if (raiz) {
    if (strcmp(nome, raiz->base.nome) == 0) {
      return raiz;
    } else if (strcmp(nome, raiz->base.nome) < 0) {
      return buscar(raiz->base.esq, nome);
    } else
      return buscar(raiz->base.dir, nome);
  } else
    return NULL;
}

Nodo *buscar_minimo(Nodo *raiz) {
  if (raiz->base.esq)
    return buscar_minimo(raiz->base.esq);

  return raiz;
}

Nodo *excluir(Nodo *raiz, char nome[]) {
  Nodo *no = buscar(raiz, nome);

  // Caso 1
  if ((no->base.esq == NULL) && (no->base.dir == NULL)) {
    free(no);
    return NULL;
  }
  // Caso 2
  if (no->base.esq == NULL) {
    Nodo *sucessor = no->base.dir;
    free(no);
    return sucessor;
  } else if (no->base.dir == NULL) {
    Nodo *sucessor = no->base.esq;
    free(no);
    return sucessor;
  }
  // Caso 3
  Nodo *sucessor = buscar_minimo(no);
  return NULL;
}

void mostrar_prompt(Pasta *no, int itc) {
  if (no->pai != NULL)
    mostrar_prompt(no->pai, itc + 1);

  printf("%s-", no->base.nome);
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
      listar(corrente->filho);
    } else if (strcmp(cmd, "ma") == 0) {
      corrente->filho = inserirNodo(corrente->filho, argt, false);
      corrente->filho->base.pai = (Nodo *)corrente;
    } else if (strcmp(cmd, "mp") == 0) {
      corrente->filho = inserirNodo(corrente->filho, argt, true);
      corrente->filho->pasta.pai = corrente;
      printf("\nSou %s e meu pai é %s\n", corrente->filho->base.nome,
             corrente->filho->pasta.pai->base.nome);
    } else if (strcmp(cmd, "cd") == 0) {
      if (strcmp(argt, "..") == 0) {
        if (corrente->pai)
          corrente = corrente->pai;
        continue;
      }
      Nodo *pasta = buscar(corrente->filho, argt);

      if (pasta && (pasta->base.tipo == T_PASTA))
        corrente = (Pasta *)pasta;

    } else if (strcmp(cmd, "rm") == 0) {
      // TODO
    }
  } while (strcmp(cmd, "ex") != 0);
  return 0;
}