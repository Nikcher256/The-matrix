#ifndef MATRIX_RAIN_H
#define MATRIX_RAIN_H

// Libs

#include <ncurses.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>

#include <locale.h>

typedef struct s_line {
    wchar_t *str;
    int length;
    int first;
    int last;
}               t_line;

// Program Initialize and Deinitialize

WINDOW *screensaver_new(int argc);
void screensaver_destroy(WINDOW *window);

// Start screen amination

void screensaver_play(WINDOW *window, int argc, char *flag, int speed);

void print_intro(WINDOW *window);
wchar_t get_wchar(void);

// Our implementation of C Standard functions

void mx_printerror(char *str);
int mx_strlen(char *s);
int mx_strcmp(const char *s1, const char *s2);

#endif
