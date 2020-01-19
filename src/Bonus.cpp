/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   Bonus.cpp                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: bpajot <bpajot@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/18 11:55:21 by bpajot       #+#   ##    ##    #+#       */
/*   Updated: 2020/01/18 17:13:05 by bpajot      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "Bonus.hpp"

Bonus::Bonus(unsigned int x, unsigned int y) {
  this->_type = "Bonus";
  this->_c = "%";
  this->_nbLive = 1;
  this->_x = x;
  this->_y = y;
  this->_dx = -1.0 / 30;
  this->_dy = 0;
  this->effect = (Bonus::Effect)(std::rand() % (EFFECT_SIZE));
}

Bonus::~Bonus(void) {}

void Bonus::updatePos(void) {
  this->_x += this->_dx;
  this->_y += this->_dy;
}

void Bonus::applyBonus(Entity *entity) {
  switch (this->effect) {
  case EFFECT_HEALTH:
    entity->setNbLive(entity->getNbLive() + 1);
    break;
  case EFFECT_SCORE:
    if (entity->getType() == "Player")
      ((Player *)entity)->updateScore(100);
  default:
    break;
  }
}

bool Bonus::hasImmunity(const Entity *entity) {
  if (entity->getType() == "Missile Enemy")
    return true;
  return false;
}