#ifndef ECS_HPP
#define ECS_HPP

#include <bitset>
#include <vector>
#include <memory>
#include <typeindex>
#include <deque>
#include <set>
#include <unordered_map>
#include <iostream>
#include <cstddef>

#include "../Utils/Pool.hpp"

const unsigned int MAX_COMPONENTS = 64;

// Signature
typedef std::bitset<MAX_COMPONENTS> Signature;

struct IComponent
{
protected:
  static int nextID;
};

template <typename T>
class Component : public IComponent
{
public:
  static int getID()
  {
    static int id = nextID++;
    return id;
  }
};

class Entity
{
private:
  int id;

public:
  Entity(int id) : id(id) {}
  int getID() const;
  void Kill();

  bool operator==(const Entity &other) const { return id == other.id; }
  bool operator!=(const Entity &other) const { return id != other.id; }
  bool operator<(const Entity &other) const { return id < other.id; }
  bool operator>(const Entity &other) const { return id > other.id; }

  template <typename TComponent, typename... TArgs>
  void addComponent(TArgs &&...args);

  template <typename TComponent>
  void removeComponent();

  template <typename TComponent>
  bool hasComponent() const;

  template <typename TComponent>
  TComponent &getComponent();

  class Registry *registry;
};

class System
{
private:
  Signature componentSignature;
  std::vector<Entity> entities;

public:
  System() = default;
  ~System() = default;

  void addEntityToSystem(Entity entity);
  void removeEntityFromSystem(Entity entity);
  std::vector<Entity> getEntities() const;
  const Signature &getSignature() const;

  template <typename TComponent>
  void requireComponent();
};

class Registry
{
  int numEntities = 0;
  std::vector<std::shared_ptr<IPool>> componentsPools;
  std::vector<Signature> entityComponentSignatures;

  std::unordered_map<std::type_index, std::shared_ptr<System>> systems;

  std::set<Entity> entitiesToBeAdded;
  std::set<Entity> entitiesToBeKilled;

  std::deque<int> freeIDs;

public:
  Registry();
  ~Registry();

  void Update();

  // Entity management
  Entity createEntity();

  void killEntity(Entity entity);

  // Component management
  template <typename TComponent, typename... TArgs>
  void addComponent(Entity entity, TArgs &&...args);

  template <typename TComponent>
  void removeComponent(Entity entity);

  template <typename TComponent>
  bool hasComponent(Entity entity) const;

  template <typename TComponent>
  TComponent &getComponent(Entity entity);

  // System management

  template <typename TSystem, typename... TArgs>
  void addSystem(TArgs &&...args);

  template <typename TSystem>
  void removeSystem();

  template <typename TSystem>
  bool hasSystem() const;

  template <typename TSystem>
  TSystem &getSystem() const;

  // Add and remove entities from systems
  void addEntityToSystem(Entity entity);
  void removeEntityFromSystem(Entity entity);

  // Reset registry
  void clearAllEntities();
};

template <typename TComponent>
void System::requireComponent()
{
  const int componentID = Component<TComponent>::getID();
  componentSignature.set(componentID);
}

template <typename TComponent, typename... TArgs>
void Registry::addComponent(Entity entity, TArgs &&...args)
{
  const int componentID = Component<TComponent>::getID();
  const int entityID = entity.getID();

  if (static_cast<size_t>(componentID) >= componentsPools.size())
  {
    componentsPools.resize(componentID + 10, nullptr);
  }

  if (!componentsPools[componentID])
  {
    std::shared_ptr<Pool<TComponent>> newComponentPool = std::make_shared<Pool<TComponent>>();
    componentsPools[componentID] = newComponentPool;
  }

  std::shared_ptr<Pool<TComponent>> componentPool = std::static_pointer_cast<Pool<TComponent>>(componentsPools[componentID]);

  if (entityID >= componentPool->getSize())
  {
    componentPool->resize(entityID + 10);
  }

  TComponent newComponent(std::forward<TArgs>(args)...);
  componentPool->set(entityID, newComponent);
  entityComponentSignatures[entityID].set(componentID);
}

template <typename TComponent>
void Registry::removeComponent(Entity entity)
{
  const int componentID = Component<TComponent>::getID();
  const int entityID = entity.getID();

  entityComponentSignatures[entityID].set(componentID, false);
}

template <typename TComponent>
bool Registry::hasComponent(Entity entity) const
{
  const int componentID = Component<TComponent>::getID();
  const int entityID = entity.getID();

  return entityComponentSignatures[entityID].test(componentID);
}

template <typename TComponent>
TComponent &Registry::getComponent(Entity entity)
{
  const int componentID = Component<TComponent>::getID();
  const int entityID = entity.getID();

  auto componentPool = std::static_pointer_cast<Pool<TComponent>>(componentsPools[componentID]);
  return componentPool->get(entityID);
}

template <typename TSystem, typename... TArgs>
void Registry::addSystem(TArgs &&...args)
{
  std::shared_ptr<TSystem> newSystem = std::make_shared<TSystem>(std::forward<TArgs>(args)...);
  systems.insert(std::make_pair(std::type_index(typeid(TSystem)), newSystem));
}

template <typename TSystem>
void Registry::removeSystem()
{
  auto system = systems.find(std::type_index(typeid(TSystem)));
  systems.erase(system);
}

template <typename TSystem>
bool Registry::hasSystem() const
{
  return systems.find(std::type_index(typeid(TSystem))) != systems.end();
}

template <typename TSystem>
TSystem &Registry::getSystem() const
{
  auto system = systems.find(std::type_index(typeid(TSystem)));
  return *(std::static_pointer_cast<TSystem>(system->second));
}

template <typename TComponent, typename... TArgs>
void Entity::addComponent(TArgs &&...args)
{
  registry->addComponent<TComponent>(*this, std::forward<TArgs>(args)...);
}

template <typename TComponent>
void Entity::removeComponent()
{
  registry->removeComponent<TComponent>(*this);
}

template <typename TComponent>
bool Entity::hasComponent() const
{
  return registry->hasComponent<TComponent>(*this);
}

template <typename TComponent>
TComponent &Entity::getComponent()
{
  return registry->getComponent<TComponent>(*this);
}

#endif // ECS_HPP