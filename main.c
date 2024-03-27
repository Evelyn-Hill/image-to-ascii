#include <stdio.h>

int main() {

  FILE *pF = fopen("amogus.png", "r");
  FILE *pW = fopen("output.txt", "w");

  char fileOut[10000];

  while (fgets(fileOut, 10000, pF) != NULL) {
    fprintf(pW, "%s", fileOut);
  }

  fclose(pF);
  fclose(pW);

  return 0;
}
