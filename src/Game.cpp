#include "Game.hpp"

Game::Game() : entities(nullptr) {
  initscr();
  noecho();
  cbreak();
  clear();
  timeout(0);
  curs_set(0);
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
      if (check_node->entity->getX() == node->entity->getX()
        && check_node->entity->getY() == node->entity->getY()) {
        node->entity->setDead();
        break;
      }
      check_node = check_node->next;
    }
    Logger *log = Logger::get();
    log->out() << "checking collision on: " << node->entity->getType() << std::endl;
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
    newNode->entity = new Missile(LINES / 2, COLS / 3, "Player");
  } else if (type == "Enemy") {
    newNode->entity = new Enemy(rand() % LINES, 3 * COLS / 4);
  } else if (type == "Player") {
    newNode->entity = new Player(LINES / 2, COLS / 3);
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

void Game::loop() {
  // Logger *log = Logger::get();
  while (true) {
    erase();
    this->purgeEntities();
    // log->out() << getch() << std::endl;
    switch (getch()) {
    case 113:
      return;
    case 27:
      this->entities->entity->setDead();
    default:
      break;
    }
    Game::EntityNode *node = this->entities;
    while (node) {
      // Move cursor and print the asset
      mvaddch(node->entity->getY(), node->entity->getX(), node->entity->getC()[0]);
      node = node->next;
    }
    this->checkCollisions();
    refresh();
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
  }
}