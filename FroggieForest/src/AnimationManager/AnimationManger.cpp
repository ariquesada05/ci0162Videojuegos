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
    bool isLoop,
    int offsetX)
{
  auto animationData = AnimationData(textureId, width, height, numFrames, fremeSpeedRate, isLoop, offsetX);
  animations[AnimationId] = animationData;
}

AnimationData AnimationManager::getAnimationData(const std::string &AnimationId)
{
  return animations[AnimationId];
}