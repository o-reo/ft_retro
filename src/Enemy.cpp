/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   Enemy.cpp                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: bpajot <bpajot@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/18 11:55:21 by bpajot       #+#   ##    ##    #+#       */
/*   Updated: 2020/01/18 15:22:35 by bpajot      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "Enemy.hpp"

Enemy::Enemy(unsigned int x, unsigned int y)
{
	this->_type = "Enemy";
	this->_c =  "x";
	this->_isAlive = true;
	this->_x = x;
	this->_y= y;
}

Enemy::~Enemy(void)
{
}

void	Enemy::updatePos(void)
{
	this->_y = - 1.0 / 20;
}