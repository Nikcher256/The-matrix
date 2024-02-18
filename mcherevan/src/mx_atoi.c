#include "../inc/part_of_the_matrix.h"


int mx_atoi(const char *str) {
    int result = 0;
    int sign = 1;

    while (mx_isspace(*str)) {
        str++;
    }
    if (*str == '+' || *str == '-') {
        sign = (*str == '-') ? -1 : 1;
        str++;
    }

    while (mx_isdigit(*str)) {
        int digit = *str - '0';

        if (result > (MX_INT_MAX - digit) / 10) {
            return (sign == 1) ? MX_INT_MAX : MX_INT_MIN;
        }

        result = result * 10 + digit;
        str++;
    }

    return result * sign;
}


