#ifndef ANIMATIONSYSTEM_HPP
#define ANIMATIONSYSTEM_HPP

#include "../Components/AnimationComponent.hpp"
#include "../Components/SpriteComponent.hpp"
#include "../ECS/ECS.hpp"

class AnimationSystem : public System
{
public:
  AnimationSystem()
  {
    requireComponent<AnimationComponent>();
    requireComponent<SpriteComponent>();
  }

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