/**
 * @file Collision.hpp
 * @brief Collision detection utilities
 * 
 * Provides collision detection and related data structures.
 */

#ifndef COLLISION_HPP
#define COLLISION_HPP

#include <cstdint>

/**
 * @struct Collision
 * @brief Axis-aligned bounding box collision data
 */
struct Collision {
    float X;       ///< X position
    float Y;       ///< Y position
    float Width;   ///< Width
    float Height;  ///< Height    
};

/**
 * @brief Check AABB collision between two bounding boxes
 * @param a First collision box
 * @param b Second collision box
 * @return bool True if boxes collide
 */
static bool checkCollision(const Collision& a, const Collision& b) {
    return (
        a.X < b.X + b.Width &&
        a.X + a.Width > b.X &&
        a.Y < b.Y + b.Height &&
        a.Y + a.Height > b.Y
    );
}

#endif // COLLISION_HPP
