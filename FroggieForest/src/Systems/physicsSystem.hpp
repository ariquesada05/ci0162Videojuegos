/**
 * @file physicsSystem.hpp
 * @brief Physics simulation system
 * 
 * Applies physics forces like gravity to dynamic entities.
 */

#ifndef PHYSICS_SYSTEM_HPP
#define PHYSICS_SYSTEM_HPP

#include "../Components/RigidBodyComponent.hpp"
#include "../ECS/ECS.hpp"

/**
 * @class PhysicsSystem
 * @brief Applies physics simulation to entities
 * 
 * Updates physics properties like velocity and forces for all entities
 * with RigidBodyComponent, including gravity application.
 */
class PhysicsSystem : public System
{
public:
  /**
   * @brief Construct a PhysicsSystem
   */
  PhysicsSystem()
  {
    requireComponent<RigidBodyComponent>();
  }

  /**
   * @brief Update physics for all entities
   */
  void update()
  {
    for (auto entity : getEntities())
    {
      auto &rigidBody = entity.getComponent<RigidBodyComponent>();

      // Aplicar la fuerza de gravedad
      if (rigidBody.isDynamic)
      {
        rigidBody.sumForces += glm::vec2(0.0f, 9.8 * rigidBody.mass * 64);
      }
    }
  }
};

#endif // PHYSICS_SYSTEM_HPP