
#ifndef ENEMYCOLLIDER_SYSTEM_HPP
#define ENEMYCOLLIDER_SYSTEM_HPP

#include <sol/sol.hpp>
#include <SDL2/SDL.h>
#include "../Components/ScriptComponent.hpp"
#include "../ECS/ECS.hpp"
#include "../Components/TransformComponent.hpp"
#include "../Components/EnemyColliderComponent.hpp"
#include "../Components/TagComponent.hpp"
#include "../EventManager/EventManager.hpp"

class EnemyColliderSystem : public System
{

    struct CollisionInfo
    {
        float X;
        float Y;
        float Width;
        float Height;
    };
public:
    EnemyColliderSystem() {
        this->requireComponent<EnemyColliderComponent>();
        requireComponent<TransformComponent>();
        requireComponent<TagComponent>();
    }


    void Update(const std::unique_ptr<EventManager>& eventManager, sol::state& lua) {
        auto entities = getEntities();

        for (auto i = entities.begin(); i != entities.end(); ++i) {
            Entity entity = *i;

            const auto& entityCollider = entity.getComponent<EnemyColliderComponent>();
            const auto& entityTransform = entity.getComponent<TransformComponent>();

            for (auto j = i + 1; j != entities.end(); ++j) {
                Entity otherEntity = *j;
                const auto& otherCollider = otherEntity.getComponent<EnemyColliderComponent>();
                const auto& otherTransform = otherEntity.getComponent<TransformComponent>();


                const bool thereIsCollision = EnemyColliderSystem::CheckCollision(
                    {
                        entityTransform.position.x, 
                        entityTransform.position.y,
                        entityCollider.width, 
                        entityCollider.height},
                    {
                        otherTransform.position.x,
                        otherTransform.position.y,
                        otherCollider.width,
                        otherCollider.height
                    }
                );

                if (thereIsCollision) {
                    
                    if(entity.hasComponent<ScriptComponent>()) {
                        const auto& script = entity.getComponent<ScriptComponent>();
                        if(script.onCollision != sol::nil) {
                            lua["this"] = entity;
                            script.onCollision(otherEntity);
                        }
                    }
                    if(otherEntity.hasComponent<ScriptComponent>()) {
                        const auto& script = otherEntity.getComponent<ScriptComponent>();
                        if(script.onCollision != sol::nil) {
                            lua["this"] = otherEntity;
                            script.onCollision(entity);
                        }
                    }
                    }
                }
            }

           // eventManager->EmitEvent<CollisionEvent>(tag.tag, collisionInfo);
    }

    static bool CheckCollision(const CollisionInfo& a, const CollisionInfo& b) {
        return (a.X < b.X + b.Width &&
                a.X + a.Width > b.X &&
                a.Y < b.Y + b.Height &&
                a.Y + a.Height > b.Y);
    }
};

#endif