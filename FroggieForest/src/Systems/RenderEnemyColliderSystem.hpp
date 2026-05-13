#ifndef RENDERENEMYCOLLIDERSYSTEM_HPP
#define RENDERENEMYCOLLIDERSYSTEM_HPP

#include <SDL2/SDL.h>
#include "../Components/ScriptComponent.hpp"
#include "../ECS/ECS.hpp"
#include "../Components/TransformComponent.hpp"
#include "../Components/EnemyColliderComponent.hpp"
#include "../Components/TagComponent.hpp"
#include "../EventManager/EventManager.hpp"


class RenderEnemyColliderSystem : public System
{
public:

    RenderEnemyColliderSystem() {
        requireComponent<EnemyColliderComponent>();
        requireComponent<TransformComponent>();
    }
    void Update(SDL_Renderer* renderer, SDL_Rect& camera) {
        for (auto& entity : getEntities()) {
            auto& collider = entity.getComponent<EnemyColliderComponent>();
            const auto& transform = entity.getComponent<TransformComponent>();

            SDL_Rect rect = {
                static_cast<int>(transform.position.x - camera.x) - 8,
                static_cast<int>(transform.position.y - camera.y) - 8,
                static_cast<int>(collider.width),
                static_cast<int>(collider.height)
            };

            SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255); // Blue color for enemy colliders
            SDL_RenderDrawRect(renderer, &rect);
        }
    }
};

#endif
