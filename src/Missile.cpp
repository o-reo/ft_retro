/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   Missile.cpp                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: bpajot <bpajot@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/18 12:54:19 by bpajot       #+#   ##    ##    #+#       */
/*   Updated: 2020/01/18 15:23:36 by bpajot      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "Missile.hpp"

Missile::Missile(unsigned int x, unsigned int y, std::string ownerType) : Entity()
{
	this->_type = "Missile";
	this->_c = "-";
	this->_isAlive = true;
	this->_x = x;
	this->_y= y;
	this->_ownerType = ownerType;
}

Missile::~Missile(void)
{
}

void	Missile::updatePos(void)
{
	if (this->_ownerType == "Player")
		this->_y =- 1.0 / 5;
	else
		this->_y =+ 1.0 / 3;
}