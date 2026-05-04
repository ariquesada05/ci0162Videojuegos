#ifndef CIIRCLE_COLIDER_COMPONENT_HPP
#define CIIRCLE_COLIDER_COMPONENT_HPP

struct CircleColiderComponent
{
  int radius;
  int width;
  int height;

  CircleColiderComponent(int radius = 0, int width = 0, int height = 0)
  {
    this->radius = radius;
    this->width = width;
    this->height = height;
  }
};

#endif // CIIRCLE_COLIDER_COMPONENT_HPP