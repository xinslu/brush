#include "brush.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

int main() {
  char *curr_line;
  int pid;
  char *username = getenv("LOGNAME");
  res_t res = split(getenv("PATH"), ":", 1);

  while (1) {

    printf("%s:$ ", username);
    curr_line = readline();

    if (*curr_line == EOF) {
      return 0;
    }

    res_t command = split(curr_line, " ", 0);
    char **argv = command.char_arr;

    pid = fork();

    if (pid == 0) {
      int status = 0;

      if (strcmp(argv[0], "cd") == 0) {
        chdir(argv[1]);
        status = 1;
      } else {

        for (int i = 0; i < res.arr_size; i++) {

          char *filename =
              malloc(strlen(res.char_arr[i]) + strlen(command.char_arr[0]));
          filename =
              strcat(strcpy(filename, res.char_arr[i]), command.char_arr[0]);

          if (file_exists(filename)) {
            status = 1;
            execv(filename, argv);
            fflush(stdout);
            break;
          }
        }

      }

      if (status == 0) {
        brush_error(strcat(command.char_arr[0], " command not found"));
      }

    } else if (pid != 0) {
      wait(0);
    }
    for (int i = 0; i < command.arr_size; i++) {
      free(command.char_arr[i]);
    }
    free(command.char_arr);
  }
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
      buffer = realloc(buffer, (unsigned int)bufsize);

      if (!buffer) {
        brush_error("Error Allocating Memory");
      }
    }
  }
  return buffer;
}

res_t split(char *path, const char *sp_char, int append) {

  char *split = strtok(path, sp_char);
  char **path_buffer = malloc(INIT_LINE_LENGTH);

  if (!path_buffer) {
    brush_error("Error Allocating Memory");
  }

  char *split_malloc;
  int elements = 0;
  int totalSize = strlen(split) + 1;
  int bufsize = INIT_LINE_LENGTH;

  while (split != NULL) {
    totalSize += (int)(strlen(split) + 1);
    split_malloc = malloc(strlen(split) + 1);

    if (!split_malloc) {
      brush_error("Error Allocating Memory");
    }

    strcpy(split_malloc, split);

    if (totalSize >= bufsize) {
      bufsize += INIT_LINE_LENGTH;
      path_buffer = realloc(path_buffer, (unsigned int)bufsize);
    }

    if (append) {
      path_buffer[elements] = strcat(split_malloc, "/");
    } else {
      path_buffer[elements] = split_malloc;
    }
    split = strtok(NULL, sp_char);
    elements++;
  }

  res_t path_arr = {path_buffer, elements};
  return path_arr;
}

void brush_error(const char *message) {
  printf("\033[0;31m");
  fprintf(stdout, "brush: %s\n", message);
  printf("\033[0m");
}
