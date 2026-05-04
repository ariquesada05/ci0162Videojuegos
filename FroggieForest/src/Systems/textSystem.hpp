#ifndef TEXTSYSTEM_HPP
#define TEXTSYSTEM_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include <memory>

#include "../Components/TextComponent.hpp"
#include "../Components/TransformComponent.hpp"
#include "../AssetManager/AssetManager.hpp"
#include "../ECS/ECS.hpp"

class TextSystem : public System
{
public:
  TextSystem()
  {
    requireComponent<TextComponent>();
    requireComponent<TransformComponent>();
  }

  void update(SDL_Renderer *renderer, const std::unique_ptr<AssetManager> &assetManager)
  {
    for (auto entity : getEntities())
    {
      auto &text = entity.getComponent<TextComponent>();
      auto &transform = entity.getComponent<TransformComponent>();

      SDL_Surface *surface = TTF_RenderText_Blended(
          assetManager->getFont(text.fontID), text.text.c_str(), text.color);
      text.width = surface->w;
      text.height = surface->h;
      SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
      SDL_FreeSurface(surface);

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