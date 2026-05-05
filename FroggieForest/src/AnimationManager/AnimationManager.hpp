#ifndef ANIMATION_MANAGER_HPP
#define ANIMATION_MANAGER_HPP

#include <map>
#include <string>

struct AnimationData
{
  std::string textureId;
  int width;
  int height;
  int numFrames;
  int fremeSpeedRate;
  bool isLoop;

  AnimationData(
      const std::string &textureId = "",
      int width = 0,
      int height = 0,
      int numFrames = 1,
      int fremeSpeedRate = 1,
      bool isLoop = true //
  )
  {
    this->textureId = textureId;
    this->width = width;
    this->height = height;
    this->numFrames = numFrames;
    this->fremeSpeedRate = fremeSpeedRate;
    this->isLoop = isLoop;
  }
};

class AnimationManager
{
private:
  std::map<std::string, AnimationData> animations;

public:
  AnimationManager();
  ~AnimationManager();

  void addAnimation(
      const std::string &AnimationId = "",
      const std::string &textureId = "",
      int width = 0,
      int height = 0,
      int numFrames = 1,
      int fremeSpeedRate = 1,
      bool isLoop = true //
  );

  AnimationData getAnimationData(const std::string &AnimationId);
};

#endif // ANIMATION_MANAGER_HPP