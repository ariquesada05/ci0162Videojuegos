/**
 * @file LapseSystem.hpp
 * @brief Action cooldown update system
 */

#ifndef LAPSE_SYSTEM_HPP
#define LAPSE_SYSTEM_HPP

#include "../ECS/ECS.hpp"
#include "../Components/LapseComponent.hpp"

/**
 * @class LapseSystem
 * @brief Updates action cooldown timers
 */
class LapseSystem : public System {
public:
    /**
     * @brief Construct a LapseSystem
     */
    LapseSystem() {
        this->requireComponent<LapseComponent>();
    }

    /**
     * @brief Update cooldown timers
     * @param deltaTime Time elapsed since last frame
     */
    void update(const double deltaTime) {
        for (auto& entity : this->getEntities()) {
            auto&[global, playerActions, lastPerformed, buffer] =
                entity.getComponent<LapseComponent>();

            for (auto& [name,action] : playerActions) {
                action.Counter += deltaTime;
                if ((action.Counter < 0 || action.Counter >= action.TimeLimit) && lastPerformed == name) {
                    lastPerformed = "";
                }
            }

            global.Counter += deltaTime;

            if ((global.Counter < 0 || global.Counter >= global.TimeLimit) && !lastPerformed.empty()) {
                lastPerformed = "";
            }
        }
    }
};

#endif 
