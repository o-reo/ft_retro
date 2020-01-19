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
  this->_c = "#";
  this->_nbLive = 1;
  this->_x = x;
  this->_y = y;
  this->_dx = -1.0 / 20;
  this->_dy = 0;
}

Bonus::~Bonus(void) {}

void Bonus::updatePos(void) {
  this->_x += this->_dx;
  this->_y += this->_dy;
}