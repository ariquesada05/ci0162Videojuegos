/**
 * @file TextComponent.hpp
 * @brief Text rendering component
 */

#ifndef TEXTCOMPONENT_HPP
#define TEXTCOMPONENT_HPP

#include <SDL2/SDL.h>
#include <string>

/**
 * @struct TextComponent
 * @brief Stores text and font information for rendering
 * 
 * Contains text content, font ID, color, and cached dimensions.
 */
struct TextComponent
{
  std::string text;   ///< The text content to render
  std::string fontID; ///< ID of the font to use
  SDL_Color color;    ///< Color of the text (RGBA)
  int width;          ///< Rendered width in pixels
  int height;         ///< Rendered height in pixels

  /**
   * @brief Construct a TextComponent
   * @param text The text content (default: " ")
   * @param fontID The font ID (default: " ")
   * @param r Red channel (0-255)
   * @param g Green channel (0-255)
   * @param b Blue channel (0-255)
   * @param a Alpha channel (0-255)
   */
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