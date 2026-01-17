#include <ncurses.h>

int main(void)
{
        char letter;

        initscr();      // init screen
        printw("Hello from ncurses, please press any key...");
        refresh();

        letter = getch();
        clear();
        printw("You pushed: '%c'", letter);
        refresh();

        getch();
        endwin();

        return 0;
}
