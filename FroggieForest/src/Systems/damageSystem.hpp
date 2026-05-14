#ifndef DAMAGESYSTEM_HPP
#define DAMAGESYSTEM_HPP

#include <iostream>
#include <memory>

#include "../Components/CircleColliderComponent.hpp"
#include "../ECS/ECS.hpp"
#include "../EventManager/EventManager.hpp"
#include "../Events/CollisionEvent.hpp"

class DamageSystem : public System
{
public:
  DamageSystem()
  {
    requireComponent<CircleColliderComponent>();
  }

  void SubscribeToCollisionEvent(std::unique_ptr<EventManager> &eventManager)
  {
    eventManager->SubscribeToEvent<CollisionEvent, DamageSystem>(this, &DamageSystem::OnCollision);
  }
  void OnCollision(CollisionEvent &event)
  {
    std::cout << "[DamageSystem] Collision detected" << event.entity1.getID() << "y" << event.entity2.getID() << std::endl;
    event.entity1.Kill();
    event.entity2.Kill();
  }
};

#endif // DAMAGESYSTEM_HPP