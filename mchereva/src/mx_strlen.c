#include "../inc/matrix_rain.h"

int mx_strlen(char *s) {
    int res = 0;
    
    while (s[res] != '\0') {
        res++;
    }

    return res;
}
