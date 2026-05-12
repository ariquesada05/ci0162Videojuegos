#ifndef ENEMYCOLLIDERCOMPONENT_HPP
#define ENEMYCOLLIDERCOMPONENT_HPP

#include <glm/glm.hpp>


struct EnemyColliderComponent
{
  float width;
  float height;

  EnemyColliderComponent(int width = 0, int height = 0){
    this->width = width;
    this->height = height;
  }
};

#endif // ENEMYCOLLIDERCOMPONENT_HPP