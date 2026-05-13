
#ifndef LIFETIME_SYSTEM_HPP
#define LIFETIME_SYSTEM_HPP

#include "../ECS/ECS.hpp"
#include "../Components/LifetimeComponent.hpp"

template<class... Ts> struct overloaded : Ts... { using Ts::operator()...; };
template<class... Ts> overloaded(Ts...) -> overloaded<Ts...>;

inline void manageLifetime(LifetimeComponent& lifetimeComponent, Entity& entity);

class LifetimeSystem : public System {
public:
    LifetimeSystem() {
        this->requireComponent<LifetimeComponent>();
    }

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
