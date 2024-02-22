#ifndef RACE02_H
#define RACE02_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h> 

#define MX_INT_MIN (-2147483647 - 1)
#define MX_INT_MAX 2147483647
#define MAX 100

typedef struct {
    int x, y;
} Point;

typedef struct {
    Point pt;
    int dist;
    Point pred;
} QueueNode;

typedef struct {
    QueueNode *nodes;
    int capacity;
    int front;
    int rear;
    int size;
} mx_queue;


bool mx_isspace(char c);
int mx_atoi(const char *str);
bool mx_isdigit(int c);
int mx_strlen(const char *s);


#endif
