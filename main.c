#include <stdio.h>
#include <stdlib.h>

typedef struct data {
  char letter;
  char morse[6];
} data;

data *readData(char *fileName);

int main(void) {
  printf("hello, world\n");
  data *codes = readData("codes.csv");
  for (int i = 0; codes[i].letter != '\0'; i++) {
    printf("%c: %s\n", codes[i].letter, codes[i].morse);
  }
  free(codes);
  codes = NULL;
  return 0;
}

data *readData(char *fileName) {
  FILE *fp = fopen(fileName, "r");
  if (fp == NULL) {
    fprintf(stderr, "Failed to open %s\n", fileName);
    return NULL;
  }
  data *codes = (data *)malloc(30 * sizeof(data));
  if (codes == NULL) {
    fprintf(stderr, "Failed to allocate memory\n");
    return NULL;
  }
  char line[10];
  int i = 0;
  while (fgets(line, sizeof(line), fp) != NULL) {
    codes[i].letter = line[0];
    for (int j = 2; line[j] != '\n'; j++) {
      codes[i].morse[j - 2] = line[j];
    }
    i++;
  }
  return codes;
}
