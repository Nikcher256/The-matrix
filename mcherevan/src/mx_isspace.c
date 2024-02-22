#include <stdbool.h>

bool mx_isspace(char c) {
    return (c == ' ' || c == '\t' || c == '\n' || c == '\r' || c == '\f' || c == '\v');
}


