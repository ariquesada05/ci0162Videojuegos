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
    int Width;   ///< Width of the damage collider in pixels
    int Height;  ///< Height of the damage collider in pixels
    int OffsetX; ///< Horizontal offset from the entity position (pixels)
    int OffsetY; ///< Vertical offset from the entity position (pixels)

    /**
     * @brief Construct a DamageColliderComponent
     * @param width The collider width (default: 0)
     * @param height The collider height (default: 0)
     * @param offsetX Horizontal offset from the entity position (default: 0)
     * @param offsetY Vertical offset from the entity position (default: 0)
     */
    DamageColliderComponent(
        int width = 0,
        int height = 0,
        int offsetX = 0,
        int offsetY = 0)
    {
        Width = width;
        Height = height;
        OffsetX = offsetX;
        OffsetY = offsetY;
    }
};

#endif