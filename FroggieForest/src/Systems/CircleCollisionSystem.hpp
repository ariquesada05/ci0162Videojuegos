/**
 * @file CircleCollisionSystem.hpp
 * @brief Circle collision detection system
 */

#ifndef CIRCLE_COLISION_SYSTEM_HPP
#define CIRCLE_COLISION_SYSTEM_HPP

#include <memory>

#include "../Components/CircleColliderComponent.hpp"
#include "../Components/TransformComponent.hpp"
#include "../ECS/ECS.hpp"
#include "../EventManager/EventManager.hpp"
#include "../Events/CollisionEvent.hpp"

/**
 * @class CircleCollisionSystem
 * @brief Detects collisions between circle colliders
 */
class CircleCollisionSystem : public System
{
public:
  /**
   * @brief Construct a CircleCollisionSystem
   */
  CircleCollisionSystem()
  {
    requireComponent<CircleColliderComponent>();
    requireComponent<TransformComponent>();
  }

  /**
   * @brief Update collision detection for circles
   * @param EventManager Reference to event manager
   */
  void update(std::unique_ptr<EventManager> &EventManager)
  {
    auto entities = getEntities();
    for (auto i = entities.begin(); i != entities.end(); i++)
    {
      Entity a = *i;
      auto &aCircleCollider = a.getComponent<CircleColliderComponent>();
      auto &aTransform = a.getComponent<TransformComponent>();

      for (auto j = i; j != entities.end(); j++)
      {
        Entity b = *j;

        if (a == b)
        {
          continue;
        }
        auto &bCircleCollider = b.getComponent<CircleColliderComponent>();
        auto &bTransform = b.getComponent<TransformComponent>();

        glm::vec2 aCenterPos = glm::vec2(
            aTransform.position.x - (aCircleCollider.width / 2) * aTransform.scale.x,
            aTransform.position.y - (aCircleCollider.height / 2) * aTransform.scale.y);

        glm::vec2 bCenterPos = glm::vec2(
            bTransform.position.x - (bCircleCollider.width / 2) * bTransform.scale.x,
            bTransform.position.y - (bCircleCollider.height / 2) * bTransform.scale.y);

        int aRadius = aCircleCollider.radius * aTransform.scale.x;
        int bRadius = bCircleCollider.radius * bTransform.scale.x;

        bool collision = CheckCircularCollision(aRadius, bRadius, aCenterPos, bCenterPos);

        if (collision)
        {
          EventManager->EmitEvent<CollisionEvent>(a, b);
        }
      }
    }
  }

  bool CheckCircularCollision(int aRadius, int bRadius, glm::vec2 aPosition, glm::vec2 bPosition)
  {
    glm::vec2 distance = aPosition - bPosition;
    double length = glm::length((distance.x * distance.x) + (distance.y * distance.y));
    // there is collision if the sum of the radius is greater or equal to
    // the distance between the two circles
    return (aRadius + bRadius) >= length;
  }
};

#endif // CIRCLE_COLISION_SYSTEM_HPP