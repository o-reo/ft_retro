#include "Game.hpp"

Game::Game() : entities(nullptr), end(false) {
  initscr();
  noecho();
  cbreak();
  clear();
  timeout(0);
  curs_set(0);
  this->player = (Player *)this->buildEntity("Player");
  Logger *log = Logger::get();
  log->out() << "Initializing window" << std::endl;
}

Game::~Game() {
  Game::EntityNode *node = this->entities;
  while (node) {
    node = this->destroyEntityNode(node);
  }
  endwin();
  Logger *log = Logger::get();
  log->out() << "Closing window" << std::endl;
}

void Game::checkCollisions() {
  Game::EntityNode *node = this->entities;
  while (node) {
    Game::EntityNode *check_node = this->entities;
    while (check_node) {
      if (check_node == node) {
        // node->entity->setDead();
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
  return pnode->next;
}

void Game::purgeEntities() {
  Game::EntityNode *node = this->entities;
  while (node) {
    if (!node->entity->getAlive()) {
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
    newNode->entity = new Missile(0, 0);
  } else if (type == "Enemy") {
    newNode->entity = new Enemy(0, 0);
  } else if (type == "Player") {
    newNode->entity = new Player(0, 0);
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
    mvaddch(node->entity->getY(), node->entity->getX(), node->entity->getC()[0]);
    node->entity->updatePos();
    node = node->next;
  }
}

void Game::catchEvents() {
  switch (getch()) {
  case 113:
    end = true;
    break;
  case 68:
    if (this->player->getX() > 0)
      this->player->setControl(Player::CONTROL_LEFT);
    break;
  case 67:
    if (this->player->getX() + 1 < (unsigned int)COLS)
      this->player->setControl(Player::CONTROL_RIGHT);
    break;
  case 65:
    if (this->player->getY() > 0)
      this->player->setControl(Player::CONTROL_UP);
    break;
  case 66:
    if (this->player->getY() + 1 < (unsigned int)LINES)
      this->player->setControl(Player::CONTROL_DOWN);
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
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
  }
}