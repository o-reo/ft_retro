#include "Asteroid.hpp"

Asteroid::Asteroid(unsigned int x, unsigned int y) {
  this->_type = "Asteroid";
  this->_c = "*";
  this->_nbLive = 10;
  this->_x = x;
  this->_y = y;
	this->_dx = -1.0 / 30;
  this->_dy = 0;
}

Asteroid::~Asteroid(void) {}

void Asteroid::updatePos(void) {
  this->_x += this->_dx;
  this->_y += this->_dy;
}

bool Asteroid::hasImmunity(const Entity *entity)
{
  (void)entity;
  return false;
}