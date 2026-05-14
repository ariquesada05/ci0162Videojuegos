/**
 * @file CameraFollowComponent.hpp
 * @brief Camera tracking component
 */

#ifndef CAMERA_FOLLOW_COMPONENT_HPP
#define CAMERA_FOLLOW_COMPONENT_HPP

/**
 * @struct CameraFollowComponent
 * @brief Marks an entity as the camera follow target
 * 
 * An entity with this component will be tracked by the camera.
 * Typically used for the player character.
 */
struct CameraFollowComponent
{
  /**
   * @brief Construct a CameraFollowComponent
   */
  CameraFollowComponent() {}
};

#endif // CAMERA_FOLLOW_COMPONENT_HPP