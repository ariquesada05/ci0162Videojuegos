#include <glm/glm.hpp>
#include <SDL2/SDL.h>
#include <sol/sol.hpp>

#include <iostream>
#include "Game/Game.hpp"

int main(int argc, char *argv[])
{
  (void)argc;
  (void)argv;

  std::cout << "Game Engine 2D" << std::endl;

  Game &game = Game::GetInstance();
  game.init();
  game.run();
  game.destroy();

  return 0;
}