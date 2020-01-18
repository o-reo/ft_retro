/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   Entity.cpp                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: bpajot <bpajot@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/18 11:20:04 by bpajot       #+#   ##    ##    #+#       */
/*   Updated: 2020/01/18 18:30:19 by bpajot      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "Entity.hpp"

Entity::Entity(void) : _type("Unknown"), _c(" "), _nbLive(1), _x(0), _y(0), _dx(0), _dy(0) {}

Entity::~Entity(void) {}

Entity::Entity(Entity const &src) { *this = src; }

Entity &Entity::operator=(Entity const &src) {
  this->_type = src.getType();
  this->_c = src.getC();
  this->_nbLive = src.getNbLive();
  this->_x = src.getX();
  this->_y = src.getY();
  return *this;
}

std::string Entity::getType(void) const { return this->_type; }

std::string Entity::getC(void) const { return this->_c; }

unsigned int Entity::getNbLive(void) const { return this->_nbLive; }

int Entity::getX(void) const { return this->_x; }

int Entity::getY(void) const { return this->_y; }

void Entity::setNbLive(unsigned int nbLive) { this->_nbLive = nbLive; }

void Entity::setX(int x) { this->_x = x; }

void Entity::setY(int y) { this->_y = y; }
