#ifndef SCENE_MANAGER_HPP
#define SCENE_MANAGER_HPP

#include <map>
#include <memory>
#include <string>
#include <sol/sol.hpp>

#include "SceneLoader.hpp"

class SceneManager
{
private:
  std::map<std::string, std::string> scenes;
  std::string nextScene;
  bool isSceneRunning = false;
  std::unique_ptr<SceneLoader> sceneLoader;

public:
  SceneManager();
  ~SceneManager();

  void LoadSceneFromScript(const std::string &scenePath, sol::state &lua);
  void LoadScene();

  std::string GetNextScene() const;
  void SetNextScene(const std::string &nextScene);

  bool IsSceneRunning() const;
  void StartScene();
  void StopScene();
};

#endif // SCENE_MANAGER_HPP