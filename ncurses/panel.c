#include <ncurses.h>
#include <panel.h>

int main()
{
        WINDOW *wins[3];
        PANEL  *panels[3];

        char *labels[] = {" Label 1", " Label 2", " Label 3"};
        int lines = 10;
        int cols  = 40;
        int y = 2;
        int x = 4;

        // Init
        initscr();
        start_color();
        cbreak();
        noecho();
        keypad(stdscr, TRUE);

        // Init Color
        init_pair(1, COLOR_RED, COLOR_BLACK);
        init_pair(2, COLOR_GREEN, COLOR_BLACK);
        init_pair(3, COLOR_BLUE, COLOR_BLACK);
        
        for (int i = 0; i < 3; ++i) {
                wins[i] = newwin(lines, cols, y + ( i * 3), x + (i * 5));

                box(wins[i], 0, 0);
                mvwprintw(wins[i], 1, 1, "%s", labels[i]);
                mvwprintw(wins[i], lines / 2, 2, "Press Tab to switch");

                wbkgd(wins[i], COLOR_PAIR(i + 1));

                panels[i] = new_panel(wins[i]);
        }

        int ch;
        int top_idx = 2;
        while ((ch = getch()) != 'q') {
                if (ch == '\t') {
                        top_idx = (top_idx + 1) % 3;
                        top_panel(panels[top_idx]);
                }

                update_panels();
                doupdate();
        }

        endwin();
        return 0;
}
