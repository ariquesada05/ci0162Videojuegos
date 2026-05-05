#include "AnimationManager.hpp"

AnimationManager::AnimationManager()
{
}

AnimationManager::~AnimationManager()
{
}

void AnimationManager::addAnimation(
    const std::string &AnimationId,
    const std::string &textureId,
    int width,
    int height,
    int numFrames,
    int fremeSpeedRate,
    bool isLoop)
{
  auto animationData = AnimationData(textureId, width, height, numFrames, fremeSpeedRate, isLoop);
  animations[AnimationId] = animationData;
}

AnimationData AnimationManager::getAnimationData(const std::string &AnimationId)
{
  return animations[AnimationId];
}