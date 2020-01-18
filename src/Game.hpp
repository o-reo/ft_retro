#ifndef GAME_HPP
#define GAME_HPP

#include "Entity.hpp"
#include "Logger.hpp"
#include <ncurses.h>
#include <string>

class Game {

public:
  struct EntityNode {
    Entity *entity;
    EntityNode *next;
  };

  Game();
  ~Game();
  void loop();
  void checkCollisions();
  Entity *buildEntity(const std::string &type);
  void purgeEntities();

protected:
  Game::EntityNode *entities;
  Entity *EntityTypes[10];

private:
  Game(Game const &src);
  Game &operator=(Game const &src);
  EntityNode *destroyEntityNode(EntityNode *);
};

#endif