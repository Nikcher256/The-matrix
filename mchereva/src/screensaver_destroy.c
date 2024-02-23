#include "../inc/matrix_rain.h"

void screensaver_destroy(WINDOW *window) {
    delwin(window);
    endwin();
    exit(0);
}
