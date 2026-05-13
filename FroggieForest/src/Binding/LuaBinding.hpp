#ifndef LUABINDING_HPP
#define LUABINDING_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h> // SDL2_mixer used for audio


#include <string>
#include <tuple>

#include "../AnimationManager/AnimationManager.hpp"
#include "../Components/AnimationComponent.hpp"
#include "../Components/BoxColliderComponent.hpp"
#include "../Components/RigidBodyComponent.hpp"
#include "../Components/TagComponent.hpp"
#include "../Components/TransformComponent.hpp"
#include "../Components/SpriteComponent.hpp"
#include "../Components/PlayerVelocity.hpp"
#include "../Game/Game.hpp"
#include "../ECS/ECS.hpp"
#include "../AudioManager/AudioManager.hpp"
#include "../StatsManager/StatsManager.hpp"

//* Animations

void ChangeAnimation(Entity entity, const std::string &animationId)
{
  auto &animation = entity.getComponent<AnimationComponent>();
  auto &sprite = entity.getComponent<SpriteComponent>();

  AnimationData data;
  data = Game::GetInstance().animationManager->getAnimationData(animationId);

  sprite.textureID = data.textureId;
  sprite.width = data.width;
  sprite.height = data.height;
  sprite.srcRect.x = 0;
  sprite.srcRect.y = 0;

  animation.currentFrame = 1;
  animation.frameTime = data.fremeSpeedRate;
  animation.numFrames = data.numFrames;
  animation.isLooping = data.isLoop;
  animation.startTime = SDL_GetTicks();
}

int GetCurrentFrame(Entity entity)
{
  auto &animation = entity.getComponent<AnimationComponent>();

  return animation.currentFrame;
}

bool IsLookingRight(Entity entity)
{
  if (!entity.hasComponent<SpriteComponent>())
  {
    return false;
  }
  return entity.getComponent<SpriteComponent>().flip == false;
}

/**
 * @brief Attack with frog tongue animation.
 * @param entity The entity that attacks.
 */
void frogAttack(Entity entity)
{
    auto& sprite = entity.getComponent<SpriteComponent>();

    // Cambiar sprite/animación
    sprite.textureID = "frog_attack";

    // Reiniciar frame
    if (entity.hasComponent<AnimationComponent>())
    {
        auto& animation = entity.getComponent<AnimationComponent>();

        animation.currentFrame = 0;
        animation.numFrames = 8;      
        animation.frameTime = 8;
        animation.isLooping = false;
    }

    std::cout << "[LUABINDING] Frog Attack" << std::endl;
}


//* Controls

bool IsActionActivated(const std::string &action)
{
  return Game::GetInstance().controllerManager->IsActionActivated(action);
}

//* Rigidbody

std::tuple<int, int> GetVelocity(Entity entity)
{
  auto &rigidBody = entity.getComponent<RigidBodyComponent>();
  return {
      static_cast<int>(rigidBody.velocity.x),
      static_cast<int>(rigidBody.velocity.y) //
  };
}

void SetVelocity(Entity entity, float x, float y)
{
  auto &rigidBody = entity.getComponent<RigidBodyComponent>();
  rigidBody.velocity.x = x;
  rigidBody.velocity.y = y;
}

void AddForce(Entity entity, float x, float y)
{
  auto &rigidBody = entity.getComponent<RigidBodyComponent>();
  rigidBody.sumForces += glm::vec2(x, y);
}

void IncrementVelocity(Entity entity, float x)
{
  auto &playerVelocity = entity.getComponent<PlayerVelocity>();
  playerVelocity.playerVelocity += x; // Assuming playerVelocity is a scalar value
}

void changeDirection(Entity entity)
{
  auto &rigidBody = entity.getComponent<RigidBodyComponent>();
  rigidBody.velocity.x *= -1;
}

//* TagComonent

std::string getTag(Entity entity)
{
  return entity.getComponent<TagComponent>().tag;
}

//* TransformComponent

std::tuple<int, int> getPosition(Entity entity)
{
  auto &transform = entity.getComponent<TransformComponent>();
  return {
      static_cast<int>(transform.position.x),
      static_cast<int>(transform.position.y) //
  };
}

void setPosition(Entity entity, int x, int y)
{
  auto &transform = entity.getComponent<TransformComponent>();
  transform.position.x = static_cast<float>(x);
  transform.position.y = static_cast<float>(y);
}

