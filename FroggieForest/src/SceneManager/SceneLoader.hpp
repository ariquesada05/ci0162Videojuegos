/**
 * @file SceneLoader.hpp
 * @brief Scene loading from Lua configuration files
 * 
 * Loads game scene data from Lua configuration files including entities,
 * sprites, animations, maps, and other game assets.
 */

#ifndef SCENELOADER_HPP
#define SCENELOADER_HPP

#include <SDL2/SDL.h>
#include <tinyxml2/tinyxml2.h>

#include <memory>
#include <string>
#include <sol/sol.hpp>
#include "../AnimationManager/AnimationManager.hpp"
#include "../AssetManager/AssetManager.hpp"
#include "../ControllerManager/ControllerManager.hpp"
#include "../ECS/ECS.hpp"
#include "../AudioManager/AudioManager.hpp"

/**
 * @class SceneLoader
 * @brief Loads game scenes from Lua configuration files
 * 
 * Parses Lua configuration files to load all scene data including entities,
 * sprites, animations, controls, maps, audio, and colliders.
 */
class SceneLoader
{
private:
  std::set<std::string> tagsWithDamageColliders; ///< Set of entity tags that have damage colliders
  
  /**
   * @brief Load sprite definitions from Lua
   */
  void LoadSprites(SDL_Renderer *renderer, sol::table sprites, std::unique_ptr<AssetManager> &assetManager);

  /**
   * @brief Load animation definitions from Lua
   */
  void LoadAnimations(const sol::table &animations, std::unique_ptr<AnimationManager> &animationManager);

  /**
   * @brief Load keyboard control mappings from Lua
   */
  void LoadKeys(const sol::table &keys, std::unique_ptr<ControllerManager> &controllerManager);

  /**
   * @brief Load a single entity and its components from Lua
   */
  void LoadEntity(sol::state &lua, Entity &entity, sol::table entityTable);

  /**
   * @brief Load all entities from Lua configuration
   */
  void LoadEntities(sol::state &lua, const sol::table &entities, std::unique_ptr<Registry> &registry);

  /**
   * @brief Load font definitions from Lua
   */
  void LoadFonts(sol::table fonts, std::unique_ptr<AssetManager> &assetManager);

  /**
   * @brief Load UI button definitions from Lua
   */
  void LoadButtons(sol::table buttons, std::unique_ptr<ControllerManager> &controllerManager);

  /**
   * @brief Load map data from Lua (tiled map reference)
   */
  void LoadMap(const sol::table map, std::unique_ptr<Registry> &registry, sol::state &lua);

  /**
   * @brief Load a layer from a tiled map file
   */
  void LoadLayer(std::unique_ptr<Registry> &registry, tinyxml2::XMLElement *layerElement, int tWidth, int tHeight, int mWidth, const std::string &tileSet, int columns);

  /**
   * @brief Load collision objects from a tiled map
   */
  void LoadColliders(std::unique_ptr<Registry> &registry, tinyxml2::XMLElement *objectGroup);

  /**
   * @brief Load sound effect definitions from Lua
   */
  void LoadSounds(const sol::table &sounds, std::unique_ptr<AudioManager> &audioManager);

  /**
   * @brief Load music track definitions from Lua
   */
  void LoadMusic(const sol::table &music, std::unique_ptr<AudioManager> &audioManager);

  /**
   * @brief Load enemy collision colliders from a tiled map
   */
  void LoadEnemiesColliders(std::unique_ptr<Registry> &registry, tinyxml2::XMLElement *objectGroup);

  /**
   * @brief Load enemy entities from a tiled map
   */
  void LoadEnemies(sol::state &lua, tinyxml2::XMLElement *objectGroup, std::unique_ptr<Registry> &registry);

  /**
   * @brief Load game statistics from Lua
   */
  void LoadStats(const sol::table &stats);

  /**
   * @brief Load damage colliders from Lua
   */
  void LoadDamageColliders(const sol::table &colliders);

  void LoadItems(const sol::table& items, std::unique_ptr<Registry>& registry);

public:
  /**
   * @brief Construct a new SceneLoader
   */
  SceneLoader();
  
  /**
   * @brief Destroy the SceneLoader
   */
  ~SceneLoader();

  /**
   * @brief Load a complete scene from a Lua configuration file
   * 
   * @param scenePath Path to the Lua scene configuration file
   * @param lua Reference to the Lua state
   * @param animationManager Reference to the animation manager
   * @param assetManager Reference to the asset manager
   * @param audioManager Reference to the audio manager
   * @param controllerManager Reference to the controller manager
   * @param registry Reference to the ECS registry
   * @param renderer SDL renderer for loading textures
   */
  void LoadScene(const std::string &scenePath, sol::state &lua,
                 std::unique_ptr<AnimationManager> &animationManager,
                 std::unique_ptr<AssetManager> &assetManager,
                 std::unique_ptr<AudioManager> &audioManager,
                 std::unique_ptr<ControllerManager> &controllerManager,
                 std::unique_ptr<Registry> &registry, SDL_Renderer *renderer);
};

#endif // SCENELOADER_HPP