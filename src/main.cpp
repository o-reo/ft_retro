#include "Game.hpp"

int main(void)
{
  Game game;
  game.loop();
  endwin();
  std::cout << "GAME OVER" << std::endl;
}