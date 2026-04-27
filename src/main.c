#include <stdio.h>
#include <string.h>

void copiarStr(char dest[], char orig[], int ini, int fim) {
  int i = 0, tam = strlen(orig);
  while (i + ini < tam && i < fim - ini && orig[i + ini] != '\0' &&
         orig[i + ini] != '\n') {
    dest[i] = orig[i + ini];
    i++;
  }
  dest[i] = '\0';
}

void obter_comando(char cmd[]) {
  char str[14];
  fflush(stdin);
  fgets(str, 14, stdin);
  copiarStr(cmd, str, 0, 2);
  copiarStr(cmd, str, 0, 2);
}

void mostrar_caminho() {};

int main() {
  mostrar_caminho();

  char cmd[3];
  do {
    obter_comando(cmd);
  } while (strcmp(cmd, "ex") != 0);
  return 0;
}