/**
 * @file DamageColliderComponent.hpp
 * @brief Damage dealing collision component
 */

#ifndef DAMAGE_COLLIDER_COMPONENT_HPP
#define DAMAGE_COLLIDER_COMPONENT_HPP

/**
 * @struct DamageColliderComponent
 * @brief Collider for dealing damage to other entities
 * 
 * Defines a collider area that deals damage when it collides with
 * other entities (typically for attacks or projectiles).
 */
struct DamageColliderComponent
{
    int Width;  ///< Width of the damage collider in pixels
    int Height; ///< Height of the damage collider in pixels

    /**
     * @brief Construct a DamageColliderComponent
     * @param width The collider width (default: 0)
     * @param height The collider height (default: 0)
     */
    DamageColliderComponent(
        int width = 0,
        int height = 0)
    {
        Width = width;
        Height = height;
    }
};

#endif