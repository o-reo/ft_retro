/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   testDisplayEntity.cpp                            .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: bpajot <bpajot@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/18 13:11:25 by bpajot       #+#   ##    ##    #+#       */
/*   Updated: 2020/01/18 15:35:51 by bpajot      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <ncurses.h>
#include "Player.hpp"
#include "Enemy.hpp"
#include "Missile.hpp"

int main(void)
{
    initscr();
    
	Player p(LINES / 2,  COLS / 3);
	Enemy e1(LINES / 3 , 3 * COLS / 4);
	Enemy e2(2 * LINES / 3, 3 * COLS / 4);
    
    while (1)
    {
        printw("Hello, SIZE_X=%d SIZE_Y=%d\n", LINES, COLS);
        printw("Player is at X=%d and Y=%d\n", p.getX(), p.getY());
        printw("Enemy 1 is at X=%d and Y=%d\n", e1.getX(), e1.getY());
        printw("Enemy 2 is at X=%d and Y=%d\n", e2.getX(), e2.getY());

        mvprintw(p.getX(), p.getY(), p.getC().c_str());
        mvprintw(e1.getX(), e1.getY(), e1.getC().c_str());
        mvprintw(e2.getX(), e2.getY(), e2.getC().c_str());

        refresh();
        if (getch())
            break;
    }
    endwin();
}