/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   Missile.cpp                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: bpajot <bpajot@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/18 12:54:19 by bpajot       #+#   ##    ##    #+#       */
/*   Updated: 2020/01/18 17:22:20 by bpajot      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "Missile.hpp"

Missile::Missile(unsigned int x, unsigned int y, std::string ownerType) : Entity()
{
	this->_type = "Missile";
	this->_c = "-";
	this->_nbLive = 1;
	this->_x = x;
	this->_y= y;
	this->_ownerType = ownerType;
	if (this->_ownerType == "Player")
		this->_dx = 1.0 / 5;
	else
		this->_dx = -1.0 / 3;
	this->_dy = 0 ;
}

Missile::~Missile(void)
{
}

void	Missile::updatePos(void)
{
	this->_x += this->_dx;
	this->_y += this->_dy;
}