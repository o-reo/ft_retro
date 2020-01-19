/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   Bonus.hpp                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: bpajot <bpajot@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/18 11:54:30 by bpajot       #+#   ##    ##    #+#       */
/*   Updated: 2020/01/18 13:12:29 by bpajot      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef BONUS_HPP
#define BONUS_HPP

#include "Entity.hpp"
#include "Player.hpp"
#include <ctime>
#include <iostream>

class Bonus : public Entity {
public:
  enum Effect { EFFECT_HEALTH, EFFECT_SCORE, EFFECT_SIZE };
  Bonus(unsigned int x, unsigned int y);
  virtual ~Bonus(void);
  void applyBonus(Entity *entity);

  virtual void updatePos(void);
  virtual bool hasImmunity(const Entity* entity);

private:
  Effect effect;
};

#endif