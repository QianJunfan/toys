#include <ncurses.h>

int main(void)
{
        int x, y;

        initscr();
        clear();

        getyx(stdscr, y, x);

        printw("x = %d, y = %d", x, y);

        refresh();
        
        y = 5;
        x = 10;
        
        move(y, x);
        printw("Over Here");

        getch();
        endwin();

        return 0;
}
