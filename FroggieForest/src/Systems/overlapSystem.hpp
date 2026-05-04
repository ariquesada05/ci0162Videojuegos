#ifndef OVERLAP_SYSTEM_HPP
#define OVERLAP_SYSTEM_HPP

#include <memory>

#include "../Components/BoxColliderComponent.hpp"
#include "../Components/RigidBodyComponent.hpp"
#include "../Components/TransformComponent.hpp"
#include "../ECS/ECS.hpp"
#include "../EventManager/EventManager.hpp"
#include "../Events/CollisionEvent.hpp"

enum Direction
{
  TOP,
  BOTTOM,
  LEFT,
  RIGHT
};

class OverlapSystem : public System
{
private:
  bool CheckCollision(Entity a, Entity b, Direction dir)
  {
    auto &aCollider = a.getComponent<BoxColliderComponent>();
    auto &bCollider = b.getComponent<BoxColliderComponent>();
    auto &aTransform = a.getComponent<TransformComponent>();
    auto &bTransform = b.getComponent<TransformComponent>();

    float aX = aTransform.previousPosition.x;
    float aY = aTransform.previousPosition.y;
    float aW = static_cast<float>(aCollider.width);
    float aH = static_cast<float>(aCollider.height);

    float bX = bTransform.previousPosition.x;
    float bY = bTransform.previousPosition.y;
    float bW = static_cast<float>(bCollider.width);
    float bH = static_cast<float>(bCollider.height);

    if (Direction::TOP == dir)
    {
      return (
          aX < bX + bW &&
          aX + aW > bX &&
          aY > bY //
      );
    }
    if (Direction::BOTTOM == dir)
    {
      return (
          aX < bX + bW &&
          aX + aW > bX &&
          aY < bY //
      );
    }

    if (Direction::LEFT == dir)
    {
      return (
          aY < bY + bH &&
          aY + aH > bY &&
          aX > bX //
      );
    }

    if (Direction::RIGHT == dir)
    {
      return (
          aY < bY + bH &&
          aY + aH > bY &&
          aX < bX //
      );
    }

    return false;
  }

  void AvoidOverlap(Entity a, Entity b)
  {
    auto &aCollider = a.getComponent<BoxColliderComponent>();
    auto &aTransform = a.getComponent<TransformComponent>();

    auto &bCollider = b.getComponent<BoxColliderComponent>();
    auto &bTransform = b.getComponent<TransformComponent>();
    auto &bRigidBody = b.getComponent<RigidBodyComponent>();

    if (CheckCollision(a, b, Direction::TOP))
    {
      bTransform.position = glm::vec2(bTransform.position.x, aTransform.position.y - bCollider.height);
      bRigidBody.velocity = glm::vec2(bRigidBody.velocity.x, 0.0f);
    }
    if (CheckCollision(a, b, Direction::BOTTOM))
    {
      bTransform.position = glm::vec2(bTransform.position.x, aTransform.position.y + aCollider.height);
      bRigidBody.velocity = glm::vec2(bRigidBody.velocity.x, 0.0f);
    }

    if (CheckCollision(a, b, Direction::LEFT))
    {
      bTransform.position = glm::vec2(aTransform.position.x - bCollider.width, bTransform.position.y);
      bRigidBody.velocity = glm::vec2(0.0f, bRigidBody.velocity.y);
    }
    if (CheckCollision(a, b, Direction::RIGHT))
    {
      bTransform.position = glm::vec2(aTransform.position.x + aCollider.width, bTransform.position.y);
      bRigidBody.velocity = glm::vec2(0.0f, bRigidBody.velocity.y);
    }
  }

public:
  OverlapSystem()
  {
    requireComponent<BoxColliderComponent>();
    requireComponent<RigidBodyComponent>();
    requireComponent<TransformComponent>();
  }

  void SubscribeToCollisionEvent(const std::unique_ptr<EventManager> &eventManager)
  {
    eventManager->SubscribeToEvent<CollisionEvent, OverlapSystem>(this, &OverlapSystem::OnColisionEvent);
  }

  void OnColisionEvent(CollisionEvent &event)
  {
    auto &aRigidBody = event.entity1.getComponent<RigidBodyComponent>();
    auto &bRigidBody = event.entity2.getComponent<RigidBodyComponent>();

    if (aRigidBody.isSolid && bRigidBody.isSolid)
    {
      if (aRigidBody.mass >= bRigidBody.mass)
      {
        AvoidOverlap(event.entity1, event.entity2);
      }
      else
      {
        AvoidOverlap(event.entity2, event.entity1);
      }
    }
  }
};

#endif // OVERLAP_SYSTEM_HPP