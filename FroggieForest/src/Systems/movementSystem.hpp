/**
 * @file movementSystem.hpp
 * @brief Entity movement system
 * 
 * Updates entity positions based on velocity and physics.
 */

#ifndef MOVEMENT_SYSTEM_HPP
#define MOVEMENT_SYSTEM_HPP

#include <glm/glm.hpp>

#include "../Components/TransformComponent.hpp"
#include "../Components/RigidBodyComponent.hpp"
#include "../ECS/ECS.hpp"

/**
 * @class MovementSystem
 * @brief Updates entity movement based on velocity
 * 
 * Applies physics velocity and acceleration to entity transforms,
 * handling both dynamic and kinematic movement.
 */
class MovementSystem : public System
{
public:
  /**
   * @brief Construct a MovementSystem
   */
  MovementSystem()
  {
    requireComponent<TransformComponent>();
    requireComponent<RigidBodyComponent>();
  }
  
  /**
   * @brief Update entity positions
   * @param dt Delta time in seconds
   */
  void update(double dt)
  {
    for (auto entity : getEntities())
    {
      auto &transform = entity.getComponent<TransformComponent>();
      auto &rigidBody = entity.getComponent<RigidBodyComponent>();

      transform.previousPosition = transform.position;

      if (rigidBody.isDynamic)
      {
        rigidBody.acceleration = rigidBody.sumForces * rigidBody.invMass;
        rigidBody.velocity += rigidBody.acceleration * static_cast<float>(dt);
        transform.position += rigidBody.velocity * static_cast<float>(dt);
        rigidBody.sumForces = glm::vec2(0, 0);
      }
      else
      {
        transform.position.x += rigidBody.velocity.x * dt;
        transform.position.y += rigidBody.velocity.y * dt;
      }
    }
  }
};

#endif // MOVEMENT_SYSTEM_HPP