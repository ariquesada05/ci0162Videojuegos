#ifndef STATECOMPONENT_HPP
#define STATECOMPONENT_HPP


#include <cstdint>

struct StateComponent {
  explicit StateComponent(const int8_t initialState = 1)
      : state(initialState), nextState(initialState) {}
  int8_t state;
  int8_t nextState;
};



#endif // STATECOMPONENT_HPP