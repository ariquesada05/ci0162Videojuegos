#ifndef SPRITE_COMPONENT_HPP
#define SPRITE_COMPONENT_HPP

#include <SDL2/SDL.h>
#include <string>

class SpriteComponent
{
public:
  std::string textureID;
  int width;
  int height;
  SDL_Rect srcRect;
  bool flip = false;

  SpriteComponent(const std::string &textureID = "none", int width = 0, int height = 0, int srcRectX = 0, int srcRectY = 0)
  {
    this->textureID = textureID;
    this->width = width;
    this->height = height;
    this->srcRect = {srcRectX, srcRectY, width, height};
  }

  ~SpriteComponent()
  {
  }
};

#endif // SPRITE_COMPONENT_HPP