#include "Game.hpp"

Game::Game() : entities(nullptr), end(false) {
  initscr();
  noecho();
  cbreak();
  clear();
  timeout(0);
  curs_set(0);
  start_color();
  init_pair(Game::COLOR_ANGRY, COLOR_RED, COLOR_BLACK);
  init_pair(Game::COLOR_CONSTIPATED, COLOR_YELLOW, COLOR_BLACK);
  init_pair(Game::COLOR_CALM, COLOR_GREEN, COLOR_BLACK);

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
    Game::EntityNode *check_node = this->entities;
    if (node->entity->getX() >= COLS || node->entity->getY() >= LINES
      || node->entity->getX() < 0 || node->entity->getY() < 0) {
      node->entity->setNbLive(0);
      node = node->next;
      continue;
    }
    while (check_node) {
      if (check_node != node && check_node->entity->getX() == node->entity->getX() &&
          check_node->entity->getY() == node->entity->getY()) {
        node->entity->setNbLive(node->entity->getNbLive() - 1);
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
    if (!node->entity->getNbLive() && node->entity->getType() != "Player") {
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
    newNode->entity = new Missile(COLS / 5, LINES / 2, "Player");
    newNode->entity->setColor(COLOR_ANGRY);
  } else if (type == "Enemy") {
    newNode->entity = new Enemy(3 * COLS / 4 + rand() % (COLS / 4), rand() % LINES);
  } else if (type == "Player") {
    newNode->entity = new Player(COLS / 5, LINES / 2);
    newNode->entity->setColor(COLOR_CONSTIPATED);
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
    attron(COLOR_PAIR(node->entity->getColor()));
    mvaddch(node->entity->getY(), node->entity->getX(), node->entity->getC()[0]);
    attroff(COLOR_PAIR(node->entity->getColor()));
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
    if (this->player->getY() < LINES - 1)
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

void Game::loop() {
  // Logger *log = Logger::get();
  while (!this->end) {
    erase();
    this->purgeEntities();
    // log->out() << getch() << std::endl;
    this->catchEvents();
    this->update();
    this->checkCollisions();
    refresh();
    clock_t   tac,tic; 
    tic = tac = clock();
    while (tac - tic < CLOCKS_PER_SEC / 100)
      tac = clock();
  }
}