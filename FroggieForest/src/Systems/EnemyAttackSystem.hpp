#ifndef ENEMYATTACKSYSTEM_HPP
#define ENEMYATTACKSYSTEM_HPP

#include <sol/sol.hpp>
#include <algorithm>
#include <stdexcept>

#include "../ECS/ECS.hpp"

#include "../Components/ScriptComponent.hpp"
#include "../Components/LapseComponent.hpp"
#include "../Components/DamageColliderComponent.hpp"
#include "../Components/AttackCycleComponent.hpp"
#include "../Components/TransformComponent.hpp"
#include "../Components/TagComponent.hpp"

#include "../Utils/Collision.hpp"

class EnemyAttackSystem : public System {
public:
    EnemyAttackSystem() {
        requireComponent<DamageColliderComponent>();
        requireComponent<LapseComponent>();
        requireComponent<ScriptComponent>();
        requireComponent<AttackCycleComponent>();
        requireComponent<TransformComponent>();
        requireComponent<TagComponent>();
    }

    void update(sol::state& lua) {

        Entity* player = nullptr;

        // Buscar jugador
        for (auto& current : getEntities()) {

            auto& tag = current.getComponent<TagComponent>();

            if (tag.tag == "player") {
                player = &current;
                break;
            }
        }

        if (player == nullptr) {
            std::cerr << "[EnemyAttackSystem] No player found\n";
            return;
        }

        // Verificar componentes del jugador
        if (!player->hasComponent<DamageColliderComponent>() ||
            !player->hasComponent<TransformComponent>()) {
            return;
        }

        auto& playerCollider =
            player->getComponent<DamageColliderComponent>();

        auto& playerTransform =
            player->getComponent<TransformComponent>();


        // Procesar enemigos
        for (auto& entity : getEntities()) {

            auto& tag = entity.getComponent<TagComponent>();

            // Saltarse jugador
            if (tag.tag == "player")
                continue;

            auto& lapses =
                entity.getComponent<LapseComponent>();

            auto& attackCycle =
                entity.getComponent<AttackCycleComponent>();

            if (attackCycle.Attacks.empty())
                continue;

            if (!lapses.CanPerformAction(""))
                continue;

            auto currentAttack = attackCycle.GetNextAttack();

            const auto& attackName = currentAttack.Name;
            const auto& awareness = currentAttack.AwarenessX;

            if (!lapses.CanPerformAction(attackName))
                continue;

            auto& entityCollider =
                entity.getComponent<DamageColliderComponent>();

            auto& entityTransform =
                entity.getComponent<TransformComponent>();


            bool collision = checkCollision(
                {
                    playerTransform.position.x,
                    playerTransform.position.y,
                    static_cast<float>(playerCollider.Width),
                    static_cast<float>(playerCollider.Height)
                },

                {
                    entityTransform.position.x - awareness.first,
                    entityTransform.position.y - awareness.second,

                    static_cast<float>(
                        entityCollider.Width + awareness.first * 2
                    ),

                    static_cast<float>(
                        entityCollider.Height + awareness.second * 2
                    )
                }
            );

            if (!collision)
                continue;

            lapses.PerformAction(attackName);

            if (!entity.hasComponent<ScriptComponent>())
                continue;

            auto& script =
                entity.getComponent<ScriptComponent>();

            if (script.onPerform == sol::nil)
                continue;

            lua["this"] = entity;

            bool playerOnRight =
                playerTransform.position.x >
                entityTransform.position.x;

            script.onPerform(
                attackName,
                playerOnRight
            );

            attackCycle.PerformAttack();
        }
    }
};

#endif