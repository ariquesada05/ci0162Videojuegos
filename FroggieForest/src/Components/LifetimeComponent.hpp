
#ifndef LIFETIMECOMPONENT_HPP
#define LIFETIMECOMPONENT_HPP

#include <variant>
#include <functional>

#include "../ECS/ECS.hpp"


struct IComponentToErase {
    virtual ~IComponentToErase() = default;
    virtual void RemoveComponent(Entity& entity) = 0;
};



template<typename TComponent>
struct ComponentToErase final : public IComponentToErase {
    void RemoveComponent(Entity& entity) override {
        entity.removeComponent<TComponent>();
    }
};

struct Nothing {
};


struct LifetimeComponent {
    float TicksAlive = 0;

    std::variant<std::shared_ptr<IComponentToErase>
        , std::function<void(const Entity&)>
        , Nothing> Action
    = Nothing();

    explicit LifetimeComponent(const float ticksAlive = 0) : TicksAlive(ticksAlive) {};

    LifetimeComponent& operator -= (const float amount) {
        TicksAlive -= amount;
        return *this;
    }

    [[nodiscard]] bool IsAlive() const {
        return TicksAlive >= 0;
    }
};

#endif 
