/**
 * @file StatsManager.hpp
 * @brief Game statistics manager
 * 
 * Manages entity statistics (health, damage, points) per entity tag.
 */

#ifndef STATS_MANAGER_HPP
#define STATS_MANAGER_HPP

#include <string>
#include <unordered_map>
#include <optional>

#include "../components/StatsComponent.hpp"
#include "../ECS/ECS.hpp"

/**
 * @class StatsManager
 * @brief Singleton manager for entity statistics
 * 
 * Maintains a mapping of entity tags to their statistics (health, damage, points),
 * providing centralized stat management and retrieval.
 */
class StatsManager {
    /**
     * @brief Map of entity tags to their statistics
     */
    std::unordered_map<std::string, StatsComponent> tagToStat {};

    /**
     * @brief Construct a StatsManager
     */
    StatsManager() = default;
public:
    /**
     * @brief Get singleton instance
     * @return StatsManager& Reference to singleton
     */
    static StatsManager& GetInstance();

    /**
     * @brief Add statistics for an entity tag
     * @param tag Entity tag identifier
     * @param stat Statistics component
     */
    void AddStat(const std::string& tag, const StatsComponent& stat);

    /**
     * @brief Add stored stats to an entity
     * @param entity The entity to add stats to
     */
    void AddStatsToEntity(Entity &entity);

    /**
     * @brief Clear all stored statistics
     */
    void Clear();

    /**
     * @brief Get stats for a tag
     * @param tag Entity tag to look up
     * @return std::optional<StatsComponent> Stats if found, empty otherwise
     */
    std::optional<StatsComponent> operator[](const std::string& tag) const;
};

#endif //STATS_MANAGER_HPP
