#include "brush.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

int main() {
  char *curr_line;
  int status = 0;
  int pid;
  char *username = getenv("LOGNAME");
  do {
    printf("%s:$ ", username);
    fflush(stdout);
    curr_line = readline();
    if (*curr_line == EOF) {
      return 0;
    }
    printf("Line: %s\n", curr_line);
    pid = fork();
    if (pid == 0) {
      parse_path(getenv("PATH"));
    }
  } while (status);
}

char *readline() {
  int i = 0;
  int c;
  int bufsize = INIT_LINE_LENGTH;
  char *buffer = malloc(sizeof(char) * INIT_LINE_LENGTH);
  if (!buffer) {
    brush_error("Error Allocating Memory");
  }
  while (1) {
    c = getchar();
    if (c == '\n') {
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
        brush_error("Error Allocating Memory");
      }
    }
  }
  return buffer;
}

void parse_path(char *path) {
  char *split = strtok(path, ":");
  while (split != NULL) {
    printf("%s\n", split);
    split = strtok(NULL, ":");
  }
}

void brush_error(const char *message) {
  printf("\033[0;31m");
  fprintf(stderr, "brush: %s", message);
  printf("\033[0m");
}
