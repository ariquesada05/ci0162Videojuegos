#ifndef GAME_HPP
#define GAME_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <sol/sol.hpp>

#include <memory>

#include "../AnimationManager/AnimationManager.hpp"
#include "../AssetManager/AssetManager.hpp"
#include "../ControllerManager/ControllerManager.hpp"
#include "../EventManager/EventManager.hpp"
#include "../ECS/ECS.hpp"
#include "../SceneManager/SceneManager.hpp"

const int FPS = 60;
const int MILISECS_PER_FRAME = 1000 / FPS;

class Game
{

public:
private:
  SDL_Window *window = nullptr;

  SDL_Rect camera = {0, 0, 0, 0};

  int millisecsPreviousFrame = 0;

  bool isRunning = false;
  bool isDebugMode = false;

public:
  SDL_Renderer *renderer = nullptr;

  std::unique_ptr<AnimationManager> animationManager = nullptr;
  std::unique_ptr<AssetManager> assetManager = nullptr;
  std::unique_ptr<ControllerManager> controllerManager = nullptr;
  std::unique_ptr<EventManager> eventManager = nullptr;
  std::unique_ptr<Registry> registry = nullptr;
  std::unique_ptr<SceneManager> sceneManager = nullptr;
  sol::state lua;

  int windowWidth = 0;
  int windowHeight = 0;

  int mapWidth = 0;
  int mapHeight = 0;

private:
  void setUp();
  void runScene();
  void processInput();
  void update();
  void render();
  Game();
  ~Game();

public:
  static Game &GetInstance();

  void run();
  void init();
  void destroy();
};

#endif // GAME_HPP