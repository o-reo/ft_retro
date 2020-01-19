#ifndef GAME_HPP
#define GAME_HPP

#include "Asteroid.hpp"
#include "Bonus.hpp"
#include "Enemy.hpp"
#include "Entity.hpp"
#include "Logger.hpp"
#include "Missile.hpp"
#include "Player.hpp"
#include "Bonus.hpp"
#include "Boss.hpp"
#include <cmath>
#include <ctime>
#include <ncurses.h>
#include <string>

class Game {

public:
  struct EntityNode {
    Entity *entity;
    EntityNode *next;
  };
  enum COLORS {
    COLOR_NONE,
    COLOR_MISSILES_PLAYER,
    COLOR_MISSILES_ENEMY,
    COLOR_PLAYER,
    COLOR_ALIEN,
    COLOR_SCORE,
    COLOR_ASTEROID,
    COLOR_BORDER,
    COLOR_BONUS
  };

  Game();
  ~Game();
  void loop();

private:
  Game(Game const &src);
  Game &operator=(Game const &src);
  EntityNode *destroyEntityNode(EntityNode *);
  void displayScore();
  void update();
  void initialize();
  void gameOver();
  void checkCollisions();
  Entity *buildEntity(const std::string &type);
  void purgeEntities();
  bool checkEmpty(const int, const int);
  void catchEvents();
  void generateEvents();
  int generateRandom(const int, const int);

  WINDOW *topbar;
  WINDOW *mainwin;
  const int topbar_size;
  const int mainwin_width;
  const int mainwin_height;
  std::clock_t start_time;
  Game::EntityNode *entities;
  Player *player;
  bool boss_active;
  bool end;
};

#endif