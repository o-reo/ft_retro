/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   Player.cpp                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: bpajot <bpajot@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/18 11:52:21 by bpajot       #+#   ##    ##    #+#       */
/*   Updated: 2020/01/18 17:20:16 by bpajot      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "Player.hpp"

Player::Player(unsigned int x, unsigned int y) : Entity(), control(CONTROL_NONE) {
  this->_type = "Player";
  this->_c = "o";
  this->_nbLive = 3;
  this->_x = x;
  this->_y = y;
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