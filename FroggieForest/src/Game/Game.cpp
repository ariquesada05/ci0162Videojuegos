#include "Game.hpp"

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include "../Events/ClickEvent.hpp"

#include "../Systems/CircleCollisionSystem.hpp"
#include "../Systems/RenderSystem.hpp"
#include "../Systems/MovementSystem.hpp"
#include "../Systems/overlapSystem.hpp"
#include "../Systems/UISystem.hpp"
#include "../Systems/CameraMovementSystem.hpp" 
// #include "../Systems/DamageSystem.hpp"
#include "../Systems/animationSystem.hpp"
#include "../Systems/ScriptSystem.hpp"
#include "../Systems/textSystem.hpp"
#include "../Systems/UISystem.hpp"
#include "../Systems/CameraMovementSystem.hpp"
#include "../Systems/boxCollisionSystem.hpp"
#include "../Systems/renderBoxColliderSystem.hpp"
#include "../Systems/physicsSystem.hpp"
#include "../Systems/EnemyColliderSystem.hpp"
#include "../Systems/RenderEnemyColliderSystem.hpp"
#include "../Systems/PlayerScoreSystem.hpp"


#include "../AudioManager/AudioManager.hpp"


Game::Game()
{
  std::cout << "[Game] Constructor" << std::endl;

  animationManager = std::make_unique<AnimationManager>();
  assetManager = std::make_unique<AssetManager>();
  controllerManager = std::make_unique<ControllerManager>();
  eventManager = std::make_unique<EventManager>();
  registry = std::make_unique<Registry>();
  sceneManager = std::make_unique<SceneManager>();
  audioManager = std::make_unique<AudioManager>();
}

Game::~Game()
{
  animationManager.reset();
  assetManager.reset();
  controllerManager.reset();
  eventManager.reset();
  registry.reset();
  sceneManager.reset();
  audioManager.reset();
  
  std::cout << "[Game] Destructor" << std::endl;
}

Game &Game::GetInstance()
{
  static Game game;
  return game;
}

void Game::setUp()
{
  registry->addSystem<AnimationSystem>();
  registry->addSystem<CircleCollisionSystem>();
  // registry->addSystem<DamageSystem>();
  registry->addSystem<MovementSystem>();
  registry->addSystem<RenderSystem>();
  registry->addSystem<ScriptSystem>();
  registry->addSystem<TextSystem>();
  registry->addSystem<UISystem>();
  registry->addSystem<CameraMovementSystem>();
  registry->addSystem<BoxCollisionSystem>();
  registry->addSystem<RenderBoxColliderSystem>();
  //registry->addSystem<PlayerScoreSystem>();

  registry->addSystem<PhysicsSystem>();
  registry->addSystem<OverlapSystem>();
  registry->addSystem<EnemyColliderSystem>();
  registry->addSystem<RenderEnemyColliderSystem>();

  lua.open_libraries(sol::lib::base, sol::lib::math);
  registry->getSystem<ScriptSystem>().CreateLuaBinding(lua);

  int flags = MIX_INIT_OGG | MIX_INIT_MP3;
  if ((Mix_Init(flags) & flags) != flags) {
      std::cerr << "SDL_mixer init failed: " << Mix_GetError() << std::endl;
  }

  if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
      std::cerr << "Mix_OpenAudio error: " << Mix_GetError() << std::endl;
  }
    sceneManager->LoadSceneFromScript("assets/scripts/scenes.lua", lua);
}

void Game::init()
{
  if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
  {
    std::cerr << "[Game] Error initializing SDL" << std::endl;
    return;
  }

  if (TTF_Init() != 0)
  {
    std::cerr << "[Game] Error initializing SDL TTF" << std::endl;
    return;
  }

  windowWidth = 800;
  windowHeight = 600;

  window = SDL_CreateWindow(
      "Froggie Forest",
      SDL_WINDOWPOS_CENTERED,
      SDL_WINDOWPOS_CENTERED,
      windowWidth,
      windowHeight,
      SDL_WINDOW_SHOWN);

  if (!window)
  {
    std::cerr << "[Game] Error creating SDL window" << std::endl;
    return;
  }

  renderer = SDL_CreateRenderer(window, -1, 0);

  if (!renderer)
  {
    std::cerr << "[Game] Error creating SDL renderer" << std::endl;
    return;
  }

  camera.w = windowWidth;
  camera.h = windowHeight;

  isRunning = true;
}

