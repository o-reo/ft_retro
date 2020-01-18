#include "Game.hpp"

Game::Game() : entities(nullptr) {
  initscr();
  noecho();
  Logger *log = Logger::get();
  log->out() << "Initializing window" << std::endl;
}

Game::~Game() {
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
  newNode->entity = new Entity("");
  if (!node) {
    this->entities = newNode;
  }
  while (node->next)
    node = node->next;
  return newNode->entity;
}

void Game::loop() {
  // Logger *log = Logger::get();
  while (true) {
    this->purgeEntities();
    Game::EntityNode *node = this->entities;
    switch (getch()) {
    case 27:
      return;
    default:
      break;
    }
    while (node) {
      // Move cursor and print the asset
      // printw()
      node = node->next;
    }
    this->checkCollisions();
    refresh();
  }
}