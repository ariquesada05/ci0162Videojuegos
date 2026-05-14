/**
 * @file AttackCycleComponent.hpp
 * @brief Attack sequencing component for enemies
 */

#ifndef ATTACKCYCLECOMPONENT_HPP
#define ATTACKCYCLECOMPONENT_HPP

#include <string>
#include <vector>

/**
 * @struct Attack
 * @brief Defines a single attack in an attack cycle
 * 
 * Represents a specific attack with awareness range for enemies.
 */
struct Attack {
    std::string Name;                      ///< Name identifier for the attack
    std::pair<size_t, size_t> AwarenessX;  ///< Horizontal awareness range (min, max)

    /**
     * @brief Construct an Attack
     * @param name The attack name
     * @param awareness The awareness range as (min, max) pair
     */
    Attack(const std::string& name,
           const std::pair<size_t, size_t>& awareness)
        : Name(name), AwarenessX(awareness) {}
};

/**
 * @struct AttackCycleComponent
 * @brief Manages enemy attack sequences
 * 
 * Cycles through a sequence of attacks, tracking the current attack
 * and managing attack transitions.
 */
struct AttackCycleComponent {
    std::string ProjectileScriptPath; ///< Path to the projectile script
    double RangeDistance = 0;         ///< Maximum attack range distance
    std::vector<Attack> Attacks {};   ///< List of attacks in the cycle
    size_t CurrentAttack = 0;         ///< Index of the current attack

    /**
     * @brief Get the next attack in the cycle
     * @return Attack The current attack
     */
    Attack GetNextAttack() {
        return Attacks[CurrentAttack];
    }

    /**
     * @brief Perform the current attack and advance to the next
     */
    void PerformAttack() {
        CurrentAttack++;

        if (CurrentAttack >= Attacks.size())
            CurrentAttack = 0;
    }
};

#endif