#ifndef BOX_COLLISION_SYSTEM_HPP
#define BOX_COLLISION_SYSTEM_HPP

#include <iostream>
#include <memory>

#include "../Components/BoxColliderComponent.hpp"
#include "../Components/ScriptComponent.hpp"
#include "../Components/TransformComponent.hpp"
#include "../ECS/ECS.hpp"
#include "../EventManager/EventManager.hpp"
#include "../Events/CollisionEvent.hpp"

class BoxCollisionSystem : public System
{
private:
  bool CheckAABBCollision(float aX, float aY, float aW, float aH,
                          float bX, float bY, float bW, float bH)
  {
    return (
        aX < bX + bW &&
        aX + aW > bX &&
        aY < bY + bH &&
        aY + aH > bY);
  }

public:
  BoxCollisionSystem()
  {
    requireComponent<BoxColliderComponent>();
    requireComponent<TransformComponent>();
  }

  void update(const std::unique_ptr<EventManager> &eventManager, sol::state_view &lua)
  {
    auto entities = getEntities();
    for (auto i = entities.begin(); i != entities.end(); i++)
    {
      Entity a = *i;
      auto &aColider = a.getComponent<BoxColliderComponent>();
      auto &aTransform = a.getComponent<TransformComponent>();

      for (auto j = i; j != entities.end(); j++)
      {
        Entity b = *j;

        if (a == b)
        {
          continue;
        }
        auto &bColider = b.getComponent<BoxColliderComponent>();
        auto &bTransform = b.getComponent<TransformComponent>();

        bool collision = CheckAABBCollision(
            aTransform.position.x,
            aTransform.position.y,
            static_cast<float>(aColider.width),
            static_cast<float>(aColider.height),
            bTransform.position.x,
            bTransform.position.y,
            static_cast<float>(bColider.width),
            static_cast<float>(bColider.height) //
        );

        if (collision)
        {
          eventManager->EmitEvent<CollisionEvent>(a, b);

          if (a.hasComponent<ScriptComponent>())
          {
            const auto &script = a.getComponent<ScriptComponent>();
            if (script.onCollision != sol::nil)
            {
              lua["this"] = a;
              script.onCollision(b);
            }
          }

          if (b.hasComponent<ScriptComponent>())
          {
            const auto &script = b.getComponent<ScriptComponent>();
            if (script.onCollision != sol::nil)
            {
              lua["this"] = b;
              script.onCollision(a);
            }
          }
        }
      }
    }
  }
};

#endif // BOX_COLLISION_SYSTEM_HPP