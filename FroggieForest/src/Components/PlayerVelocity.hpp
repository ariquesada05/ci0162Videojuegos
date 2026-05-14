/**
 * @file PlayerVelocity.hpp
 * @brief Player-specific velocity component
 */

#ifndef PLAYERVELOCITY_HPP
#define PLAYERVELOCITY_HPP

/**
 * @struct PlayerVelocity
 * @brief Stores player movement speed
 * 
 * Component specifically for player entity movement speed.
 */
struct PlayerVelocity
{
  int playerVelocity; ///< Player movement speed in pixels per frame

  /**
   * @brief Construct a PlayerVelocity
   * @param playerVelocity The movement speed (default: 0)
   */
  PlayerVelocity(int playerVelocity = 0) {
    this->playerVelocity = playerVelocity;
  }
 
};

#endif