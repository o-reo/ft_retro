/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   Missile.cpp                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: bpajot <bpajot@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/18 12:54:19 by bpajot       #+#   ##    ##    #+#       */
/*   Updated: 2020/01/19 13:02:35 by bpajot      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "Missile.hpp"

Missile::Missile(unsigned int x, unsigned int y, std::string ownerType) : Entity() {
  this->_type = "Missile";
  this->_c = "-";
  this->_nbLive = 1;
  this->_x = x;
  this->_y = y;
  this->_ownerType = ownerType;
  if (this->_ownerType == "Player")
    this->_dx = 1.0 / 5;
  else
    this->_dx = -1.0 / 3;
  this->_dy = 0;
}

Missile::~Missile(void) {}

std::string Missile::getType(void) const {
  if (this->_ownerType == "Player")
    return ("Missile Player");
  else
    return ("Missile Enemy");
}

void Missile::updatePos(void) {
  this->_x += this->_dx;
  this->_y += this->_dy;
}

bool Missile::hasImmunity(const Entity *entity) {
  if (entity->getType() == "Boss" && this->_dx < 0.0f)
    return true;
	if (entity->getType() == "Enemy" && this->_ownerType == "Enemy")
		return true;
	if (entity->getType() == this->getType())
		return true;
  return false;
}