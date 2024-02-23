#include "../inc/matrix_rain.h"

void screensaver_play(WINDOW *window, int argc, char *flag, int speed) {
    int rows;
    int columns;

    getmaxyx(window, columns, rows);
    start_color();

    init_pair(1, COLOR_WHITE, COLOR_BLACK);
    init_pair(2, COLOR_GREEN, COLOR_BLACK);
    init_pair(3, COLOR_RED, COLOR_BLACK);
    init_pair(4, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(5, COLOR_CYAN, COLOR_BLACK);
    init_pair(6, COLOR_YELLOW, COLOR_BLACK);
    init_pair(7, COLOR_BLUE, COLOR_BLACK);

    noecho();

    t_line *line_arr = malloc(sizeof(t_line) * rows);

    for (int i = 0; i < rows; i++) {
        line_arr[i].str = malloc(sizeof(wchar_t) * columns);

        for(int j = 0; j < columns; j++) {
            line_arr[i].str[j] = get_wchar();
        }

        line_arr[i].length = rand() % columns;
        line_arr[i].first = 0 - line_arr[i].length - line_arr[i].length;
        line_arr[i].last = 0 - line_arr[i].length;
    }

    wbkgd(window, COLOR_PAIR(2));
    int color = 2;
    
    wclear(window);

    if((argc == 2 && mx_strcmp(flag, "-s") == 0)) {
        print_intro(window);
    }

    while(true) {
        wtimeout(window, speed);

        if(getch() == 'q') {
            break;
        }

        switch(getch()) {
            case '-': 
                if (speed < 100) {
                    speed += 5;
                }
                break;
            case '+':
                if (speed > 20) {
                    speed -= 5;
                }
                break;
            case 'w':
                if (color > 2) {
                    color--;
                }
                break;
            case 's':
                if (color < 7) {
                    color++;
                }
                break;
        }
        wclear(window);

        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < columns; j++) {
                if(j >= line_arr[i].first && j <= line_arr[i].last) {
                    if(j == line_arr[i].last) {
                        attroff(COLOR_PAIR(color));
                        attron(COLOR_PAIR(1));
                    }

                    mvprintw(j, i + i, "%lc", line_arr[i].str[j]);

                    if(j == line_arr[i].last) {
                        attroff(COLOR_PAIR(1));
                        attron(COLOR_PAIR(color));
                    }

                    if(j == line_arr[i].first) {
                        line_arr[i].str[j] = get_wchar();
                    }

                    if(j == line_arr[i].last) {
                        line_arr[i].str[j] = get_wchar();
                    }
                }
            }
            line_arr[i].first++;
            line_arr[i].last++;

            if(line_arr[i].first > columns) {
                line_arr[i].length = rand() % columns;
                line_arr[i].first = 0 - line_arr[i].length - line_arr[i].length;
                line_arr[i].last = 0 - line_arr[i].length;
            }  
        }

        refresh();
    }

    for(int i = 0; i < columns; i++) {
        free(line_arr[i].str);
    }

    free(line_arr);
}
