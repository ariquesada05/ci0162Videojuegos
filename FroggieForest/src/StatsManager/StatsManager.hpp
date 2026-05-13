#ifndef STATS_MANAGER_HPP
#define STATS_MANAGER_HPP

#include <string>
#include <unordered_map>
#include <optional>

#include "../components/StatsComponent.hpp"
#include "../ECS/ECS.hpp"

class StatsManager {
    std::unordered_map<std::string, StatsComponent> tagToStat {};

    StatsManager() = default;
public:
    static StatsManager& GetInstance();

   
    void AddStat(const std::string& tag, const StatsComponent& stat);

   
    void AddStatsToEntity(Entity &entity);

   
    void Clear();

  
    std::optional<StatsComponent> operator[](const std::string& tag) const;
};



#endif //STATS_MANAGER_HPP
