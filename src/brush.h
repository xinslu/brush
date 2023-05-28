#pragma once

#define INIT_LINE_LENGTH 100
#define INIT_PATH_LENGTH 50

typedef struct {
    char **char_arr;
    int arr_size;
} res_t;


int main();
res_t split(char *, const char *, int);
void brush_error(const char *);
int file_exists(char *);
char *readline(void);
