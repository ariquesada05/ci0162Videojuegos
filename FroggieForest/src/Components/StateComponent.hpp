/**
 * @file StateComponent.hpp
 * @brief Entity state management component
 */

#ifndef STATECOMPONENT_HPP
#define STATECOMPONENT_HPP

#include <cstdint>

/**
 * @struct StateComponent
 * @brief Tracks entity state transitions
 * 
 * Stores the current state and the next state for state machine behavior.
 */
struct StateComponent {
  int8_t state;     ///< Current state ID
  int8_t nextState; ///< Next state ID (for state transitions)

  /**
   * @brief Construct a StateComponent
   * @param initialState The initial state ID (default: 1)
   */
  explicit StateComponent(const int8_t initialState = 1)
      : state(initialState), nextState(initialState) {}
};

#endif // STATECOMPONENT_HPP