std::tuple<int, int> getSize(Entity entity)
{
  auto &transform = entity.getComponent<TransformComponent>();
  auto &sprite = entity.getComponent<SpriteComponent>();

  return {
      static_cast<int>(sprite.width * transform.scale.x),
      static_cast<int>(sprite.height * transform.scale.y) //
  };
}


//* Score and player functions

void IncrementPlayerVelocity(Entity entity, int increment)
{
  auto &playerVelocity = entity.getComponent<PlayerVelocity>();
  playerVelocity.playerVelocity += increment;
}

void getPlayerVelocity(Entity entity, int &velocity)
{
  auto &playerVelocity = entity.getComponent<PlayerVelocity>();
  velocity = playerVelocity.playerVelocity;
}

int getHealth(Entity entity)
{
  if (!entity.hasComponent<StatsComponent>()) {
    return -1; // or some default value indicating no health
  }
  auto &stats = entity.getComponent<StatsComponent>();
  return stats.Health;
}

void setHealth(Entity entity, int health)
{
  entity.getComponent<StatsComponent>().Health = health;
}

int getPoints(Entity entity)
{
  if (!entity.hasComponent<StatsComponent>()) {
    return -1; // or some default value indicating no points
  }
  auto &stats = entity.getComponent<StatsComponent>();
  return stats.Points;
}

void setPoints(Entity entity, int points)
{
  entity.getComponent<StatsComponent>().Points = points;
}


// int getDamage(Entity entity)
// {
//   if (!entity.hasComponent<StatsComponent>()) {
//     return -1; // or some default value indicating no damage
//   }
//   auto &stats = entity.getComponent<StatsComponent>();
//   return stats.damage;
// }

// int setDamage(Entity entity, int damage)
// {
//   entity.getComponent<StatsComponent>().damage = damage;
// }
//* Scenes

void GoToScene(const std::string &scenePath)
{
  Game::GetInstance().sceneManager->SetNextScene(scenePath);
  Game::GetInstance().sceneManager->StopScene();
}

//* Sprites

void FlipSprite(Entity entity, bool flip)
{
  auto &sprite = entity.getComponent<SpriteComponent>();
  sprite.flip = flip;
}

//* Collisions

bool leftCollision(Entity This, Entity Other)
{
  const auto &thisCollider = This.getComponent<BoxColliderComponent>();
  const auto &thisTransform = This.getComponent<TransformComponent>();

  const auto &otherCollider = Other.getComponent<BoxColliderComponent>();
  const auto &otherTransform = Other.getComponent<TransformComponent>();

  float thisX = thisTransform.previousPosition.x;
  float thisY = thisTransform.previousPosition.y;
  float thisHeight = static_cast<float>(thisCollider.height);

  float otherX = otherTransform.previousPosition.x;
  float otherY = otherTransform.previousPosition.y;
  float otherHeight = static_cast<float>(otherCollider.height);

  // El lado izquierdo de this choca con el lado derecho de other

  return (
      otherY < thisY + thisHeight &&
      otherY + otherHeight > thisY &&
      otherX < thisX);
}

bool rightCollision(Entity This, Entity Other)
{
  const auto &thisCollider = This.getComponent<BoxColliderComponent>();
  const auto &thisTransform = This.getComponent<TransformComponent>();

  const auto &otherCollider = Other.getComponent<BoxColliderComponent>();
  const auto &otherTransform = Other.getComponent<TransformComponent>();

  float thisX = thisTransform.previousPosition.x;
  float thisY = thisTransform.previousPosition.y;
  float thisH = static_cast<float>(thisCollider.height);

  float otherX = otherTransform.previousPosition.x;
  float otherY = otherTransform.previousPosition.y;
  float otherH = static_cast<float>(otherCollider.height);

  // El lado derecho de this choca con el lado izquierdo de other

  return (
      otherY < thisY + thisH &&
      otherY + otherH > thisY &&
      otherX > thisX);
}

//audio section

void PlaySound(const std::string &soundId)
{
  Game::GetInstance().audioManager->PlaySoundEffect(soundId);
}

void PlayMusic(const std::string &musicId)
{
  Game::GetInstance().audioManager->PlayMusic(musicId);
}

void StopAllSounds()
{
  Game::GetInstance().audioManager->StopAllSounds();
}



#endif // LUABINDING_HPP