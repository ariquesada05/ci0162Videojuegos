/**
 * @file CircleColliderComponent.hpp
 * @brief Circular collision detection component
 */

#ifndef CIRCLECOLLIDERCOMPONENT_HPP
#define CIRCLECOLLIDERCOMPONENT_HPP

/**
 * @struct CircleColliderComponent
 * @brief Circular collider for collision detection
 * 
 * Defines a circular collider for an entity with a radius.
 * Also includes bounding box dimensions.
 */
struct CircleColliderComponent
{
  int radius; ///< Radius of the circle collider in pixels
  int width;  ///< Width of the bounding box
  int height; ///< Height of the bounding box

  /**
   * @brief Construct a CircleColliderComponent
   * @param radius The collider radius (default: 0)
   * @param width The bounding box width (default: 0)
   * @param height The bounding box height (default: 0)
   */
  CircleColliderComponent(int radius = 0, int width = 0, int height = 0)
  {
    this->radius = radius;
    this->width = width;
    this->height = height;
  }
};

#endif // CIRCLE_COLLIDER_COMPONENT_HPP