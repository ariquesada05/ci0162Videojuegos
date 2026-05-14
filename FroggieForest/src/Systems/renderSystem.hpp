/**
 * @file renderSystem.hpp
 * @brief Sprite rendering system
 * 
 * Renders all entities with sprite and transform components to the screen.
 */

#ifndef RENDER_SYSTEM_HPP
#define RENDER_SYSTEM_HPP

#include <SDL2/SDL.h>

#include "../ECS/ECS.hpp"
#include "../AssetManager/AssetManager.hpp"
#include "../Components/TransformComponent.hpp"
#include "../Components/SpriteComponent.hpp"

/**
 * @class RenderSystem
 * @brief Renders sprites for all entities
 * 
 * Processes all entities that have both TransformComponent and SpriteComponent,
 * drawing them to the screen with camera support.
 */
class RenderSystem : public System
{
public:
  /**
   * @brief Construct a RenderSystem
   */
  RenderSystem()
  {
    requireComponent<TransformComponent>();
    requireComponent<SpriteComponent>();
  }

  /**
   * @brief Update and render all entities
   * @param renderer The SDL renderer to draw with
   * @param AssetManager The asset manager containing textures
   * @param camera The camera viewport rectangle
   */
  void update(SDL_Renderer *renderer, const std::unique_ptr<AssetManager> &AssetManager, SDL_Rect &camera)
  {
    for (auto &entity : getEntities())
    {
      const auto &sprite = entity.getComponent<SpriteComponent>();
      const auto &transform = entity.getComponent<TransformComponent>();
      SDL_Texture *texture = AssetManager->getTexture(sprite.textureID);
      if (texture == nullptr)
      {
        std::cerr << "[RenderSystem] Missing texture: " << sprite.textureID << std::endl;
        continue;
      }

      SDL_Rect srcRect = sprite.srcRect;
      SDL_Rect dstRect = {
          static_cast<int>(transform.position.x - camera.x),
          static_cast<int>(transform.position.y - camera.y),
          static_cast<int>(sprite.width * transform.scale.x),
          static_cast<int>(sprite.height * transform.scale.y),
      };

      SDL_RenderCopyEx(
          renderer,
          texture,
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