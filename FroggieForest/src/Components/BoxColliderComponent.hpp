/**
 * @file BoxColliderComponent.hpp
 * @brief Rectangular collision detection component
 */

#ifndef BOX_COLLIDER_COMPONENT_HPP
#define BOX_COLLIDER_COMPONENT_HPP

#include <glm/glm.hpp>

/**
 * @struct BoxColliderComponent
 * @brief Rectangular AABB collider for collision detection
 * 
 * Defines an axis-aligned bounding box collider for an entity.
 * The position is relative to the entity's transform position.
 */
struct BoxColliderComponent
{
  int width;           ///< Width of the collider in pixels
  int height;          ///< Height of the collider in pixels
  glm::vec2 offset;    ///< Offset from the entity's position

  /**
   * @brief Construct a BoxColliderComponent
   * @param width The collider width (default: 0)
   * @param height The collider height (default: 0)
   * @param offset The offset from entity position (default: 0, 0)
   */
  BoxColliderComponent(int width = 0, int height = 0, glm::vec2 offset = glm::vec2(0, 0))
  {
    this->width = width;
    this->height = height;
    this->offset = offset;
  }
};

#endif // BOX_COLLIDER_COMPONENT_HPP