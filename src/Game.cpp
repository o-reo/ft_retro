#include "Game.hpp"

Game::Game() : entities(nullptr), end(false), score(0), scorebar(3), start_time(std::clock()) {
  initscr();
  noecho();
  cbreak();
  clear();
  timeout(0);
  curs_set(0);
  start_color();
  // Set cyan to be purpleish
  init_color(COLOR_CYAN, 600, 20, 500);
  init_pair(Game::COLOR_MISSILES, COLOR_RED, COLOR_BLACK);
  init_pair(Game::COLOR_PLAYER, COLOR_YELLOW, COLOR_BLACK);
  init_pair(Game::COLOR_SCORE, COLOR_GREEN, COLOR_BLACK);
  init_pair(Game::COLOR_ALIEN, COLOR_CYAN, COLOR_BLACK);

  this->topbar = subwin(stdscr, this->scorebar, COLS, 0, 0);
  this->mainwin = subwin(stdscr, LINES - this->scorebar, COLS, this->scorebar, 0);

  this->player = (Player *)this->buildEntity("Player");
  int i = -1;
  while (++i < 100)
    this->buildEntity("Enemy");
  Logger *log = Logger::get();
  log->out() << "Initializing window" << std::endl;
}

Game::~Game() {
  Logger *log = Logger::get();
  Game::EntityNode *node = this->entities;
  while (node) {
    this->destroyEntityNode(node);
    node = node->next;
  }
  endwin();
  log->out() << "Closing window" << std::endl;
  delete log;
  this->end = true;
}

void Game::checkCollisions() {
  Game::EntityNode *node = this->entities;
  while (node) {
    if (node->entity->getX() >= COLS || node->entity->getY() >= (LINES - this->scorebar) || node->entity->getX() < 0 ||
        node->entity->getY() < 0) {
      node->entity->setNbLive(0);
      node = node->next;
      continue;
    }
    Game::EntityNode *check_node = this->entities;
    while (check_node) {
      if (check_node != node && check_node->entity->getX() == node->entity->getX() &&
          check_node->entity->getY() == node->entity->getY()) {
        node->entity->setNbLive(std::max(node->entity->getNbLive(), 1u) - 1);
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
    newNode->entity = new Missile(COLS / 5, (LINES - this->scorebar) / 2, "Player");
    newNode->entity->setColor(COLOR_MISSILES);
  } else if (type == "Enemy") {
    newNode->entity = new Enemy(3 * COLS / 4 + rand() % (COLS / 4), rand() % (LINES - this->scorebar));
    newNode->entity->setColor(COLOR_ALIEN);
  } else if (type == "Player") {
    newNode->entity = new Player(COLS / 5, (LINES - this->scorebar) / 2);
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
    if (this->player->getX() < COLS - 1)
      this->player->setControl(Player::CONTROL_RIGHT);
    break;
  case 65:
    if (this->player->getY() > 0)
      this->player->setControl(Player::CONTROL_UP);
    break;
  case 66:
    if (this->player->getY() < (LINES - this->scorebar - 1))
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
  }
}