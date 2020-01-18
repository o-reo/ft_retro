/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   Entity.cpp                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: bpajot <bpajot@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/18 11:20:04 by bpajot       #+#   ##    ##    #+#       */
/*   Updated: 2020/01/18 14:07:51 by bpajot      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "Entity.hpp"

Entity::Entity(void) : 	_type("Unknown"),
						_c(" "),
						_isAlive(true),
						_x(0),
						_y(0)
{
}

Entity::~Entity(void)
{
}

Entity::Entity(Entity const &src)
{
	*this = src;
}

Entity		&Entity::operator=(Entity const &src)
{
	this->_isAlive = src.getAlive();
	this->_x = src.getX();
	this->_y = src.getY();
	return *this;
}

std::string		Entity::getType(void) const
{
	return this->_type;
}

std::string		Entity::getC(void) const
{
	return this->_c;
}

bool			Entity::getAlive(void) const
{
	return this->_isAlive;
}

unsigned int	Entity::getX(void) const
{
	return this->_x;
}

unsigned int	Entity::getY(void) const
{
	return this->_y;
}

void		Entity::setDead(void)
{
	this->_isAlive = false;
}

void		Entity::setX(unsigned int x)
{
	this->_x = x;
}

void		Entity::setY(unsigned int y)
{
	this->_y = y;
}