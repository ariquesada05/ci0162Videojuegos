
#ifndef LAPSE_COMPONENT_HPP
#define LAPSE_COMPONENT_HPP

#include <map>
#include <string>
#include <optional>


struct TimingTracer {
    double Counter = 0;
    double TimeLimit = 0;
};

struct LapseComponent {
    TimingTracer Global;
    std::map<std::string, TimingTracer> PlayerActions; 
    std::string LastPerformed;

    std::optional<TimingTracer> GlobalBuffer;

    void PerformAction(const std::string& actionName) {
        Global.Counter = 0;

        LastPerformed = actionName;

        if (actionName.empty() || PlayerActions.find(actionName) == PlayerActions.end()) {
            return;
        }

        auto&[Counter, TimeLimit] = PlayerActions.at(actionName);
        Counter = 0;
    }

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
