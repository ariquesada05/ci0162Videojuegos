#ifndef ANIMATIONCOMPONENT_HPP
#define ANIMATIONCOMPONENT_HPP

#include <SDL2/SDL.h>

struct AnimationComponent
{
  int numFrames;
  int currentFrame;
  int frameTime;
  bool isLooping;
  int startTime;

  AnimationComponent(int numFrames = 1, int frameTime = 1, bool isLooping = true)
  {
    this->numFrames = numFrames;
    this->frameTime = frameTime;
    this->isLooping = isLooping;
    this->currentFrame = 1;
    this->startTime = SDL_GetTicks();
  }
};

#endif // ANIMATIONCOMPONENT_HPP