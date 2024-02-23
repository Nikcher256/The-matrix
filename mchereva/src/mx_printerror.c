#include "../inc/matrix_rain.h"

void mx_printerror(char *str) {
    write(STDERR_FILENO, str, mx_strlen(str));
}