void Game::processInput()
{
  SDL_Event event;

  while (SDL_PollEvent(&event))
  {
    switch (event.type)
    {
    case SDL_QUIT:
      sceneManager->StopScene();
      isRunning = false;
      break;
    case SDL_KEYDOWN:
      if (event.key.keysym.sym == SDLK_ESCAPE)
      {
        sceneManager->StopScene();
        isRunning = false;
        break;
      }
      if (event.key.keysym.sym == SDLK_i)
      {
        isDebugMode = !isDebugMode;
        break;
      }
      controllerManager->KeyDown(event.key.keysym.sym);
      break;
    case SDL_KEYUP:
      controllerManager->KeyUp(event.key.keysym.sym);
      break;
    case SDL_MOUSEMOTION:
      int mousePosX, mousePosY;
      SDL_GetMouseState(&mousePosX, &mousePosY);
      controllerManager->SetMousePos(mousePosX, mousePosY);
      break;
    case SDL_MOUSEBUTTONDOWN:
      controllerManager->SetMousePos(event.button.x, event.button.y);
      controllerManager->MouseButtonDown(static_cast<int>(event.button.button));
      eventManager->EmitEvent<ClickEvent>(static_cast<int>(event.button.button), event.button.x, event.button.y);
      break;
    case SDL_MOUSEBUTTONUP:
      controllerManager->SetMousePos(event.button.x, event.button.y);
      controllerManager->MouseButtonUp(static_cast<int>(event.button.button));
      break;
    default:
      break;
    }
  }
}

void Game::update()
{
  int millisecsToWait = MILISECS_PER_FRAME - (SDL_GetTicks() - millisecsPreviousFrame);

  if (0 < millisecsToWait && millisecsToWait <= MILISECS_PER_FRAME)
  {
    SDL_Delay(millisecsToWait);
  }

  double deltaTime = (SDL_GetTicks() - millisecsPreviousFrame) / 1000.0;
  // TODO: add this variable to the LUA state

  millisecsPreviousFrame = SDL_GetTicks();

  eventManager->Reset();
  // registry->getSystem<DamageSystem>().SubscribeToCollisionEvent(eventManager);
  registry->getSystem<OverlapSystem>().SubscribeToCollisionEvent(eventManager);
  registry->getSystem<UISystem>().SubscribeToClickEvent(eventManager);

  registry->Update();
  registry->getSystem<ScriptSystem>().update(lua);

  registry->getSystem<PhysicsSystem>().update();
  registry->getSystem<MovementSystem>().update(deltaTime);
  registry->getSystem<BoxCollisionSystem>().update(eventManager, lua);
  registry->getSystem<CircleCollisionSystem>().update(eventManager);
  //damage
  registry->getSystem<EnemyColliderSystem>().Update(eventManager, lua);

  registry->getSystem<AnimationSystem>().update();
  registry->getSystem<CameraMovementSystem>().Update(camera);
}

void Game::render()
{
  SDL_SetRenderDrawColor(renderer, 31, 31, 31, 255);
  SDL_RenderClear(renderer);

  registry->getSystem<RenderSystem>().update(renderer, assetManager, camera);
  registry->getSystem<TextSystem>().update(renderer, assetManager);

  //stats and plkayer score


  if (isDebugMode)
  {
    registry->getSystem<RenderBoxColliderSystem>().Update(renderer, camera);
    registry->getSystem<RenderEnemyColliderSystem>().Update(renderer, camera);
  }

  SDL_RenderPresent(renderer);
}

void Game::runScene()
{
  sceneManager->LoadScene();
  registry->getSystem<ScriptSystem>().initFromScript(lua);

  while (sceneManager->IsSceneRunning())
  {
    processInput();
    update();
    render();
  }

  assetManager->ClearAssets();
  registry->clearAllEntities();
}

void Game::run()
{
  setUp();

  while (isRunning)
  {
    sceneManager->StartScene();
    runScene();
  }
}

void Game::destroy()
{
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  TTF_Quit();
  SDL_Quit();
}
