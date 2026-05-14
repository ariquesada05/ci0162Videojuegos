/**
 * @file RenderDamageColliderSystem.hpp
 * @brief Debug damage collider visualization system
 */

#ifndef RENDERDAMAGECOLLIDER_SYSTEM_HPP
#define RENDERDAMAGECOLLIDER_SYSTEM_HPP

#include <SDL2/SDL.h>
#include "../Components/damageColliderComponent.hpp"
#include "../Components/TransformComponent.hpp"
#include "../ECS/ECS.hpp"

/**
 * @class RenderDamageColliderSystem
 * @brief Renders damage colliders for debugging
 */
class RenderDamageColliderSystem : public System {
public:
    /**
     * @brief Construct a RenderDamageColliderSystem
     */
    RenderDamageColliderSystem() {
        requireComponent<DamageColliderComponent>();
        requireComponent<TransformComponent>();
    }

    /**
     * @brief Render all damage colliders
     * @param renderer The SDL renderer
     * @param camera The camera viewport
     */
    void Update(SDL_Renderer* renderer, SDL_Rect& camera) {
        for (auto entity : getEntities()) {
            const auto& collider = entity.getComponent<DamageColliderComponent>();
            const auto& transform = entity.getComponent<TransformComponent>();

            SDL_Rect box = {
                static_cast<int>(transform.position.x - camera.x) - 4,
                static_cast<int>(transform.position.y - camera.y) - 4,
                static_cast<int>(collider.Width) + 8,
                static_cast<int>(collider.Height) + 8
            };

            SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
            SDL_RenderDrawRect(renderer, &box);
        }
    }
};

#endif 