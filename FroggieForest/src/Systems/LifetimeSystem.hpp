/**
 * @file LifetimeSystem.hpp
 * @brief Entity lifetime management system
 */

#ifndef LIFETIME_SYSTEM_HPP
#define LIFETIME_SYSTEM_HPP

#include "../ECS/ECS.hpp"
#include "../Components/LifetimeComponent.hpp"

/**
 * @brief Overload pattern for variant visiting
 */
template<class... Ts> struct overloaded : Ts... { using Ts::operator()...; };
template<class... Ts> overloaded(Ts...) -> overloaded<Ts...>;

/**
 * @brief Manage entity lifetime and perform expiration actions
 * @param lifetimeComponent The lifetime component
 * @param entity The entity to manage
 */
inline void manageLifetime(LifetimeComponent& lifetimeComponent, Entity& entity);

/**
 * @class LifetimeSystem
 * @brief Manages entity lifetimes and expiration
 * 
 * Tracks entity lifetimes and performs configured actions when
 * entities expire.
 */
class LifetimeSystem : public System {
public:
    /**
     * @brief Construct a LifetimeSystem
     */
    LifetimeSystem() {
        this->requireComponent<LifetimeComponent>();
    }

    /**
     * @brief Update entity lifetimes
     * @param deltaTime Time elapsed since last frame in seconds
     */
    void update(const float deltaTime) {
        for (auto& entity : this->getEntities()) {
            auto& lifetimeComponent = entity.getComponent<LifetimeComponent>();

            lifetimeComponent -= deltaTime;

            if (!lifetimeComponent.IsAlive()) {
                manageLifetime(lifetimeComponent, entity);
            }
        }
    }
};


inline void manageLifetime(LifetimeComponent& lifetimeComponent, Entity& entity) {
    std::visit( overloaded {
        [&](Nothing) { entity.Kill(); },
        [&](const std::shared_ptr<IComponentToErase>& componentToErase) {
            if (componentToErase) componentToErase->RemoveComponent(entity);
        },
        [&](const std::function<void(const Entity&)>& action) { action(entity); }
    }, lifetimeComponent.Action);
}

#endif //LIFETIME_SYSTEM_HPP
