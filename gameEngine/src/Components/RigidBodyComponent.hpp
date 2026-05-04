#ifndef RIGIDBODY_COMPONENT_HPP
#define RIGIDBODY_COMPONENT_HPP

#include <glm/glm.hpp>

struct RigidBodyComponent
{
  bool isDynamic;
  bool isSolid;

  glm::vec2 sumForces = glm::vec2(0, 0);
  glm::vec2 velocity = glm::vec2(0, 0);
  glm::vec2 acceleration = glm::vec2(0, 0);

  float mass;
  float invMass;

  RigidBodyComponent(bool isDynamic = false, bool isSolid = false, float mass = 1)
  {
    this->isDynamic = isDynamic;
    this->isSolid = isSolid;
    this->mass = mass;
    this->invMass = 1 / mass;
  };
};

#endif // RIGIDBODY_COMPONENT_HPP