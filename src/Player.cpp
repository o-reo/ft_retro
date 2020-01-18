/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   Player.cpp                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: bpajot <bpajot@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/18 11:52:21 by bpajot       #+#   ##    ##    #+#       */
/*   Updated: 2020/01/18 12:48:02 by bpajot      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "Player.hpp"

Player::Player(unsigned int x, unsigned int y) :	Entity()
{
	this->_type = "Player";
	this->_c = 'o';
	this->_isAlive = true;
	this->_x = x;
	this->_y= y;
}

Player::~Player(void)
{
}