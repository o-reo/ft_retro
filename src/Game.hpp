#ifndef GAME_HPP
#define GAME_HPP

#include "Enemy.hpp"
#include "Entity.hpp"
#include "Logger.hpp"
#include "Missile.hpp"
#include "Player.hpp"
#include <ctime>
#include <ncurses.h>
#include <string>

class Game {

public:
  struct EntityNode {
    Entity *entity;
    EntityNode *next;
  };
  enum COLORS { COLOR_NONE, COLOR_MISSILES, COLOR_PLAYER, COLOR_ALIEN, COLOR_SCORE, COLOR_BORDER };

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
  void catchEvents();

  WINDOW *topbar;
  WINDOW *mainwin;
  int score;
  const int topbar_size;
  const int mainwin_width;
  const int mainwin_height;
  std::clock_t start_time;
  Game::EntityNode *entities;
  Player *player;
  bool end;
};

#endif