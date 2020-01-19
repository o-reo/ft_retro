/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   Entity.hpp                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: bpajot <bpajot@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/18 11:12:54 by bpajot       #+#   ##    ##    #+#       */
/*   Updated: 2020/01/19 13:30:26 by bpajot      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef ENTITY_HPP
#define ENTITY_HPP

#include "ncurses.h"
#include <iostream>

class Entity {
protected:
  Entity(void);
  Entity(Entity const &src);
  Entity &operator=(Entity const &src);
  std::string _type;
  std::string _c;
  unsigned int _nbLive;
  float _x;
  float _y;
  float _dx;
  float _dy;
  unsigned int _color;

public:
  virtual ~Entity(void);

  virtual std::string getType(void) const;
  std::string getC(void) const;
  unsigned int getNbLive(void) const;
  int getX(void) const;
  int getY(void) const;
  float getdX(void) const;
  unsigned int getColor(void) const;
  void setNbLive(unsigned int nbLive);
  void updateNbLive(const int delta);
  void setX(int x);
  void setY(int y);
  void setColor(unsigned int color);
  virtual void updatePos(void) = 0;
  virtual bool hasImmunity(const Entity *entity) = 0;
};

#endif