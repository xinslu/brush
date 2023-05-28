#pragma once

#define INIT_LINE_LENGTH 100
#define INIT_PATH_LENGTH 50

typedef struct {
    char **char_arr;
    int arr_size;
} res_t;


char *readline();
int main();
char *readline(void);
res_t parse_path(char *);
void brush_error(const char *);
int file_exists(char *);
