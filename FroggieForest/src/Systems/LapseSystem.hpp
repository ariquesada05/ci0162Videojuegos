
#ifndef LAPSE_SYSTEM_HPP
#define LAPSE_SYSTEM_HPP

#include "../ECS/ECS.hpp"
#include "../Components/LapseComponent.hpp"

class LapseSystem : public System {
public:
    LapseSystem() {
        this->requireComponent<LapseComponent>();
    }

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
