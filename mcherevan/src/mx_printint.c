#include "../inc/part_of_the_matrix.h"

void mx_printint(int n) {
    if (n < 0) {
        mx_printchar('-');
        n = -n;
    }

    if (n < 10) {
        mx_printchar(n + '0');
    } 
    else {
        mx_printint(n / 10);
        mx_printchar(n % 10 + '0');
    }
}
