/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   Boss.cpp                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: bpajot <bpajot@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/19 14:41:33 by bpajot       #+#   ##    ##    #+#       */
/*   Updated: 2020/01/19 18:25:10 by bpajot      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "Boss.hpp"
#include <cmath>

Boss::Boss(unsigned int x, unsigned int y) : Entity() {
  this->_type = "Boss";
  this->_c = "#";
  this->_nbLive = 20;
  this->_x = x;
  this->_y = y;
  this->_base_y = y;
  this->_dx = -1.0 / 200;
  this->_dy = 0;
}

Boss::~Boss(void) {}

void Boss::updatePos(void) {
  this->_x += this->_dx;
  this->_x += this->_dx;
  // this->_dy += 1;
  // this->_y = this->_base_y + 5 * cos(this->_dy);
}

bool Boss::hasImmunity(const Entity *entity) {
	std::string type = entity->getType();
	if (type != "Missile Player")
		return true;
	return false;
}