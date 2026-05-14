/**
 * @file Game.hpp
 * @brief Main game engine class
 * 
 * Central game loop and manager that coordinates all game systems including
 * rendering, input, physics, and scene management.
 */

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
#include "../AudioManager/AudioManager.hpp"

const int FPS = 60;                           ///< Target frames per second
const int MILISECS_PER_FRAME = 1000 / FPS;  ///< Milliseconds per frame

/**
 * @class Game
 * @brief Main game engine and singleton
 * 
 * Central class that manages the game loop, all managers, and coordinates
 * the execution of all game systems. Implemented as a singleton pattern.
 */
class Game
{

public:
private:
  SDL_Window *window = nullptr;   ///< SDL window

  SDL_Rect camera = {0, 0, 0, 0}; ///< Camera view rectangle

  int millisecsPreviousFrame = 0; ///< Time of previous frame for delta time calculation

  bool isRunning = false;  ///< Whether the game is running
  bool isDebugMode = false; ///< Debug mode flag
  bool isPaused = false;   ///< Game pause state

public:
  SDL_Renderer *renderer = nullptr; ///< SDL renderer

  std::unique_ptr<AnimationManager> animationManager = nullptr;  ///< Animation manager
  std::unique_ptr<AssetManager> assetManager = nullptr;          ///< Asset manager
  std::unique_ptr<ControllerManager> controllerManager = nullptr; ///< Input controller
  std::unique_ptr<EventManager> eventManager = nullptr;           ///< Event dispatcher
  std::unique_ptr<Registry> registry = nullptr;                   ///< ECS registry
  std::unique_ptr<SceneManager> sceneManager = nullptr;           ///< Scene manager
  std::unique_ptr<AudioManager> audioManager = nullptr;           ///< Audio manager
  sol::state lua;                                                  ///< Lua scripting state

  int windowWidth = 0;  ///< Window width in pixels
  int windowHeight = 0; ///< Window height in pixels

  int mapWidth = 0;  ///< Current map width in pixels
  int mapHeight = 0; ///< Current map height in pixels

  int playerScore = 0; ///< Current player score

private:
  /**
   * @brief Initialize game systems
   */
  void setUp();
  
  /**
   * @brief Run the current scene
   */
  void runScene();
  
  /**
   * @brief Process input events
   */
  void processInput();
  
  /**
   * @brief Update game state
   */
  void update();
  
  /**
   * @brief Render the current frame
   */
  void render();
  
  /**
   * @brief Construct a new Game (private for singleton)
   */
  Game();
  
  /**
   * @brief Destroy the Game
   */
  ~Game();

public:
  /**
   * @brief Get the singleton instance of the game
   * @return Game& Reference to the game instance
   */
  static Game &GetInstance();

  /**
   * @brief Start the main game loop
   */
  void run();
  
  /**
   * @brief Initialize the game
   */
  void init();
  
  /**
   * @brief Shut down the game and clean up resources
   */
  void destroy();
};

#endif // GAME_HPP