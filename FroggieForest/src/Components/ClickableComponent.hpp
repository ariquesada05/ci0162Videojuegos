/**
 * @file ClickableComponent.hpp
 * @brief Click interaction component
 */

#ifndef CLICKABLE_COMPONENT_HPP
#define CLICKABLE_COMPONENT_HPP

/**
 * @struct ClickableComponent
 * @brief Marks an entity as clickable
 * 
 * Entities with this component can respond to mouse clicks.
 * The isClicked flag tracks if the entity was clicked this frame.
 */
struct ClickableComponent
{
  bool isClicked; ///< Whether this entity was clicked this frame

  /**
   * @brief Construct a ClickableComponent
   */
  ClickableComponent()
  {
    isClicked = false;
  }
};

#endif // CLICKABLE_COMPONENT_HPP