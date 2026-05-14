/**
 * @file AnimationComponent.hpp
 * @brief Animation state component
 */

#ifndef ANIMATIONCOMPONENT_HPP
#define ANIMATIONCOMPONENT_HPP

#include <SDL2/SDL.h>

/**
 * @struct AnimationComponent
 * @brief Stores animation state and timing data
 * 
 * Tracks the current animation frame, total frame count, and timing
 * information for sprite animations.
 */
struct AnimationComponent
{
  int numFrames;    ///< Total number of frames in this animation
  int currentFrame; ///< Index of the current frame being displayed
  int frameTime;    ///< Time in milliseconds to show each frame
  bool isLooping;   ///< Whether the animation loops when it reaches the end
  int startTime;    ///< SDL tick time when this animation started

  /**
   * @brief Construct an AnimationComponent
   * @param numFrames The total number of frames (default: 1)
   * @param frameTime Duration of each frame in milliseconds (default: 1)
   * @param isLooping Whether to loop the animation (default: true)
   */
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