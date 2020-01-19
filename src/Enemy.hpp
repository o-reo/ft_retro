/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   Enemy.hpp                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: bpajot <bpajot@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/18 11:54:30 by bpajot       #+#   ##    ##    #+#       */
/*   Updated: 2020/01/18 13:12:29 by bpajot      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef ENEMY_HPP
#define ENEMY_HPP

#include "Entity.hpp"
#include "Logger.hpp"
#include <iostream>

class Enemy : public Entity {
public:
  Enemy(unsigned int x, unsigned int y);
  virtual ~Enemy(void);

  virtual void updatePos(void);
  virtual bool hasImmunity(const Entity *entity);
};

#endif