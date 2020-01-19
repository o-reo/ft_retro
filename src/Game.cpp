#include "Game.hpp"

Game::Game()
    : topbar_size(2), mainwin_width(120), mainwin_height(20), entities(nullptr), player(nullptr), boss_active(false),
      end(false) {
  initscr();
  noecho();
  cbreak();
  clear();
  timeout(0);
  curs_set(0);
  start_color();

  std::srand(std::clock());

  // Set cyan to be purpleish
  init_color(COLOR_CYAN, 600, 20, 500);
  init_color(COLOR_BLUE, 400, 400, 400);
  init_pair(Game::COLOR_MISSILES_PLAYER, COLOR_RED, COLOR_BLACK);
  init_pair(Game::COLOR_MISSILES_ENEMY, COLOR_MAGENTA, COLOR_BLACK);
  init_pair(Game::COLOR_PLAYER, COLOR_YELLOW, COLOR_BLACK);
  init_pair(Game::COLOR_SCORE, COLOR_GREEN, COLOR_BLACK);
  init_pair(Game::COLOR_ALIEN, COLOR_CYAN, COLOR_BLACK);
  init_pair(Game::COLOR_BORDER, COLOR_BLUE, COLOR_BLACK);
  init_pair(Game::COLOR_ASTEROID, COLOR_BLUE, COLOR_BLACK);
  init_pair(Game::COLOR_BONUS, COLOR_GREEN, COLOR_BLACK);

  this->topbar = subwin(stdscr, this->topbar_size, this->mainwin_width, 0, 0);

  // DRAW BORDERS
  WINDOW *border = subwin(stdscr, this->mainwin_height + 3, this->mainwin_width + 3, this->topbar_size, 0);
  wattron(border, COLOR_PAIR(COLOR_BORDER));
  box(border, ACS_VLINE, ACS_HLINE);
  wattroff(this->mainwin, COLOR_PAIR(COLOR_BORDER));

  this->mainwin = subwin(stdscr, this->mainwin_height + 1, this->mainwin_width + 1, this->topbar_size + 1, 1);

  this->initialize();
}

void Game::initialize() {
  Logger *log = Logger::get();
  log->out() << "Initializing window" << std::endl;
  Game::EntityNode *ents = this->entities;
  while (ents) {
    this->destroyEntityNode(ents);
    ents = ents->next;
  }
  this->start_time = std::clock();
  this->entities = nullptr;
  this->player = (Player *)this->buildEntity("Player");
  int i = -1;
  while (++i < 10) {
    log->out() << "Creation enemy " << i << std::endl;
    this->buildEntity("Enemy");
  }
  log->out() << "Initializing window" << std::endl;
  if (LINES < (this->mainwin_height + 10) || COLS < (this->mainwin_width + 10)) {
    this->end = true;
    mvprintw(LINES / 2, COLS / 2 - 15, "Terminal window is too small");
    refresh();
    for (unsigned long i = 1999999999; i > 0; i--)
      ;
    return;
  }
  this->end = false;
}

Game::~Game() {
  Logger *log = Logger::get();
  Game::EntityNode *node = this->entities;
  while (node) {
    this->destroyEntityNode(node);
    node = node->next;
  }
  init_color(COLOR_BLUE, 0, 0, 1000);
  endwin();
  log->out() << "Closing window" << std::endl;
  delete log;
  this->end = true;
}

void Game::checkCollisions() {
  // Logger *log = Logger::get();
  bool has_boss = false;
  Game::EntityNode *node = this->entities;
  while (node) {
    if (node->entity->getType() == "Boss")
      has_boss = true;
    if (node->entity->getX() > this->mainwin_width || node->entity->getY() > this->mainwin_height ||
        node->entity->getX() < 0 || node->entity->getY() < 0) {
      node->entity->setNbLive(0);
      if (node->entity->getType() == "Enemy")
        this->player->updateScore(-1);
      node = node->next;
      continue;
    }
    Game::EntityNode *check_node = this->entities;
    while (check_node) {
      if (check_node != node && check_node->entity->getX() == node->entity->getX() &&
          check_node->entity->getY() == node->entity->getY()) {
        if (!node->entity->hasImmunity(check_node->entity)) {
          node->entity->updateNbLive(-1);
          if (node->entity->getNbLive() > 0)
            node->entity->setNbLive(node->entity->getNbLive() - 1);
        }
        if (node->entity->getType() == "Player" && check_node->entity->getType() == "Bonus")
          ((Bonus *)(check_node->entity))->applyBonus(node->entity);
        if (node->entity->getType() == "Missile Player" && check_node->entity->getType() == "Enemy")
          this->player->updateScore(1);
        break;
      }
      check_node = check_node->next;
    }
    if (node->entity->getType() == "Boss" && node->entity->getNbLive() == 0) {
      Game::EntityNode *check_boss = this->entities;
      while (check_boss) {
        if (check_boss != node && check_boss->entity->getType() == "Boss")
          check_boss->entity->updateNbLive(-1 * this->generateRandom(0, 1));
        check_boss = check_boss->next;
      }
    }
    node = node->next;
  }
  if (this->boss_active && !has_boss)
    this->player->updateScore(500);
  this->boss_active = has_boss;
}

