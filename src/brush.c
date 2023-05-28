#include "brush.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <sys/stat.h>

int main() {
  char *curr_line;
  int status = 0;
  int pid;
  char *username = getenv("LOGNAME");
  Path res = parse_path(getenv("PATH"));
  do {
    printf("%s:$ ", username);
    fflush(stdout);
    curr_line = readline();
    if (*curr_line == EOF) {
      return 0;
    }
    pid = fork();
    if (pid == 0) {
      for (int i = 0; i < res.elements; i++) {
        char *filename = strcat(strcat(res.path_elem[i], "/"), curr_line);
        if (file_exists(filename)) {
            char *argv;
            execv(filename, &argv);
            status = 1;
            break;
        }
      }
    }
  } while (status);
}

int file_exists(char *filename) {
  struct stat buffer;
  return (stat(filename, &buffer) == 0);
}

char *readline() {
  int i = 0;
  int c;
  int bufsize = INIT_LINE_LENGTH;
  char *buffer = malloc(INIT_LINE_LENGTH);
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
      buffer = realloc(buffer, (unsigned int) bufsize);
      if (!buffer) {
        brush_error("Error Allocating Memory");
      }
    }
  }
  return buffer;
}
Path parse_path(char *path) {
  char *split = strtok(path, ":");
  char **path_buffer = malloc(INIT_PATH_LENGTH);
  char *split_malloc;
  int elements = 0;
  int totalSize = strlen(split)+1;
  int bufsize = INIT_PATH_LENGTH;
  while (split != NULL) {
    totalSize += (int)(strlen(split)+1);
    split_malloc = malloc(strlen(split)+1);
    strcpy(split_malloc, split);
    if (totalSize >= bufsize) {
      bufsize += INIT_PATH_LENGTH;
      path_buffer = realloc(path_buffer, (unsigned int) bufsize);
    }
    path_buffer[elements] = split_malloc;
    split = strtok(NULL, ":");
    elements++;
  }
  Path path_arr= {path_buffer, elements};
  return path_arr;
}


void brush_error(const char *message) {
  printf("\033[0;31m");
  fprintf(stderr, "brush: %s", message);
  printf("\033[0m");
}
