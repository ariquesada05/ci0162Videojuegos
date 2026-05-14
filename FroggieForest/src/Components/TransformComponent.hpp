/**
 * @file TransformComponent.hpp
 * @brief Position, scale, and rotation component
 */

#ifndef TRANSFORM_COMPONENT_HPP
#define TRANSFORM_COMPONENT_HPP

#include <glm/glm.hpp>

/**
 * @struct TransformComponent
 * @brief Stores spatial transform data for an entity
 * 
 * Tracks the position, scale, and rotation of an entity in world space,
 * as well as the previous position for physics calculations.
 */
struct TransformComponent
{
  glm::vec2 position;        ///< Current position in world space
  glm::vec2 scale;           ///< Scale factors (1.0 = normal size)
  glm::vec2 previousPosition; ///< Position from the previous frame
  double rotation;           ///< Rotation angle in degrees

  /**
   * @brief Construct a TransformComponent
   * @param position The initial position (default: 0, 0)
   * @param scale The initial scale (default: 1, 1)
   * @param rotation The initial rotation (default: 0)
   */
  TransformComponent(glm::vec2 position = glm::vec2(0.0, 0.0), glm::vec2 scale = glm::vec2(1.0, 1.0), double rotation = 0.0)
  {
    this->position = position;
    this->previousPosition = position;
    this->scale = scale;
    this->rotation = rotation;
  }
};

#endif // TRANSFORM_COMPONENT_HPP