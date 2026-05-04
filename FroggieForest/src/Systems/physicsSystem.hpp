#ifndef PHYSICS_SYSTEM_HPP
#define PHYSICS_SYSTEM_HPP

#include "../Components/RigidBodyComponent.hpp"
#include "../ECS/ECS.hpp"

class PhysicsSystem : public System
{
public:
  PhysicsSystem()
  {
    requireComponent<RigidBodyComponent>();
  }

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