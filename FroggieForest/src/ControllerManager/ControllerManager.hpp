/**
 * @file ControllerManager.hpp
 * @brief Manager for input handling (keyboard and mouse)
 * 
 * Handles keyboard and mouse input events, maintaining state for actions
 * and mouse position.
 */

#ifndef CONTROLLER_MANAGER_HPP
#define CONTROLLER_MANAGER_HPP

#include <SDL2/SDL.h>

#include <map>
#include <string>

/**
 * @class ControllerManager
 * @brief Manages input events (keyboard and mouse)
 * 
 * Tracks the state of keyboard keys and mouse buttons, maps them to game actions,
 * and provides the current mouse position.
 */
class ControllerManager
{
private:
  std::map<std::string, int> actionKeyName;     ///< Mapping of action names to key codes
  std::map<int, bool> keyDown;                  ///< Current state of each key
  std::map<std::string, int> mouseButtonName;   ///< Mapping of action names to mouse buttons
  std::map<int, bool> mouseButtonDown;          ///< Current state of each mouse button

  int mousePosX = 0; ///< Current mouse X position
  int mousePosY = 0; ///< Current mouse Y position

public:
  /**
   * @brief Construct a new ControllerManager
   */
  ControllerManager();
  
  /**
   * @brief Destroy the ControllerManager
   */
  ~ControllerManager();

  /**
   * @brief Clear all input state
   */
  void Clear();

  // Keyboard methods
  
  /**
   * @brief Register a keyboard key for an action
   * @param action The name of the action
   * @param keyCode The SDL key code
   */
  void AddActionKey(const std::string &action, int keyCode);
  
  /**
   * @brief Called when a key is pressed
   * @param keyCode The SDL key code that was pressed
   */
  void KeyDown(int keyCode);
  
  /**
   * @brief Called when a key is released
   * @param keyCode The SDL key code that was released
   */
  void KeyUp(int keyCode);
  
  /**
   * @brief Check if an action is currently active
   * @param action The name of the action to check
   * @return bool True if the action's key is currently pressed
   */
  bool IsActionActivated(const std::string &action);

  // Mouse methods
  
  /**
   * @brief Register a mouse button for an action
   * @param action The name of the action
   * @param mouseButton The SDL mouse button constant
   */
  void AddMouseButton(const std::string &action, int mouseButton);
  
  /**
   * @brief Called when a mouse button is pressed
   * @param mouseButton The SDL mouse button constant
   */
  void MouseButtonDown(int mouseButton);
  
  /**
   * @brief Called when a mouse button is released
   * @param mouseButton The SDL mouse button constant
   */
  void MouseButtonUp(int mouseButton);
  
  /**
   * @brief Check if a mouse button action is currently active
   * @param action The name of the action to check
   * @return bool True if the action's mouse button is currently pressed
   */
  bool IsMouseButtonActivated(const std::string &action);

  /**
   * @brief Set the current mouse position
   * @param x The X coordinate
   * @param y The Y coordinate
   */
  void SetMousePos(int x, int y);
  
  /**
   * @brief Get the current mouse position
   * @return std::tuple<int, int> A tuple containing (x, y) coordinates
   */
  std::tuple<int, int> GetMousePos();
};

#endif // CONTROLLER_MANAGER_HPP