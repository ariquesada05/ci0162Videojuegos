
/**
 * @file LifetimeComponent.hpp
 * @brief Entity lifetime and expiration component
 */

#ifndef LIFETIMECOMPONENT_HPP
#define LIFETIMECOMPONENT_HPP

#include <variant>
#include <functional>

#include "../ECS/ECS.hpp"

/**
 * @struct IComponentToErase
 * @brief Interface for component removal actions
 * 
 * Defines the interface for removing a component from an entity.
 */
struct IComponentToErase {
    /**
     * @brief Destroy the IComponentToErase
     */
    virtual ~IComponentToErase() = default;
    
    /**
     * @brief Remove a component from an entity
     * @param entity The entity to remove the component from
     */
    virtual void RemoveComponent(Entity& entity) = 0;
};

/**
 * @struct ComponentToErase
 * @brief Template implementation for component removal
 * 
 * @tparam TComponent The type of component to remove
 */
template<typename TComponent>
struct ComponentToErase final : public IComponentToErase {
    /**
     * @brief Remove the component from an entity
     * @param entity The entity to remove the component from
     */
    void RemoveComponent(Entity& entity) override {
        entity.removeComponent<TComponent>();
    }
};

/**
 * @struct Nothing
 * @brief Sentinel value for no action
 */
struct Nothing {
};

/**
 * @struct LifetimeComponent
 * @brief Manages entity lifetime and expiration behavior
 * 
 * Tracks how long an entity has been alive and can perform actions
 * when the entity expires (remove a component or execute a callback).
 */
struct LifetimeComponent {
    float TicksAlive = 0; ///< Time in ticks that the entity has been alive

    /**
     * @brief Action to perform when entity expires
     * 
     * Can be:
     * - A shared pointer to a component remover
     * - A callback function
     * - Nothing (no action)
     */
    std::variant<std::shared_ptr<IComponentToErase>
        , std::function<void(const Entity&)>
        , Nothing> Action
    = Nothing();

    /**
     * @brief Construct a LifetimeComponent
     * @param ticksAlive The lifetime in ticks (default: 0)
     */
    explicit LifetimeComponent(const float ticksAlive = 0) : TicksAlive(ticksAlive) {};

    /**
     * @brief Decrease the lifetime
     * @param amount The amount of ticks to subtract
     * @return LifetimeComponent& Reference to this component
     */
    LifetimeComponent& operator -= (const float amount) {
        TicksAlive -= amount;
        return *this;
    }

    /**
     * @brief Check if the entity is still alive
     * @return bool True if TicksAlive >= 0
     */
    [[nodiscard]] bool IsAlive() const {
        return TicksAlive >= 0;
    }
};

#endif 
