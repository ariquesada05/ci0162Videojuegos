/**
 * @file textSystem.hpp
 * @brief Text rendering system
 * 
 * Renders text entities using fonts and SDL_ttf.
 */

#ifndef TEXTSYSTEM_HPP
#define TEXTSYSTEM_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include <memory>

#include "../Components/TextComponent.hpp"
#include "../Components/TransformComponent.hpp"
#include "../AssetManager/AssetManager.hpp"
#include "../ECS/ECS.hpp"

/**
 * @class TextSystem
 * @brief Renders text for all entities
 * 
 * Renders text from TextComponent using fonts from AssetManager.
 * Caches rendered textures for entities with text.
 */
class TextSystem : public System
{
public:
  /**
   * @brief Construct a TextSystem
   */
  TextSystem()
  {
    requireComponent<TextComponent>();
    requireComponent<TransformComponent>();
  }
  
  /**
   * @brief Update and render all text entities
   * @param renderer The SDL renderer to draw with
   * @param assetManager The asset manager containing fonts
   */
  void update(SDL_Renderer *renderer, const std::unique_ptr<AssetManager> &assetManager)
  {
    for (auto entity : getEntities())
    {
      auto &text = entity.getComponent<TextComponent>();
      auto &transform = entity.getComponent<TransformComponent>();

      TTF_Font *font = assetManager->getFont(text.fontID);
      if (font == nullptr)
      {
        std::cerr << "[TextSystem] Missing font: " << text.fontID << std::endl;
        continue;
      }

      SDL_Surface *surface = TTF_RenderText_Blended(
          font, text.text.c_str(), text.color);
      if (surface == nullptr)
      {
        std::cerr << "[TextSystem] Failed to render text: " << TTF_GetError() << std::endl;
        continue;
      }

      text.width = surface->w;
      text.height = surface->h;

      SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
      SDL_FreeSurface(surface); 
      if (texture == nullptr)
      {
        std::cerr << "[TextSystem] Failed to create text texture: " << SDL_GetError() << std::endl;
        continue;
      }

      SDL_Rect destRect = {
          static_cast<int>(transform.position.x),
          static_cast<int>(transform.position.y),
          text.width * static_cast<int>(transform.scale.x),
          text.height * static_cast<int>(transform.scale.y)};

      SDL_RenderCopy(renderer, texture, NULL, &destRect);
      SDL_DestroyTexture(texture);
    }
  }
};

#endif // TEXTSYSTEM_HPP
