#ifndef UI_SYSTEM_HPP
#define UI_SYSTEM_HPP

#include <SDL2/SDL.h>

#include <memory>
#include <string>

#include "../Components/ClickableComponent.hpp"
#include "../Components/ScriptComponent.hpp"
#include "../Components/TextComponent.hpp"
#include "../Components/TransformComponent.hpp"
#include "../ECS/ECS.hpp"
#include "../EventManager/EventManager.hpp"
#include "../Events/ClickEvent.hpp"

class UISystem : public System
{
public:
  UISystem() : System()
  {
    requireComponent<ClickableComponent>();
    requireComponent<TextComponent>();
    requireComponent<TransformComponent>();
  }

  void SubscribeToClickEvent(std::unique_ptr<EventManager> &eventManager)
  {
    eventManager->SubscribeToEvent<ClickEvent>(this, &UISystem::OnClickEvent);
  }

  void OnClickEvent(ClickEvent &event)
  {
    for (auto &entity : getEntities())
    {
      auto &text = entity.getComponent<TextComponent>();
      auto &transform = entity.getComponent<TransformComponent>();

      if (transform.position.x <= event.posX && event.posX < transform.position.x + text.width && transform.position.y <= event.posY && event.posY < transform.position.y + text.height)
      {
        if (entity.hasComponent<ScriptComponent>())
        {
          const auto &script = entity.getComponent<ScriptComponent>();
          if (script.onClick != sol::lua_nil)
          {
            script.onClick();
          }
        }
      }
    }
  }
};

#endif // UI_SYSTEM_HPP