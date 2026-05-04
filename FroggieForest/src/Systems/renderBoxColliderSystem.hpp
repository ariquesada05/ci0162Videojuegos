#ifndef RENDERBOXCOLLIDERSYSTEM_HPP
#define RENDERBOXCOLLIDERSYSTEM_HPP

#include <SDL2/SDL.h>

#include "../ECS/ECS.hpp"
#include "../Components/BoxColliderComponent.hpp"
#include "../Components/TransformComponent.hpp"

class RenderBoxColliderSystem : public System
{
public:
  RenderBoxColliderSystem()
  {
    requireComponent<BoxColliderComponent>();
    requireComponent<TransformComponent>();
  }

  void Update(SDL_Renderer *renderer, SDL_Rect &camera)
  {
    for (auto entity : getEntities())
    {
      const auto &collider = entity.getComponent<BoxColliderComponent>();
      const auto &transform = entity.getComponent<TransformComponent>();

      SDL_Rect box = {
          static_cast<int>(transform.position.x - camera.x),
          static_cast<int>(transform.position.y - camera.y),
          static_cast<int>(collider.width * transform.scale.x),
          static_cast<int>(collider.height * transform.scale.y) //
      };

      SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
      SDL_RenderDrawRect(renderer, &box);
    }
  }
};

#endif // RENDERBOXCOLLIDERSYSTEM_HPP