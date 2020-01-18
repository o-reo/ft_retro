#ifndef GAME_HPP
#define GAME_HPP

#include "Enemy.hpp"
#include "Entity.hpp"
#include "Logger.hpp"
#include "Missile.hpp"
#include "Player.hpp"
#include <chrono>
#include <ncurses.h>
#include <string>
#include <thread>

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