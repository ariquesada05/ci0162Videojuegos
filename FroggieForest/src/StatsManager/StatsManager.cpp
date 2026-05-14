#include "StatsManager.hpp"
#include "../Components/TagComponent.hpp"

StatsManager &StatsManager::GetInstance()
{
    static StatsManager instance;
    return instance;
}

void StatsManager::AddStat(
    const std::string &tag,
    const StatsComponent &stat)
{


    tagToStat.insert({tag, stat});
}



void StatsManager::AddStatsToEntity(Entity &entity)
{
    if (!entity.hasComponent<TagComponent>())
    {
        std::cout << "ENTITY HAS NO TAG"
                  << std::endl;

        return;
    }

    const auto &tagComp =
        entity.getComponent<TagComponent>();

    const auto &tag = tagComp.tag;

    std::cout << "TRYING TO ADD STATS TO: "
              << tag
              << std::endl;

    auto it = tagToStat.find(tag);

    if (it == tagToStat.end())
    {
        std::cout << "NO STATS FOUND FOR TAG: "
                  << tag
                  << std::endl;

        return;
    }

    std::cout << "ADDING STATS COMPONENT TO ENTITY: "
              << entity.getID()
              << std::endl;

    entity.addComponent<StatsComponent>(it->second);
}

void StatsManager::Clear()
{
    tagToStat.clear();
}

std::optional<StatsComponent>
StatsManager::operator[](
    const std::string &tag) const
{
    auto it = tagToStat.find(tag);

    if (it == tagToStat.end())
    {
        return std::nullopt;
    }

    return it->second;
}