bool Game::checkEmpty(const int x, const int y) {
  Game::EntityNode *node = this->entities;
  while (node) {
    if (node->entity->getX() == x && node->entity->getY() == y) {
      return false;
    }
    node = node->next;
  }
  return true;
}

Game::EntityNode *Game::destroyEntityNode(EntityNode *node) {
  Game::EntityNode *pnode = this->entities;
  if (node == this->entities)
    this->entities = node->next;
  while (pnode && pnode->next) {
    if (pnode->next == node) {
      pnode->next = node->next;
    }
    pnode = pnode->next;
  }
  delete node->entity;
  delete node;
  return pnode ? pnode->next : nullptr;
}

void Game::purgeEntities() {
  Game::EntityNode *node = this->entities;
  while (node) {
    if (node->entity->getNbLive() <= 0 && node->entity->getType() != "Player") {
      node = this->destroyEntityNode(node);
    } else {
      node = node->next;
    }
  }
}

Entity *Game::buildEntity(const std::string &type) {
  Game::EntityNode *node = this->entities;
  Game::EntityNode *newNode = new Game::EntityNode;
  newNode->next = nullptr;
  if (type == "Bonus") {
    // Random Bonus position
    int y;
    bool empty = false;
    while (empty == false) {
      y = this->generateRandom(0, this->mainwin_height);
      empty = Game::checkEmpty(0, y);
    }
    newNode->entity = new Bonus(this->mainwin_width / 2, y);
    newNode->entity->setColor(COLOR_BONUS);
  } else if (type == "Missile Player") {
    newNode->entity = new Missile(this->mainwin_width, this->mainwin_height / 2, "Player");
    newNode->entity->setColor(COLOR_MISSILES_PLAYER);
  } else if (type == "Missile Enemy") {
    newNode->entity = new Missile(this->mainwin_width, this->mainwin_height / 2, "Enemy");
    newNode->entity->setColor(COLOR_MISSILES_ENEMY);
  } else if (type == "Asteroid") {
    // Random Asteroid position
    int y;
    bool empty = false;
    while (empty == false) {
      y = this->generateRandom(0, this->mainwin_height);
      empty = Game::checkEmpty(0, y);
    }
    newNode->entity = new Asteroid(this->mainwin_width, y);
    newNode->entity->setColor(COLOR_ASTEROID);
  } else if (type == "Enemy") {
    // Random enemy position
    int x, y;
    bool empty = false;
    while (empty == false) {
      x = 3 * this->mainwin_width / 4 + this->generateRandom(0, this->mainwin_width / 4);
      y = this->generateRandom(0, this->mainwin_height);
      empty = Game::checkEmpty(x, y);
    }
    newNode->entity = new Enemy(x, y);
    newNode->entity->setColor(COLOR_ALIEN);
  } else if (type == "Player") {
    newNode->entity = new Player(this->mainwin_width / 5, this->mainwin_height / 2);
    newNode->entity->setColor(COLOR_PLAYER);
  } else if (type == "Boss") {
    newNode->entity = new Boss(4 * this->mainwin_width / 5, this->mainwin_height / 2);
    newNode->entity->setColor(COLOR_ALIEN);
  }
  if (!node) {
    this->entities = newNode;
    return newNode->entity;
  }
  while (node->next)
    node = node->next;
  node->next = newNode;
  return newNode->entity;
}

int Game::generateRandom(const int low, const int up) { return (low + std::rand() % (1 + up)); }

