#ifndef DAMAGE_COLLISION_SYSTEM_HPP
#define DAMAGE_COLLISION_SYSTEM_HPP

#include <sol/sol.hpp>

#include "../ECS/ECS.hpp"
#include "../Components/DamageColliderComponent.hpp"
#include "../Components/ScriptComponent.hpp"
#include "../Components/TransformComponent.hpp"
#include "../Components/TagComponent.hpp"
#include "../EventManager/EventManager.hpp"

#include "../Utils/Collision.hpp"

class DamageCollisionSystem : public System {
public:
    DamageCollisionSystem() {
        requireComponent<DamageColliderComponent>();
        requireComponent<TransformComponent>();
        requireComponent<TagComponent>();
    }

    void Update(sol::state& lua) {
        
        auto entities = getEntities();

        for (auto i = entities.begin(); i != entities.end(); ++i) {
            Entity a = *i;
            const auto& aCollider = a.getComponent<DamageColliderComponent>();
            const auto& aTransform = a.getComponent<TransformComponent>();

            for (auto j = i + 1; j != entities.end(); ++j) {
                Entity b = *j;
                const auto& bCollider = b.getComponent<DamageColliderComponent>();
                const auto& bTransform = b.getComponent<TransformComponent>();

                const bool collision = checkCollision(
                    {
                        aTransform.position.x,
                        aTransform.position.y,
                        static_cast<float>(aCollider.Width),
                        static_cast<float>(aCollider.Height)
                    },
                    {
                        bTransform.position.x,
                        bTransform.position.y,
                        static_cast<float>(bCollider.Width),
                        static_cast<float>(bCollider.Height)
                    });

                if (!collision) {
                    continue;
                }

                if (a.hasComponent<ScriptComponent>()) {
                    const auto& script = a.getComponent<ScriptComponent>();
                    if (script.onDamage != sol::nil) {
                        lua["this"] = a;
                        (void) script.onDamage(b);
                    }
                }

                if (b.hasComponent<ScriptComponent>()) {
                    const auto& script = b.getComponent<ScriptComponent>();

                    if (script.onDamage != sol::nil) {
                        lua["this"] = b;
                        (void) script.onDamage(a);
                    }
                }
            }
        }
    }
};

#endif 
