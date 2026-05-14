/**
 * @file animationSystem.hpp
 * @brief Sprite animation system
 * 
 * Updates animation frames for all entities with animations.
 */

#ifndef ANIMATIONSYSTEM_HPP
#define ANIMATIONSYSTEM_HPP

#include "../Components/AnimationComponent.hpp"
#include "../Components/SpriteComponent.hpp"
#include "../ECS/ECS.hpp"

/**
 * @class AnimationSystem
 * @brief Updates animations for all entities
 * 
 * Processes all entities with AnimationComponent and SpriteComponent,
 * updating the current frame based on elapsed time.
 */
class AnimationSystem : public System
{
public:
  /**
   * @brief Construct an AnimationSystem
   */
  AnimationSystem()
  {
    requireComponent<AnimationComponent>();
    requireComponent<SpriteComponent>();
  }

  /**
   * @brief Update all animations
   */
  void update()
  {
    for (auto &entity : getEntities())
    {
      auto &animation = entity.getComponent<AnimationComponent>();
      auto &sprite = entity.getComponent<SpriteComponent>();

      animation.currentFrame = ((SDL_GetTicks() - animation.startTime) * animation.frameTime / 1000) % animation.numFrames;

      sprite.srcRect.x = sprite.width * animation.currentFrame;
    }
  }
};

#endif // ANIMATIONSYSTEM_HPP