void Game::generateEvents() {
  // Generate Bonus
  if (this->generateRandom(0, 500) == 0) {
    this->buildEntity("Bonus");
  }
  // Generate Asteroids
  if (this->generateRandom(0, 300) == 0) {
    this->buildEntity("Asteroid");
  }
  // Generate Enemies
  int ratio = 1500 / (this->player->getScore() + 1) + 10;
  if (this->generateRandom(0, ratio) == 0) {
    Enemy *en = (Enemy *)this->buildEntity("Enemy");
    Missile *miss = (Missile *)this->buildEntity("Missile Enemy");
    miss->setX(en->getX() - 1);
    miss->setY(en->getY());
  }
  std::clock_t current_time = (std::clock() - this->start_time) / CLOCKS_PER_SEC;
  if (!this->boss_active && current_time != 0 && current_time % 60 == 0) {
    this->boss_active = true;
    for (int i = 0; i <= 12; i++) {
      int begin;
      int end;
      if (i < 4) {
        begin = -2;
        end = +2;
      } else if (i < 8) {
        begin = -6;
        end = +6;
      } else {
        begin = -10;
        end = +10;
      }
      for (int j = begin; j <= end; j++) {
        Boss *bs = (Boss *)this->buildEntity("Boss");
        bs->setX(4 * this->mainwin_width / 5 + i);
        bs->setY(this->mainwin_height / 2 + j);
        if (i == 0 || i == 4 || i == 8) {
          Missile *miss = (Missile *)this->buildEntity("Missile Enemy");
          miss->setX(bs->getX() - 1);
          miss->setY(bs->getY());
        }
      }
    }
  }
}

void Game::update() {
  Game::EntityNode *node = this->entities;
  while (node) {
    // Move cursor and print the asset
    wattron(this->mainwin, COLOR_PAIR(node->entity->getColor()));
    mvwaddch(this->mainwin, node->entity->getY(), node->entity->getX(), node->entity->getC()[0]);
    wattroff(this->mainwin, COLOR_PAIR(node->entity->getColor()));
    node->entity->updatePos();
    node = node->next;
  }
}

void Game::catchEvents() {
  Entity *miss = nullptr;
  switch (getch()) {
  case 113:
    end = true;
    break;
  case 68:
    if (this->player->getX() > 0)
      this->player->setControl(Player::CONTROL_LEFT);
    break;
  case 67:
    if (this->player->getX() < this->mainwin_width)
      this->player->setControl(Player::CONTROL_RIGHT);
    break;
  case 65:
    if (this->player->getY() > 0)
      this->player->setControl(Player::CONTROL_UP);
    break;
  case 66:
    if (this->player->getY() < this->mainwin_height)
      this->player->setControl(Player::CONTROL_DOWN);
    break;
  case 32:
    if (this->player->shoot()) {
      miss = this->buildEntity("Missile Player");
      miss->setX(this->player->getX() + 1);
      miss->setY(this->player->getY());
    }
    break;
  default:
    break;
  }
}

void Game::displayScore() {
  werase(this->topbar);
  wattron(this->topbar, A_BOLD);
  wattron(this->topbar, COLOR_PAIR(COLOR_SCORE));
  mvwprintw(this->topbar, 1, 1, "Time: %4i  Score: %4i  Lives: %4u", (std::clock() - this->start_time) / CLOCKS_PER_SEC,
            this->player->getScore(), this->player->getNbLive());
  wattroff(this->topbar, COLOR_PAIR(COLOR_SCORE));
  wattroff(this->topbar, A_BOLD);
  wrefresh(this->topbar);
}

void Game::gameOver() {
  // Logger *log = Logger::get();
  timeout(-1);
  werase(this->mainwin);
  mvwprintw(this->mainwin, this->mainwin_height / 2, this->mainwin_width / 2, "GAME OVER");
  wrefresh(this->mainwin);
  int c;
  while ((c = getch()) != 113) {
    timeout(0);
    if (c == 10) {
      this->initialize();
      this->loop();
      break;
    }
  }
}

void Game::loop() {
  std::clock_t tic, tac;
  while (!this->end) {
    tic = std::clock();
    werase(this->mainwin);
    this->purgeEntities();
    this->catchEvents();
    this->checkCollisions();
    this->generateEvents();
    this->displayScore();
    this->update();
    wrefresh(this->mainwin);
    if (this->player->getNbLive() <= 0)
      break;
    tac = std::clock();
    while (tac - tic < CLOCKS_PER_SEC / 100)
      tac = std::clock();
  }
  this->gameOver();
}