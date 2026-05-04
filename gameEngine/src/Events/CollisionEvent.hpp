#ifndef COLLISION_EVENT_HPP
#define COLLISION_EVENT_HPP

#include "../ECS/ECS.hpp"
#include "../EventManager/Event.hpp"

class CollisionEvent : public Event
{
public:
  Entity entity1;
  Entity entity2;

  CollisionEvent(Entity entity1, Entity entity2)
      : entity1(entity1), entity2(entity2) {}
};

#endif // COLLISION_EVENT_HPP