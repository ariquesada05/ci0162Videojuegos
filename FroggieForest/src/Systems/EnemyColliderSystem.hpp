/**
 * @file EnemyColliderSystem.hpp
 * @brief Enemy collision management system
 */

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
#include "../Components/BoxColliderComponent.hpp"

/**
 * @class EnemyColliderSystem
 * @brief Manages enemy collision detection
 */
class EnemyColliderSystem : public System
{

    /**
     * @struct CollisionInfo
     * @brief Stores collision bounds information
     */
    struct CollisionInfo
    {
        float X;      ///< X position
        float Y;      ///< Y position
        float Width;  ///< Width
        float Height; ///< Height
    };
public:
    /**
     * @brief Construct an EnemyColliderSystem
     */
    EnemyColliderSystem() {
        requireComponent<EnemyColliderComponent>();
        requireComponent<TransformComponent>();
        requireComponent<TagComponent>();
    }


   void Update(sol::state& lua) {

    auto entities = getEntities();

    for (auto i = entities.begin(); i != entities.end(); ++i) {
        Entity entity = *i;

        const auto& entityCollider =
            entity.getComponent<EnemyColliderComponent>();

        const auto& entityTransform =
            entity.getComponent<TransformComponent>();

        // recorrer TODAS las entidades del juego
        for (auto j = entities.begin(); j != entities.end(); ++j) {
            Entity otherEntity = *j;

            if (entity == otherEntity)
                continue;

            if (!otherEntity.hasComponent<BoxColliderComponent>())
                continue;

            const auto& otherCollider =
                otherEntity.getComponent<BoxColliderComponent>();

            const auto& otherTransform =
                otherEntity.getComponent<TransformComponent>();

                    CollisionInfo a {
                        entityTransform.position.x,
                        entityTransform.position.y - entityCollider.height, // ajustar la posición Y para que el collider esté debajo de la entidad
                        (float)entityCollider.width,
                        (float)entityCollider.height
                    };

                    CollisionInfo b {
                        otherTransform.position.x,
                        otherTransform.position.y,
                        (float)otherCollider.width,
                        (float)otherCollider.height
                    };

                    bool thereIsCollision = CheckCollision(a, b);                   


            if (thereIsCollision) {

                if(entity.hasComponent<ScriptComponent>()) {

                    const auto& script =
                        entity.getComponent<ScriptComponent>();

                    if(script.onCollision != sol::nil) {

                        lua["this"] = entity;
                        script.onCollision(otherEntity);
                    }
                }
                if(otherEntity.hasComponent<ScriptComponent>()) {
             

                    const auto& script =
                        otherEntity.getComponent<ScriptComponent>();

                    if(script.onCollision != sol::nil) {

                        lua["this"] = otherEntity;
                        script.onCollision(entity);
                    }
                }
            }
        }
    }
}

    static bool CheckCollision(const CollisionInfo& a, const CollisionInfo& b) {
        return (a.X < b.X + b.Width &&
                a.X + a.Width > b.X &&
                a.Y < b.Y + b.Height &&
                a.Y + a.Height > b.Y);
    }
};

#endif