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

class SceneLoader
{
private:
  void LoadSprites(SDL_Renderer *renderer, sol::table sprites, std::unique_ptr<AssetManager> &assetManager);

  void LoadAnimations(const sol::table &animations, std::unique_ptr<AnimationManager> &animationManager);

  void LoadKeys(const sol::table &keys, std::unique_ptr<ControllerManager> &controllerManager);

  void LoadEntities(sol::state &lua, const sol::table &entities, std::unique_ptr<Registry> &registry);

  void LoadFonts(sol::table fonts, std::unique_ptr<AssetManager> &assetManager);

  void LoadButtons(sol::table buttons, std::unique_ptr<ControllerManager> &controllerManager);

  void LoadMap(const sol::table map, std::unique_ptr<Registry> &registry);

  void LoadLayer(std::unique_ptr<Registry> &registry, tinyxml2::XMLElement *layerElement, int tWidth, int tHeight, int mWidth, const std::string &tileSet, int columns);

  void LoadColliders(std::unique_ptr<Registry> &registry, tinyxml2::XMLElement *objectGroup);

public:
  SceneLoader();
  ~SceneLoader();

  void LoadScene(const std::string &scenePath, sol::state &lua,
                 std::unique_ptr<AnimationManager> &animationManager,
                 std::unique_ptr<AssetManager> &assetManager,
                 std::unique_ptr<ControllerManager> &controllerManager,
                 std::unique_ptr<Registry> &registry, SDL_Renderer *renderer);
};

#endif // SCENELOADER_HPP