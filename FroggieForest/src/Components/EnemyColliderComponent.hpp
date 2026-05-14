/**
 * @file EnemyColliderComponent.hpp
 * @brief Enemy collision detection component
 */

#ifndef ENEMYCOLLIDERCOMPONENT_HPP
#define ENEMYCOLLIDERCOMPONENT_HPP

#include <glm/glm.hpp>

/**
 * @struct EnemyColliderComponent
 * @brief Collider for enemy entities
 * 
 * Defines a collision area specific to enemy entities for collision
 * detection with the player and other objects.
 */
struct EnemyColliderComponent
{
  float width;  ///< Width of the enemy collider in pixels
  float height; ///< Height of the enemy collider in pixels

  /**
   * @brief Construct an EnemyColliderComponent
   * @param width The collider width (default: 0)
   * @param height The collider height (default: 0)
   */
  EnemyColliderComponent(int width = 0, int height = 0){
    this->width = width;
    this->height = height;
  }
};

#endif // ENEMYCOLLIDERCOMPONENT_HPP