/**
 * @file CollisionEvent.hpp
 * @brief Collision event between two entities
 */

#ifndef COLLISION_EVENT_HPP
#define COLLISION_EVENT_HPP

#include "../ECS/ECS.hpp"
#include "../EventManager/Event.hpp"

/**
 * @class CollisionEvent
 * @brief Event fired when two entities collide
 * 
 * Represents a collision between two entities in the game world.
 */
class CollisionEvent : public Event
{
public:
  Entity entity1; ///< The first entity involved in the collision
  Entity entity2; ///< The second entity involved in the collision

  /**
   * @brief Construct a new CollisionEvent
   * @param entity1 The first entity
   * @param entity2 The second entity
   */
  CollisionEvent(Entity entity1, Entity entity2)
      : entity1(entity1), entity2(entity2) {}
};

#endif // COLLISION_EVENT_HPP