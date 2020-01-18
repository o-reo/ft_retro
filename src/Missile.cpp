/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   Missile.cpp                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: bpajot <bpajot@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/18 12:54:19 by bpajot       #+#   ##    ##    #+#       */
/*   Updated: 2020/01/18 12:59:33 by bpajot      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "Missile.hpp"

Missile::Missile(unsigned int x, unsigned int y) : Entity()
{
	this->_type = "Missile";
	this->_c = '-';
	this->_isAlive = true;
	this->_x = x;
	this->_y= y;
}

Missile::~Missile(void)
{
}

void	Missile::updatePos(void)
{
	//direction depends if it's from Player (x++) or fron Enemy (x--)
}