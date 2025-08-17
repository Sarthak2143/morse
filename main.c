#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct data {
  char letter;
  char morse[6];
} data;

data *readData(char *fileName);
char *encodeLetter(char letter, data *table);
char decodeLetter(char *morse, data *table);

int main(void) {
  data *codes = readData("codes.csv");
  char *morse = encodeLetter('s', codes);
  printf("morse: %s\n", morse);
  char letter = decodeLetter(morse, codes);
  printf("letter: %c\n", letter);
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

char *encodeLetter(char letter, data *table) {
  for (size_t i = 0; i < 26; i++) {
    if (letter == table[i].letter) {
      return table[i].morse;
    }
  }
  return NULL;
}

char decodeLetter(char *morse, data *table) {
  for (size_t i = 0; i < 26; i++) {
    if (strcmp(morse, table[i].morse) == 0) {
      return table[i].letter;
    }
  }
  return NULL;
}
