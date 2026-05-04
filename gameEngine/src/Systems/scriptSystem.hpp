#ifndef SCRIPT_SYSTEM_HPP
#define SCRIPT_SYSTEM_HPP

#include <memory>
#include <sol/sol.hpp>

#include "../Binding/LuaBinding.hpp"
#include "../Components/ScriptComponent.hpp"
#include "../ECS/ECS.hpp"

class ScriptSystem : public System
{
public:
  ScriptSystem()
  {
    requireComponent<ScriptComponent>();
  }

  void CreateLuaBinding(sol::state &lua)
  {
    // Clases
    lua.new_usertype<Entity>("entity");

    // Functions
    lua.set_function("change_animation", ChangeAnimation);

    lua.set_function("is_action_activated", IsActionActivated);

    lua.set_function("get_velocity", GetVelocity);
    lua.set_function("set_velocity", SetVelocity);

    lua.set_function("add_force", AddForce);

    lua.set_function("go_to_scene", GoToScene);
    lua.set_function("flip_sprite", FlipSprite);

    lua.set_function("get_tag", getTag);

    lua.set_function("left_collision", leftCollision);
    lua.set_function("right_collision", rightCollision);

    lua.set_function("get_position", getPosition);
    lua.set_function("set_position", setPosition);

    lua.set_function("get_size", getSize);
  }

  void update(sol::state &lua)
  {
    for (auto &entity : getEntities())
    {
      auto &script = entity.getComponent<ScriptComponent>();

      if (script.update != sol::lua_nil)
      {
        lua["this"] = entity;
        script.update();
      }
    }
  }
};

#endif // SCRIPT_SYSTEM_HPP