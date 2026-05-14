/**
 * @file CameraMovementSystem.hpp
 * @brief Camera following system
 * 
 * Updates camera position to follow entity with CameraFollowComponent.
 */

#ifndef CAMERA_MOVEMENT_SYSTEM_HPP
#define CAMERA_MOVEMENT_SYSTEM_HPP

#include <SDL2/SDL.h>

#include "../ECS/ECS.hpp"

#include "../Components/CameraFollowComponent.hpp"
#include "../Components/TransformComponent.hpp"

#include "../Game/Game.hpp"

/**
 * @class CameraMovementSystem
 * @brief Manages camera position following a target entity
 * 
 * Updates the camera viewport to follow the entity marked with
 * CameraFollowComponent, typically the player.
 */
class CameraMovementSystem : public System
{
public:
  /**
   * @brief Construct a CameraMovementSystem
   */
  CameraMovementSystem()
  {
    requireComponent<TransformComponent>();
    requireComponent<CameraFollowComponent>();
  }

  /**
   * @brief Update camera position
   * @param camera The camera rectangle to update
   */
  void Update(SDL_Rect &camera)
  {
    for (auto entity : getEntities())
    {
      const auto &transform = entity.getComponent<TransformComponent>();

      if (transform.position.x + (camera.w / 2) < static_cast<float>(Game::GetInstance().mapWidth))
      {
        camera.x = static_cast<int>(transform.position.x) - (camera.w / 2);
      }
      if (transform.position.y + (camera.h / 2) < static_cast<float>(Game::GetInstance().mapHeight))
      {
        camera.y = static_cast<int>(transform.position.y) - (camera.h / 2);
      }

      camera.x = camera.x < 0 ? 0 : camera.x;
      camera.y = camera.y < 0 ? 0 : camera.y;
      // camera.x = camera.x > Game::GetInstance().mapWidth - camera.w ? Game::GetInstance().mapWidth - camera.w : camera.x;
      // camera.y = camera.y > Game::GetInstance().mapHeight - camera.h ? Game::GetInstance().mapHeight - camera.h : camera.y;
    }
  }
};

#endif // CAMERA_MOVEMENT_SYSTEM_HPP