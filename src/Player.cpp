/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   Player.cpp                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: bpajot <bpajot@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/18 11:52:21 by bpajot       #+#   ##    ##    #+#       */
/*   Updated: 2020/01/18 18:14:37 by bpajot      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "Player.hpp"

Player::Player(unsigned int x, unsigned int y) : Entity(), control(CONTROL_NONE), score(0) {
  this->_type = "Player";
  this->_c = ">";
  this->_nbLive = 3;
  this->_x = x;
  this->_y = y;
  this->last_shoot = std::clock();
}

Player::~Player(void) {}

void Player::setControl(Player::CONTROL ctrl) { this->control = ctrl; }

void Player::updatePos(void) {
  switch (this->control) {
  case CONTROL_LEFT:
    this->_x -= 1;
    break;
  case CONTROL_RIGHT:
    this->_x += 1;
    break;
  case CONTROL_UP:
    this->_y -= 1;
    break;
  case CONTROL_DOWN:
    this->_y += 1;
    break;
  default:
    break;
  }
  this->control = CONTROL_NONE;
}

int Player::getScore() const { return this->score; }

void Player::updateScore(const int delta) {
  if (delta > 0 || this->score >= -delta)
    this->score += delta;
  else
    this->score = 0;
}

bool Player::hasImmunity(const Entity *entity) {
  if (entity->getType() == "Missile Player")
    return true;
  if (entity->getType() == "Bonus")
    return true;
  return false;
}

bool Player::shoot()
{
  std::clock_t current = std::clock();
  if ((current - this->last_shoot) < CLOCKS_PER_SEC / 10)
    return false;
  this->last_shoot = current;
  return true;
}