/**
 * @file SceneManager.hpp
 * @brief Scene management system
 * 
 * Handles the loading and management of game scenes/levels using Lua configuration.
 */

#ifndef SCENE_MANAGER_HPP
#define SCENE_MANAGER_HPP

#include <map>
#include <memory>
#include <string>
#include <sol/sol.hpp>

#include "SceneLoader.hpp"

/**
 * @class SceneManager
 * @brief Manages game scenes and transitions
 * 
 * Handles the loading, starting, and stopping of game scenes. Scenes are
 * defined using Lua configuration files.
 */
class SceneManager
{
private:
  std::map<std::string, std::string> scenes; ///< Map of scene names to file paths
  std::string nextScene;                     ///< Name of the next scene to load
  bool isSceneRunning = false;               ///< Whether a scene is currently running
  std::unique_ptr<SceneLoader> sceneLoader;  ///< Scene loader utility

public:
  /**
   * @brief Construct a new SceneManager
   */
  SceneManager();
  
  /**
   * @brief Destroy the SceneManager
   */
  ~SceneManager();

  /**
   * @brief Load a scene from a Lua script file
   * @param scenePath Path to the Lua scene configuration file
   * @param lua Reference to the Lua state
   */
  void LoadSceneFromScript(const std::string &scenePath, sol::state &lua);
  
  /**
   * @brief Load the next scene
   */
  void LoadScene();

  /**
   * @brief Get the name of the next scene to load
   * @return std::string The next scene name
   */
  std::string GetNextScene() const;
  
  /**
   * @brief Set the next scene to load
   * @param nextScene The name of the next scene
   */
  void SetNextScene(const std::string &nextScene);

  /**
   * @brief Check if a scene is currently running
   * @return bool True if a scene is running
   */
  bool IsSceneRunning() const;
  
  /**
   * @brief Start running the current scene
   */
  void StartScene();
  
  /**
   * @brief Stop the current scene
   */
  void StopScene();
};

#endif // SCENE_MANAGER_HPP