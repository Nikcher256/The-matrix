#include "../inc/matrix_rain.h"

void print_intro(WINDOW *window) {
    char **intro_string = malloc(sizeof(char*) * 4);
    
    intro_string[0] = "Wake up , Neo..";
    intro_string[1] = "The Matrix has you..";
    intro_string[2] = "Follow the white rabbit";
    intro_string[3] = "Knock, knock, Neo"; 
 
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < mx_strlen(intro_string[i]); j++) {
            mvwaddch(window, 2, 2 + j, intro_string[i][j]);
            refresh();
            //usleep(200000);
        }

        wclear(window);
    }

    free(intro_string);
}
