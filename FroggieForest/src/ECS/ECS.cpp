#include "ECS.hpp"
#include <algorithm>

int IComponent::nextID = 0;

int Entity::getID() const
{
  return id;
}

void Entity::Kill()
{
  registry->killEntity(*this);
}

void System::addEntityToSystem(Entity entity)
{
  entities.push_back(entity);
}

void System::removeEntityFromSystem(Entity entity)
{
  auto it = std::remove_if(entities.begin(), entities.end(), [&](Entity other)
                           { return other.getID() == entity.getID(); });
  entities.erase(it, entities.end());
}

std::vector<Entity> System::getEntities() const
{
  return entities;
}

const Signature &System::getSignature() const
{
  return componentSignature;
}

Registry::Registry()
{
  std::cout << "[Registry] Se ejecuta registro" << std::endl;
}

Registry::~Registry()
{
  std::cout << "[Registry] Se ejecuta destrucción" << std::endl;
}

Entity Registry::createEntity()
{
  int entityID = 0;

  if (freeIDs.empty())
  {
    entityID = numEntities++;
    if (static_cast<long unsigned int>(entityID) >= entityComponentSignatures.size())
    {
      entityComponentSignatures.resize(entityID + 100);
    }
  }
  else
  {
    entityID = freeIDs.front();
    freeIDs.pop_front();
  }

  Entity entity(entityID);
  entity.registry = this;
  entitiesToBeAdded.insert(entity);

  

  return entity;
}

void Registry::killEntity(Entity entity)
{
  entitiesToBeKilled.insert(entity);
  std::cout << "[Registry] Se elimina entidad" << std::endl;
}

void Registry::addEntityToSystem(Entity entity)
{
  const int entityID = entity.getID();

  const auto &entityComponentSignature = entityComponentSignatures[entityID];

  for (const auto &system : systems)
  {
    const auto &componentSignature = system.second->getSignature();

    if ((entityComponentSignature & componentSignature) == componentSignature)
    {
      system.second->addEntityToSystem(entity);
    }
  }
}

void Registry::removeEntityFromSystem(Entity entity)
{
  for (const auto &system : systems)
  {
    system.second->removeEntityFromSystem(entity);
  }
}

void Registry::Update()
{
  for (const auto &entity : entitiesToBeAdded)
  {
    addEntityToSystem(entity);
  }

  for (const auto &entity : entitiesToBeKilled)
  {
    removeEntityFromSystem(entity);
    entityComponentSignatures[entity.getID()].reset();

    // TODO: agregar id a lista de ids libres
    freeIDs.push_back(entity.getID());
  }

  entitiesToBeAdded.clear();
  entitiesToBeKilled.clear();
}

void Registry::clearAllEntities()
{
  for (int i = 0; i < numEntities; i++)
  {
    removeEntityFromSystem(Entity(i));
    entityComponentSignatures[i].reset();
    freeIDs.push_back(i);
  }
}