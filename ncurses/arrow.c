#include <ncurses.h>

int main(void)
{
        int key, x, y;
        initscr();
        keypad(stdscr, TRUE);
        noecho();
        
        x = 5;
        y = 5;

        move(y, x);
start:
        if (key == 'q')
                return 0;

        clear();

        move(0, 0);
        printw("Press left or right arrow - exit by pressing: q");

        move(y, x);
        printw("O");
        refresh();

        key = getch();
        if (key == KEY_LEFT) {
                x--;
                if (x < 0)
                        x = 0;
        } else if (key == KEY_RIGHT) {
                x++;
                if (x > 30)
                        x = 30;
        }
        
        goto start;
        return 0;
}
