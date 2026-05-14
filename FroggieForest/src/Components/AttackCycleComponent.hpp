#ifndef ATTACKCYCLECOMPONENT_HPP
#define ATTACKCYCLECOMPONENT_HPP

#include <string>
#include <vector>

struct Attack {
    std::string Name;
    std::pair<size_t, size_t> AwarenessX;

    Attack(const std::string& name,
           const std::pair<size_t, size_t>& awareness)
        : Name(name), AwarenessX(awareness) {}
};

struct AttackCycleComponent {
    std::string ProjectileScriptPath;
    double RangeDistance = 0;
    std::vector<Attack> Attacks {};
    size_t CurrentAttack = 0;

    Attack GetNextAttack() {
        return Attacks[CurrentAttack];
    }

    void PerformAttack() {
        CurrentAttack++;

        if (CurrentAttack >= Attacks.size())
            CurrentAttack = 0;
    }
};

#endif