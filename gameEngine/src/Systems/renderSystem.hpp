#ifndef RENDER_SYSTEM_HPP
#define RENDER_SYSTEM_HPP

#include <SDL2/SDL.h>

#include "../ECS/ECS.hpp"
#include "../AssetManager/AssetManager.hpp"
#include "../Components/TransformComponent.hpp"
#include "../Components/SpriteComponent.hpp"

class RenderSystem : public System
{
public:
  RenderSystem()
  {
    requireComponent<TransformComponent>();
    requireComponent<SpriteComponent>();
  }

  void update(SDL_Renderer *renderer, const std::unique_ptr<AssetManager> &AssetManager, SDL_Rect &camera)
  {
    for (auto &entity : getEntities())
    {
      const auto &sprite = entity.getComponent<SpriteComponent>();
      const auto &transform = entity.getComponent<TransformComponent>();

      SDL_Rect srcRect = sprite.srcRect;
      SDL_Rect dstRect = {
          static_cast<int>(transform.position.x - camera.x),
          static_cast<int>(transform.position.y - camera.y),
          static_cast<int>(sprite.width * transform.scale.x),
          static_cast<int>(sprite.height * transform.scale.y),
      };

      SDL_RenderCopyEx(
          renderer,
          AssetManager->getTexture(sprite.textureID),
          &srcRect,
          &dstRect,
          transform.rotation,
          NULL,
          (sprite.flip) ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE //
      );
    }
  }
};

#endif // RENDER_SYSTEM_HPP