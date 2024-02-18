#ifndef PART_OF_THE_MATRIX_H
#define PART_OF_THE_MATRIX_H

#define MX_INT_MIN (-2147483647 - 1)
#define MX_INT_MAX 2147483647

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>

double mx_pow(double n, unsigned int pow);
char* mx_strchr(const char* s, int c);
char *mx_strcpy(char *dst, const char *src);
void mx_printint(int n);
bool mx_isspace(char c);
void mx_printchar(char c);
int mx_atoi(const char *str);
bool mx_isdigit(int c);
int mx_strlen(const char *s);
void mx_printerr(const char *s);

#endif
