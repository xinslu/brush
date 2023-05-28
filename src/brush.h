#pragma once

#define INIT_LINE_LENGTH 100
#define INIT_PATH_LENGTH 50

typedef struct {
    char **path_elem;
    int elements;
} Path;


char *readline();
int main();
char *readline(void);
Path parse_path(char *);
void brush_error(const char *);
int file_exists(char *);
