#ifndef GAME_HPP
#define GAME_HPP

#include "Enemy.hpp"
#include "Entity.hpp"
#include "Logger.hpp"
#include "Missile.hpp"
#include "Player.hpp"
#include <ncurses.h>
#include <string>
#include <time.h>

class Game {

public:
  struct EntityNode {
    Entity *entity;
    EntityNode *next;
  };
  enum COLORS {
    COLOR_NONE,
    COLOR_ANGRY,
    COLOR_CALM,
    COLOR_CONSTIPATED
  };

  Game();
  ~Game();
  void loop();
  void checkCollisions();
  Entity *buildEntity(const std::string &type);
  void purgeEntities();
  void catchEvents();

protected:
  Game::EntityNode *entities;
  Player *player;
  bool end;

private:
  Game(Game const &src);
  Game &operator=(Game const &src);
  EntityNode *destroyEntityNode(EntityNode *);
  void update();
};

#endif