/**
 * @file ECS.hpp
 * @brief Entity Component System (ECS) architecture for game objects
 * 
 * This file implements a flexible ECS pattern for managing game entities,
 * their components, and the systems that operate on them.
 */

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

/** @brief Maximum number of component types supported by the system */
const unsigned int MAX_COMPONENTS = 64;

/** @brief Bitset representing which components an entity has */
typedef std::bitset<MAX_COMPONENTS> Signature;

/**
 * @struct IComponent
 * @brief Base interface for all component types
 * 
 * Provides a common interface for all components in the ECS system.
 */
struct IComponent
{
protected:
  static int nextID; ///< Static counter for component type IDs
};

template <typename T>
class Component : public IComponent
{
public:
  /**
   * @brief Get the unique ID for a component type
   * @tparam T The component type
   * @return int Unique component type ID
   */
  static int getID()
  {
    static int id = nextID++;
    return id;
  }
};

/**
 * @class Entity
 * @brief Represents an object in the game world with components
 * 
 * An entity is an object that can have various components attached to it.
 * Components define the properties and behaviors of the entity.
 */
class Entity
{
private:
  int id; ///< Unique identifier for this entity

public:
  /**
   * @brief Construct a new Entity
   * @param id The unique identifier for this entity
   */
  Entity(int id) : id(id) {}
  
  /**
   * @brief Get the unique ID of this entity
   * @return int The entity ID
   */
  int getID() const;
  
  /**
   * @brief Mark this entity for deletion
   */
  void Kill();

  bool operator==(const Entity &other) const { return id == other.id; } ///< Equality operator
  bool operator!=(const Entity &other) const { return id != other.id; } ///< Inequality operator
  bool operator<(const Entity &other) const { return id < other.id; }   ///< Less than operator
  bool operator>(const Entity &other) const { return id > other.id; }   ///< Greater than operator

  /**
   * @brief Add a component to this entity
   * @tparam TComponent The component type to add
   * @tparam TArgs The argument types for the component constructor
   * @param args Arguments to pass to the component constructor
   */
  template <typename TComponent, typename... TArgs>
  void addComponent(TArgs &&...args);

  /**
   * @brief Remove a component from this entity
   * @tparam TComponent The component type to remove
   */
  template <typename TComponent>
  void removeComponent();

  /**
   * @brief Check if this entity has a specific component
   * @tparam TComponent The component type to check for
   * @return bool True if the entity has the component
   */
  template <typename TComponent>
  bool hasComponent() const;

  /**
   * @brief Get a component from this entity
   * @tparam TComponent The component type to retrieve
   * @return TComponent& Reference to the component
   */
  template <typename TComponent>
  TComponent &getComponent();

  class Registry *registry; ///< Pointer to the registry that manages this entity
};

/**
 * @class System
 * @brief Base class for systems that operate on entities with specific components
 * 
 * A system is responsible for implementing logic that acts on entities that have
 * specific components. Systems are the behavior layer of the ECS architecture.
 */
class System
{
private:
  Signature componentSignature;        ///< Bitset of required components
  std::vector<Entity> entities;        ///< List of entities matched by this system

public:
  System() = default;
  ~System() = default;

  /**
   * @brief Add an entity to this system
   * @param entity The entity to add
   */
  void addEntityToSystem(Entity entity);
  
  /**
   * @brief Remove an entity from this system
   * @param entity The entity to remove
   */
  void removeEntityFromSystem(Entity entity);
  
  /**
   * @brief Get all entities in this system
   * @return std::vector<Entity> Vector of entities
   */
  std::vector<Entity> getEntities() const;
  
  /**
   * @brief Get the component signature required by this system
   * @return const Signature& Reference to the component signature
   */
  const Signature &getSignature() const;

  /**
   * @brief Require a specific component type for this system
   * @tparam TComponent The component type to require
   */
  template <typename TComponent>
  void requireComponent();
};

/**
 * @class Registry
 * @brief Central manager for all entities, components, and systems
 * 
 * The Registry is the core of the ECS architecture. It manages entity creation,
 * component management, system registration, and entity lifecycle.
 */
class Registry
{
  int numEntities = 0;                                           ///< Total number of entities created
  std::vector<std::shared_ptr<IPool>> componentsPools;          ///< Storage pools for each component type
  std::vector<Signature> entityComponentSignatures;             ///< Signature of each entity

  std::unordered_map<std::type_index, std::shared_ptr<System>> systems; ///< All registered systems

  std::set<Entity> entitiesToBeAdded;   ///< Entities scheduled for addition
  std::set<Entity> entitiesToBeKilled;  ///< Entities scheduled for deletion

  std::deque<int> freeIDs;              ///< Pool of available entity IDs

public:
  /**
   * @brief Construct a new Registry
   */
  Registry();
  
  /**
   * @brief Destroy the Registry
   */
  ~Registry();

  /**
   * @brief Update the registry - processes pending entity additions/deletions
   */
  void Update();

  /**
   * @brief Create a new entity
   * @return Entity The newly created entity
   */
  Entity createEntity();

  /**
   * @brief Mark an entity for deletion
   * @param entity The entity to delete
   */
  void killEntity(Entity entity);

  /**
   * @brief Add a component to an entity
   * @tparam TComponent The component type to add
   * @tparam TArgs Argument types for component constructor
   * @param entity The entity to add the component to
   * @param args Arguments for the component constructor
   */
  template <typename TComponent, typename... TArgs>
  void addComponent(Entity entity, TArgs &&...args);

  /**
   * @brief Remove a component from an entity
   * @tparam TComponent The component type to remove
   * @param entity The entity to remove the component from
   */
  template <typename TComponent>
  void removeComponent(Entity entity);

  /**
   * @brief Check if an entity has a component
   * @tparam TComponent The component type to check for
   * @param entity The entity to check
   * @return bool True if the entity has the component
   */
  template <typename TComponent>
  bool hasComponent(Entity entity) const;

  /**
   * @brief Get a component from an entity
   * @tparam TComponent The component type to retrieve
   * @param entity The entity to get the component from
   * @return TComponent& Reference to the component
   */
  template <typename TComponent>
  TComponent &getComponent(Entity entity);

  /**
   * @brief Register a new system
   * @tparam TSystem The system type to register
   * @tparam TArgs Argument types for system constructor
   * @param args Arguments for the system constructor
   */
  template <typename TSystem, typename... TArgs>
  void addSystem(TArgs &&...args);

  /**
   * @brief Remove a system
   * @tparam TSystem The system type to remove
   */
  template <typename TSystem>
  void removeSystem();

  /**
   * @brief Check if a system is registered
   * @tparam TSystem The system type to check for
   * @return bool True if the system is registered
   */
  template <typename TSystem>
  bool hasSystem() const;

  /**
   * @brief Get a registered system
   * @tparam TSystem The system type to retrieve
   * @return TSystem& Reference to the system
   */
  template <typename TSystem>
  TSystem &getSystem() const;

  /**
   * @brief Add an entity to all matching systems
   * @param entity The entity to add
   */
  void addEntityToSystem(Entity entity);
  
  /**
   * @brief Remove an entity from all systems
   * @param entity The entity to remove
   */
  void removeEntityFromSystem(Entity entity);

  /**
   * @brief Clear all entities from the registry
   */
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
  
  addEntityToSystem(entity);
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