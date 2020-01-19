#include "Game.hpp"

Game::Game()
    : score(0), topbar_size(2), mainwin_width(120), mainwin_height(20), entities(nullptr), player(nullptr), end(false) {
  initscr();
  noecho();
  cbreak();
  clear();
  timeout(0);
  curs_set(0);
  start_color();
  // Set cyan to be purpleish
  init_color(COLOR_CYAN, 600, 20, 500);
  init_color(COLOR_BLUE, 400, 400, 400);
  init_pair(Game::COLOR_MISSILES, COLOR_RED, COLOR_BLACK);
  init_pair(Game::COLOR_PLAYER, COLOR_YELLOW, COLOR_BLACK);
  init_pair(Game::COLOR_SCORE, COLOR_GREEN, COLOR_BLACK);
  init_pair(Game::COLOR_ALIEN, COLOR_CYAN, COLOR_BLACK);
  init_pair(Game::COLOR_BORDER, COLOR_BLUE, COLOR_BLACK);

  this->topbar = subwin(stdscr, this->topbar_size, this->mainwin_width, 0, 0);
  this->mainwin = subwin(stdscr, this->mainwin_height, this->mainwin_width, this->topbar_size, 0);

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
  this->score = 0;
  int i = -1;
  while (++i < 10) {
    log->out() << "Creation enemy " << i << std::endl;
    this->buildEntity("Enemy");
  }
  log->out() << "Initializing window" << std::endl;
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
  Game::EntityNode *node = this->entities;
  while (node) {
    if (node->entity->getX() >= this->mainwin_width || node->entity->getY() >= (this->mainwin_height) ||
        node->entity->getX() < 0 || node->entity->getY() < 0) {
      node->entity->setNbLive(0);
      node = node->next;
      continue;
    }
    Game::EntityNode *check_node = this->entities;
    while (check_node) {
      if (check_node != node && check_node->entity->getX() == node->entity->getX() &&
          check_node->entity->getY() == node->entity->getY()) {
        if (node->entity->getNbLive() != 0)
          node->entity->setNbLive(node->entity->getNbLive() - 1);
        if (check_node->entity->getType() == "Enemy" || node->entity->getType() == "Enemy")
          this->score++;
        if (node->entity->getType() == "Player" && node->entity->getNbLive() == 0)
          this->end = true;
        break;
      }
      check_node = check_node->next;
    }
    node = node->next;
  }
}

bool Game::checkEmpty(int x, int y) {
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
  if (type == "Missile") {
    newNode->entity = new Missile(this->mainwin_width / 5, this->mainwin_height / 2, "Player");
    newNode->entity->setColor(COLOR_MISSILES);
  } else if (type == "Enemy") {
    int x, y;
    bool empty = false;
    while (empty == false) {
      std::srand(std::clock());
      x = 1 + 3 * (this->mainwin_width - 2) / 4 + std::rand() % ((this->mainwin_width - 1) / 4);
      y = 1 + std::rand() % (this->mainwin_height - 2);
      empty = Game::checkEmpty(x, y);
    }
    newNode->entity = new Enemy(x, y);
    newNode->entity->setColor(COLOR_ALIEN);
  } else if (type == "Player") {
    newNode->entity = new Player(this->mainwin_width / 5, this->mainwin_height / 2);
    newNode->entity->setColor(COLOR_PLAYER);
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

void Game::update() {
  wattron(this->mainwin, COLOR_PAIR(COLOR_BORDER));
  box(this->mainwin, ACS_VLINE, ACS_HLINE);
  wattroff(this->mainwin, COLOR_PAIR(COLOR_BORDER));
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
    if (this->player->getX() > 1)
      this->player->setControl(Player::CONTROL_LEFT);
    break;
  case 67:
    if (this->player->getX() < this->mainwin_width - 2)
      this->player->setControl(Player::CONTROL_RIGHT);
    break;
  case 65:
    if (this->player->getY() > 1)
      this->player->setControl(Player::CONTROL_UP);
    break;
  case 66:
    if (this->player->getY() < (this->mainwin_height - 2))
      this->player->setControl(Player::CONTROL_DOWN);
    break;
  case 32:
    miss = this->buildEntity("Missile");
    miss->setX(this->player->getX() + 1);
    miss->setY(this->player->getY());
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
            this->score, this->player->getNbLive());
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
  while (!this->end) {
    this->displayScore();
    werase(this->mainwin);
    this->purgeEntities();
    this->catchEvents();
    this->update();
    this->checkCollisions();
    wrefresh(this->mainwin);
    std::clock_t tac, tic;
    tic = tac = std::clock();
    while (tac - tic < CLOCKS_PER_SEC / 100)
      tac = std::clock();
    std::srand(std::clock());
    int ratio = 1000 / (this->score + 1) + 10;
    if (std::rand() % ratio == 0)
      this->buildEntity("Enemy");
  }
  this->gameOver();
}