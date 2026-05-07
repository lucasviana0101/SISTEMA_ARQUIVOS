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

Nodo *inserirNodo(Nodo *no, char nome[], enum tipo_nodo tipo, Pasta *pai) {

  if (!no) {
    Nodo *novo_no = criarNodo(nome, tipo);

    if (novo_no->base.tipo == T_PASTA)
      novo_no->pasta.pai = pai;

    return novo_no;
  }

  if (strcmp(nome, no->base.nome) < 0) {
    no->base.esq = inserirNodo(no->base.esq, nome, tipo, pai);
  } else if (strcmp(nome, no->base.nome) > 0) {
    no->base.dir = inserirNodo(no->base.dir, nome, tipo, pai);
  } else {
    printf("comando invalido\n");
    return no;
  }

  no->base.h = calcular_altura(no);

  return balancear(no);
}

Nodo *buscar(Nodo *raiz, char nome[]) {
  if (raiz) {
    if (strcmp(nome, raiz->base.nome) == 0) {
      return raiz;
    } else if (strcmp(nome, raiz->base.nome) < 0) {
      return buscar(raiz->base.esq, nome);
    } else
      return buscar(raiz->base.dir, nome);
  } else {
    return NULL;
  }
}

void liberarPasta(Nodo *no) {
  if (!no)
    return;

  liberarPasta(no->base.esq);

  free(no);

  liberarPasta(no->base.dir);
}

void liberarNodo(Nodo *no) {
  if (!no)
    return;

  if (no->base.tipo == T_PASTA) {
    liberarPasta(no->pasta.filho);
  }

  free(no);
  return;
}

Nodo *remover(Nodo *no, char nome[], int itrc) {
  Nodo *sucessor = no;

  if (!no) {
    printf("comando invalido\n");
    return no;
  }
  if (strcmp(nome, no->base.nome) < 0) {
    no->base.esq = remover(no->base.esq, nome, itrc);
  } else if (strcmp(nome, no->base.nome) > 0) {
    no->base.dir = remover(no->base.dir, nome, itrc);
  } else {
    // Caso 3
    if ((no->base.esq) && (no->base.dir)) {
      // printf("\nExclusão caso 3\n");
      Nodo *min_dir = no;
      Nodo *min_dir_pai = no;

      for (Nodo *p = no->base.dir; p != NULL; p = p->base.esq) {
        min_dir_pai = min_dir;
        min_dir = p;
      }

      min_dir_pai->base.dir = remover(min_dir, min_dir->base.nome, itrc + 1);

      min_dir->base.dir = no->base.dir;
      min_dir->base.esq = no->base.esq;

      min_dir->base.h = calcular_altura(min_dir);
      min_dir = balancear(min_dir);

      sucessor = min_dir;
    } else if (no->base.esq) {
      // printf("\nExclusão caso 2\n");
      sucessor = no->base.esq;
    } else if (no->base.dir) {
      // printf("\nExclusão caso 2\n");
      sucessor = no->base.dir;
    } else {
      // printf("\nExclusão caso 1\n");
      sucessor = NULL;
    }

    if (itrc == 0) {
      liberarNodo(no);
    }
  }

  return sucessor;
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
  Nodo *a = rotEsq(pivo->base.esq);
  pivo->base.esq = a;

  return rotDir(pivo);
}

Nodo *rotDirEsq(Nodo *pivo) {
  Nodo *a = rotDir(pivo->base.dir);
  pivo->base.dir = a;

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

void mostraArvore(Nodo *p, int nivel) {
  int i;
  if (p) {
    mostraArvore(p->base.dir, nivel + 1);
    printf("\n");
    for (i = 0; i < nivel; i++)
      printf("\t");
    printf("%s\n", p->base.nome);
    mostraArvore(p->base.esq, nivel + 1);
  }
}

void listar(Nodo *no) {
  if (no) {
    listar(no->base.esq);

    printf("%s", no->base.nome);

    if (no->base.tipo)
      putc('-', stdout);

    putc('\n', stdout);

    listar(no->base.dir);
  }
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
      // printf("\n");
      listar(corrente->filho);
    } else if (strcmp(cmd, "ma") == 0) {
      corrente->filho = inserirNodo(corrente->filho, argt, T_ARQUIVO, corrente);
    } else if (strcmp(cmd, "mp") == 0) {
      corrente->filho = inserirNodo(corrente->filho, argt, T_PASTA, corrente);
    } else if (strcmp(cmd, "cd") == 0) {
      if (strcmp(argt, "..") == 0) {
        if (corrente->pai)
          corrente = corrente->pai;
        continue;
      }
      Nodo *pasta = buscar(corrente->filho, argt);

      if (pasta && (pasta->base.tipo == T_PASTA)) {
        corrente = (Pasta *)pasta;
      } else {
        printf("comando invalido\n");
      }

    } else if (strcmp(cmd, "rm") == 0) {
      corrente->filho = remover(corrente->filho, argt, 0);
    } else if (strcmp(cmd, "tr") == 0) {
      mostraArvore(corrente->filho, 0);
    }
  } while (strcmp(cmd, "ex") != 0);

  liberarNodo(raiz.filho);
  printf("sistema encerrado\n");
  return 0;
}
