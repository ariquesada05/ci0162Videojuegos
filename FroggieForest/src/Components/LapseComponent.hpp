
/**
 * @file LapseComponent.hpp
 * @brief Action cooldown and timing component
 */

#ifndef LAPSE_COMPONENT_HPP
#define LAPSE_COMPONENT_HPP

#include <map>
#include <string>
#include <optional>

/**
 * @struct TimingTracer
 * @brief Tracks timing for cooldowns
 * 
 * Maintains a counter and time limit for action cooldown management.
 */
struct TimingTracer {
    double Counter = 0;     ///< Current counter value
    double TimeLimit = 0;   ///< Maximum time limit
};

/**
 * @struct LapseComponent
 * @brief Manages action cooldowns and timing
 * 
 * Tracks global cooldown and per-action cooldowns to prevent spamming
 * of actions and enforce timing between actions.
 */
struct LapseComponent {
    TimingTracer Global;                          ///< Global action cooldown
    std::map<std::string, TimingTracer> PlayerActions;  ///< Per-action cooldowns
    std::string LastPerformed;                    ///< Name of the last action performed
    std::optional<TimingTracer> GlobalBuffer;     ///< Optional buffer for global timing

    /**
     * @brief Mark an action as performed (reset its cooldown)
     * @param actionName The name of the action to perform
     */
    void PerformAction(const std::string& actionName) {
        Global.Counter = 0;

        LastPerformed = actionName;

        if (actionName.empty() || PlayerActions.find(actionName) == PlayerActions.end()) {
            return;
        }

        auto&[Counter, TimeLimit] = PlayerActions.at(actionName);
        Counter = 0;
    }

    /**
     * @brief Check if an action can be performed (cooldown has expired)
     * @param actionName The name of the action to check
     * @return bool True if the action can be performed
     */
    bool CanPerformAction(const std::string& actionName) const
    {
    const bool globalCan =
        Global.Counter < 0 ||
        Global.Counter > Global.TimeLimit;

    if (actionName.empty()) {
        return globalCan;
    }

    if (PlayerActions.find(actionName) ==
        PlayerActions.end())
    {
        return false;
    }

    return globalCan &&
           (
             PlayerActions.at(actionName).Counter < 0 ||
             PlayerActions.at(actionName).Counter >
             PlayerActions.at(actionName).TimeLimit
           );
}
};

#endif //LAPSE_COMPONENT_HPP
