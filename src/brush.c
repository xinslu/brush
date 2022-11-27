#include "brush.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

int main() {
  char *curr_line;
  int status = 0;
  do {
    printf("$ ");
    fflush(stdout);
    curr_line = readline();
    printf("%s", curr_line);
  } while (status);
}

char *readline() {
  int i = 0;
  int c;
  int bufsize = INIT_LINE_LENGTH;
  char *buffer = malloc(sizeof(char) * INIT_LINE_LENGTH);
  if (!buffer) {
    printf("\033[0;31m");
    fprintf(stderr, "brush: error allocating memory");
    printf("\033[0m");
  }
  while (1) {
    c = getchar();
    if (c == EOF || c == '\n') {
      buffer[i] = '\0';
      return buffer;
    } else {
      buffer[i] = c;
    }
    i++;

    if (i >= bufsize) {
      bufsize += INIT_LINE_LENGTH;
      buffer = realloc(buffer, (unsigned int)bufsize);
      if (!buffer) {
        printf("\033[0;31m");
        fprintf(stderr, "brush: error allocating memory");
        printf("\033[0m");
      }
    }
  }
  return buffer;
}

void brush_error(char *message) {
  printf("\033[0;31m");
  fprintf(stderr, "%s", message);
  printf("\033[0m");
}
