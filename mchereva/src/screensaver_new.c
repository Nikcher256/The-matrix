#include "../inc/matrix_rain.h"

WINDOW *screensaver_new(int argc) {
    // setlocale <- Set locale for Japanese letters

    // Parse usage error

    if(argc > 2) {
        mx_printerror("usage: ./matrix_rain [-s]\n");
        exit(0);
    }

    WINDOW* window = initscr();

    // Parse creation error

    if(window == NULL) {
        mx_printerror("ERROR\n");
        exit(0);
    }

    start_color();
    curs_set(false);

    return window;
}
