#include "StatsManager.hpp"
#include "../Components/TagComponent.hpp"

StatsManager &StatsManager::GetInstance() {
    static StatsManager instance;
    return instance;
}

void StatsManager::AddStat(const std::string &tag, const StatsComponent &stat) {
    tagToStat.insert({tag, stat});
}

void StatsManager::AddStatsToEntity(Entity &entity) {
    if (!entity.hasComponent<TagComponent>()) {
        return;
    }

    const auto& tagComp = entity.getComponent<TagComponent>();
    const auto& tag = tagComp.tag;

    auto it = tagToStat.find(tag);
    if (it == tagToStat.end()) {
        return;
    }

    entity.addComponent<StatsComponent>(it->second);
}

void StatsManager::Clear() {
    tagToStat.clear();
}

std::optional<StatsComponent> StatsManager::operator[](const std::string &tag) const {
    auto it = tagToStat.find(tag);
    if (it == tagToStat.end()) {
        return std::nullopt;
    }

    return it->second;
}