/**
 * @file AnimationManager.hpp
 * @brief Manager for animation data and sprite frame information
 * 
 * Provides storage and retrieval of animation data including texture IDs,
 * frame dimensions, speed, and looping information.
 */

#ifndef ANIMATION_MANAGER_HPP
#define ANIMATION_MANAGER_HPP

#include <map>
#include <string>

/**
 * @struct AnimationData
 * @brief Stores information about an animation
 * 
 * Contains all the data needed to render and manage sprite animations,
 * including texture reference and frame parameters.
 */
struct AnimationData
{
  std::string textureId;  ///< ID of the texture containing the sprite sheet
  int width;              ///< Width of a single frame in pixels
  int height;             ///< Height of a single frame in pixels
  int numFrames;          ///< Total number of frames in the animation
  int fremeSpeedRate;     ///< Speed at which to advance frames (1 = every frame, 2 = every 2 frames, etc)
  bool isLoop;            ///< Whether the animation loops when finished

  /**
   * @brief Construct animation data with default values
   * 
   * @param textureId The texture ID (default: empty string)
   * @param width Frame width in pixels (default: 0)
   * @param height Frame height in pixels (default: 0)
   * @param numFrames Number of frames (default: 1)
   * @param fremeSpeedRate Frame speed rate (default: 1)
   * @param isLoop Whether to loop (default: true)
   */
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

/**
 * @class AnimationManager
 * @brief Manages animation data for sprites
 * 
 * Stores and retrieves animation data for all sprites in the game.
 * Uses a map to cache animation configurations by unique IDs.
 */
class AnimationManager
{
private:
  std::map<std::string, AnimationData> animations; ///< Cache of animation data

public:
  /**
   * @brief Construct a new AnimationManager
   */
  AnimationManager();
  
  /**
   * @brief Destroy the AnimationManager
   */
  ~AnimationManager();

  /**
   * @brief Add or register an animation
   * 
   * @param AnimationId A unique identifier for this animation
   * @param textureId The ID of the texture containing the sprite sheet
   * @param width Width of a single frame in pixels
   * @param height Height of a single frame in pixels
   * @param numFrames Total number of frames in the animation
   * @param fremeSpeedRate Speed at which to advance frames
   * @param isLoop Whether the animation should loop
   */
  void addAnimation(
      const std::string &AnimationId = "",
      const std::string &textureId = "",
      int width = 0,
      int height = 0,
      int numFrames = 1,
      int fremeSpeedRate = 1,
      bool isLoop = true //
  );

  /**
   * @brief Retrieve animation data by ID
   * 
   * @param AnimationId The unique identifier of the animation
   * @return AnimationData The animation data
   */
  AnimationData getAnimationData(const std::string &AnimationId);
};

#endif // ANIMATION_MANAGER_HPP