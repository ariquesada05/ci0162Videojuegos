/**
 * @file overlapSystem.hpp
 * @brief Directional collision overlap detection system
 */

#ifndef OVERLAP_SYSTEM_HPP
#define OVERLAP_SYSTEM_HPP

#include <algorithm>
#include <memory>

#include "../Components/BoxColliderComponent.hpp"
#include "../Components/RigidBodyComponent.hpp"
#include "../Components/TransformComponent.hpp"
#include "../ECS/ECS.hpp"
#include "../EventManager/EventManager.hpp"
#include "../Events/CollisionEvent.hpp"

/**
 * @enum Direction
 * @brief Collision direction enumeration
 */
enum Direction
{
  TOP,    ///< Collision from top
  BOTTOM, ///< Collision from bottom
  LEFT,   ///< Collision from left
  RIGHT   ///< Collision from right
};

/**
 * @class OverlapSystem
 * @brief Detects directional collisions
 */
class OverlapSystem : public System
{
private:
  /**
   * @brief Check directional collision
   * @param a First entity
   * @param b Second entity
   * @param dir Direction to check
   * @return bool True if collision exists in direction
   */
  // Empuja a 'b' (entidad dinámica) fuera de 'a' (entidad estática/pesada)
  // resolviendo SOLO el eje de menor penetración. Así un aterrizaje (mucho
  // solapamiento horizontal, poco vertical) se resuelve hacia arriba y no
  // se dispara además un empuje lateral que haría que el piso actuara como
  // pared.
  void AvoidOverlap(Entity a, Entity b)
  {
    auto &aCollider = a.getComponent<BoxColliderComponent>();
    auto &aTransform = a.getComponent<TransformComponent>();

    auto &bCollider = b.getComponent<BoxColliderComponent>();
    auto &bTransform = b.getComponent<TransformComponent>();
    auto &bRigidBody = b.getComponent<RigidBodyComponent>();

    float aX = aTransform.position.x;
    float aY = aTransform.position.y;
    float aW = static_cast<float>(aCollider.width);
    float aH = static_cast<float>(aCollider.height);

    float bX = bTransform.position.x;
    float bY = bTransform.position.y;
    float bW = static_cast<float>(bCollider.width);
    float bH = static_cast<float>(bCollider.height);

    // Solapamiento real en cada eje (positivo solo si de verdad se traslapan).
    float overlapX = std::min(aX + aW, bX + bW) - std::max(aX, bX);
    float overlapY = std::min(aY + aH, bY + bH) - std::max(aY, bY);

    if (overlapX <= 0.0f || overlapY <= 0.0f)
    {
      return;
    }

    float aCenterX = aX + aW * 0.5f;
    float aCenterY = aY + aH * 0.5f;
    float bCenterX = bX + bW * 0.5f;
    float bCenterY = bY + bH * 0.5f;

    if (overlapY < overlapX)
    {
      // Penetración vertical menor => colisión de piso/techo.
      if (bCenterY < aCenterY)
      {
        // 'b' viene desde arriba: se posa sobre 'a'.
        bTransform.position.y = aY - bH;
      }
      else
      {
        // 'b' viene desde abajo: golpea el techo.
        bTransform.position.y = aY + aH;
      }
      bRigidBody.velocity.y = 0.0f;
    }
    else
    {
      // Penetración horizontal menor => colisión lateral (pared).
      if (bCenterX < aCenterX)
      {
        bTransform.position.x = aX - bW;
      }
      else
      {
        bTransform.position.x = aX + aW;
      }
      bRigidBody.velocity.x = 0.0f;
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