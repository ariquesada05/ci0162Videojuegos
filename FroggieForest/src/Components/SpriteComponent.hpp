/**
 * @file SpriteComponent.hpp
 * @brief Sprite rendering component
 */

#ifndef SPRITE_COMPONENT_HPP
#define SPRITE_COMPONENT_HPP

#include <SDL2/SDL.h>
#include <string>

/**
 * @class SpriteComponent
 * @brief Stores sprite rendering information
 * 
 * Contains the texture ID, dimensions, and source rectangle for rendering
 * a sprite from a texture atlas.
 */
class SpriteComponent
{
public:
  std::string textureID; ///< ID of the texture to render
  int width;             ///< Width of the sprite frame in pixels
  int height;            ///< Height of the sprite frame in pixels
  SDL_Rect srcRect;      ///< Source rectangle in the texture
  bool flip = false;     ///< Whether to flip the sprite horizontally

  /**
   * @brief Construct a SpriteComponent
   * @param textureID The texture ID (default: "none")
   * @param width The sprite width (default: 0)
   * @param height The sprite height (default: 0)
   * @param srcRectX The X position in the texture (default: 0)
   * @param srcRectY The Y position in the texture (default: 0)
   */
  SpriteComponent(const std::string &textureID = "none", int width = 0, int height = 0, int srcRectX = 0, int srcRectY = 0)
  {
    this->textureID = textureID;
    this->width = width;
    this->height = height;
    this->srcRect = {srcRectX, srcRectY, width, height};
  }

  /**
   * @brief Destroy the SpriteComponent
   */
  ~SpriteComponent()
  {
  }
};

#endif // SPRITE_COMPONENT_HPP