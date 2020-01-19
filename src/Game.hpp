#ifndef GAME_HPP
#define GAME_HPP

#include "Enemy.hpp"
#include "Entity.hpp"
#include "Logger.hpp"
#include "Missile.hpp"
#include "Player.hpp"
#include <ncurses.h>
#include <string>
#include <ctime>

class Game {

public:
  struct EntityNode {
    Entity *entity;
    EntityNode *next;
  };
  enum COLORS { COLOR_NONE, COLOR_MISSILES, COLOR_PLAYER, COLOR_ALIEN, COLOR_SCORE };

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
  void displayScore();
  void update();
  WINDOW *topbar;
  WINDOW *mainwin;
  int score;
  const int scorebar;
  const std::clock_t start_time;
};

#endif