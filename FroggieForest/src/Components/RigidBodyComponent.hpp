/**
 * @file RigidBodyComponent.hpp
 * @brief Physics component for dynamic bodies
 */

#ifndef RIGIDBODY_COMPONENT_HPP
#define RIGIDBODY_COMPONENT_HPP

#include <glm/glm.hpp>

/**
 * @struct RigidBodyComponent
 * @brief Stores physics simulation data for an entity
 * 
 * Contains velocity, acceleration, forces, and mass information
 * for dynamic physics simulation.
 */
struct RigidBodyComponent
{
  bool isDynamic; ///< Whether this body is affected by physics
  bool isSolid;   ///< Whether this body is solid and collides with others

  glm::vec2 sumForces = glm::vec2(0, 0);   ///< Sum of all forces applied
  glm::vec2 velocity = glm::vec2(0, 0);    ///< Current velocity
  glm::vec2 acceleration = glm::vec2(0, 0); ///< Current acceleration

  float mass;    ///< Mass of the body in kg
  float invMass; ///< Inverse mass (1/mass) for calculations

  /**
   * @brief Construct a RigidBodyComponent
   * @param isDynamic Whether the body is dynamic (default: false)
   * @param isSolid Whether the body is solid (default: false)
   * @param mass The mass in kg (default: 1)
   */
  RigidBodyComponent(bool isDynamic = false, bool isSolid = false, float mass = 1)
  {
    this->isDynamic = isDynamic;
    this->isSolid = isSolid;
    this->mass = mass;
    this->invMass = 1 / mass;
  };
};

#endif // RIGIDBODY_COMPONENT_HPP