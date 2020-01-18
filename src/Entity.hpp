/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   Entity.hpp                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: bpajot <bpajot@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/18 11:12:54 by bpajot       #+#   ##    ##    #+#       */
/*   Updated: 2020/01/18 15:17:00 by bpajot      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <iostream>

class Entity {
protected:
  Entity(void);
  Entity(Entity const &src);
  Entity &operator=(Entity const &src);
  std::string _type;
  std::string _c;
  bool _isAlive;
  float _x;
  float _y;
  unsigned int _color;

public:
  virtual ~Entity(void);

  std::string getType(void) const;
  std::string getC(void) const;
  bool getAlive(void) const;
  unsigned int getX(void) const;
  unsigned int getY(void) const;
  void setDead(void);
  void setColor(unsigned int x);
  unsigned int getColor() const;
  void setX(unsigned int x);
  void setY(unsigned int y);
  virtual void updatePos(void) = 0;
};

#endif