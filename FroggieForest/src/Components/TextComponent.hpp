#ifndef TEXTCOMPONENT_HPP
#define TEXTCOMPONENT_HPP

#include <SDL2/SDL.h>
#include <string>

struct TextComponent
{
  std::string text;
  std::string fontID;
  SDL_Color color;
  int width;
  int height;

  TextComponent(
      const std::string &text = " ",
      const std::string &fontID = " ",
      u_char r = 0, u_char g = 0, u_char b = 0, u_char a = 0)
  {
    this->text = text;
    this->fontID = fontID;
    this->color.a = a;
    this->color.r = r;
    this->color.g = g;
    this->color.b = b;
    this->width = 0;
    this->height = 0;
  }
};

#endif // TEXTCOMPONENT_HPP