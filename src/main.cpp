/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main.cpp                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: bpajot <bpajot@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/18 13:11:25 by bpajot       #+#   ##    ##    #+#       */
/*   Updated: 2020/01/18 13:22:25 by bpajot      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <ncurses.h>
#include "Player.hpp"
#include "Enemy.hpp"
#include "Missile.hpp"

int main(void)
{
	Player p(5, 5);
	Enemy e1(10, 2);
	Enemy e2(10, 8);
    
    initscr();
    printw("Hello, SIZE_X=%d SIZE_Y=%d", LINES, COLS);
    refresh();
    getch();
    endwin();
}