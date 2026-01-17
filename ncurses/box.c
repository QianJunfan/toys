#include <ncurses.h>

int main(void)
{
        initscr();
        cbreak();
        noecho();
        curs_set(0);

        int h, w;
        getmaxyx(stdscr, h, w);

        int win_h = 10;
        int win_w = 40;
        int start_y = (h - win_h) / 2;
        int start_x = (h - win_w) / 2;

        WINDOW *my_win = newwin(win_h, win_w, start_y, start_x);

        box(my_win, 0, 0);

        mvwprintw(my_win, 0, 2, " This is a title ");
        mvwprintw(my_win, win_h / 2, (win_w - 14) / 2, "This is a box");

        wrefresh(my_win);

        wgetch(my_win);

        delwin(my_win);

        endwin();

        return 0;
}
