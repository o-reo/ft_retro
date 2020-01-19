#ifndef ASTEROID_HPP
#define ASTEROID_HPP

#include "Entity.hpp"

class Asteroid : public Entity {
public:
  Asteroid(unsigned int x, unsigned int y);
  virtual ~Asteroid(void);

  virtual void updatePos(void);
  virtual bool hasImmunity(const Entity* entity);
};

#endif