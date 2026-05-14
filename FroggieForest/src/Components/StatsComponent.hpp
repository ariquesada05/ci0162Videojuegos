/**
 * @file StatsComponent.hpp
 * @brief Game statistics component
 */

#ifndef STATS_COMPONENT_HPP
#define STATS_COMPONENT_HPP

/**
 * @struct StatsComponent
 * @brief Stores game statistics for entities
 * 
 * Tracks health, points, and damage values for game entities.
 */
struct StatsComponent
{
    int Health; ///< Current health value
    int Points; ///< Current points/score value
    int Damage; ///< Damage value (for attacks)

    /**
     * @brief Construct a StatsComponent
     * @param health Initial health (default: 0)
     * @param points Initial points (default: 0)
     * @param damage Initial damage (default: 0)
     */
    StatsComponent(
        int health = 0,
        int points = 0,
        int damage = 0)
    {
        Health = health;
        Points = points;
        Damage = damage;
    }
};

#endif