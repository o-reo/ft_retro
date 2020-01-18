#include <ncurses.h>

int main(void)
{
    initscr();
    printw("Hello");
    refresh();
    getch();
    endwin();
}