/**
 * @file renderBoxColliderSystem.hpp
 * @brief Debug box collider visualization system
 */

#ifndef RENDERBOXCOLLIDERSYSTEM_HPP
#define RENDERBOXCOLLIDERSYSTEM_HPP

#include <SDL2/SDL.h>

#include "../ECS/ECS.hpp"
#include "../Components/BoxColliderComponent.hpp"
#include "../Components/TransformComponent.hpp"

/**
 * @class RenderBoxColliderSystem
 * @brief Renders box colliders for debugging
 * 
 * Visualizes box colliders as rectangles on the screen for debugging purposes.
 */
class RenderBoxColliderSystem : public System
{
public:
  /**
   * @brief Construct a RenderBoxColliderSystem
   */
  RenderBoxColliderSystem()
  {
    requireComponent<BoxColliderComponent>();
    requireComponent<TransformComponent>();
  }

  /**
   * @brief Render all box colliders
   * @param renderer The SDL renderer to draw with
   * @param camera The camera viewport
   */
  void Update(SDL_Renderer *renderer, SDL_Rect &camera)
  {
    for (auto entity : getEntities())
    {
      const auto &collider = entity.getComponent<BoxColliderComponent>();
      const auto &transform = entity.getComponent<TransformComponent>();

      // La física (boxCollisionSystem/overlapSystem) usa el tamaño del
      // collider SIN escalar, así que la caja de depuración debe dibujarse
      // igual para que coincida con dónde ocurren realmente las colisiones.
      SDL_Rect box = {
          static_cast<int>(transform.position.x - camera.x),
          static_cast<int>(transform.position.y - camera.y),
          static_cast<int>(collider.width),
          static_cast<int>(collider.height) //
      };

      SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
      SDL_RenderDrawRect(renderer, &box);
    }
  }
};

#endif // RENDERBOXCOLLIDERSYSTEM_HPP