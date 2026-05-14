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

    if (!lua["entity"].valid())
    {
        lua.new_usertype<Entity>("entity");
    }

    // Functions
    lua.set_function("change_animation", ChangeAnimation);

    lua.set_function("is_action_activated", IsActionActivated);

    lua.set_function("get_velocity", GetVelocity);
    lua.set_function("set_velocity", SetVelocity);

    lua.set_function("add_force", AddForce);
    lua.set_function("increment_velocity", IncrementVelocity);
    lua.set_function("change_direction", changeDirection);

    lua.set_function("frog_attack", frogAttack);

    lua.set_function("add_force", AddForce);


    lua.set_function("go_to_scene", GoToScene);
    lua.set_function("flip_sprite", FlipSprite);

    lua.set_function("get_tag", getTag);

    lua.set_function("left_collision", leftCollision);
    lua.set_function("right_collision", rightCollision);

    lua.set_function("get_position", getPosition);
    lua.set_function("set_position", setPosition);

    lua.set_function("get_size", getSize);

    lua.set_function("play_sound", PlaySound);
    lua.set_function("play_music", PlayMusic);
    lua.set_function("stop_all_sounds", StopAllSounds);

    lua.set_function("get_score", GetPoints);
    lua.set_function("increment_score", SetPoints);
    lua.set_function("get_health",GetHealth);
    lua.set_function("increment_health", SetHealth);

    lua.set_function("get_damage", GetDamage);
    lua.set_function("set_damage", SetDamage);




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

  void initFromScript(sol::state& lua) {
        // loop through all entities and call the on_init function
        for (auto& entity : getEntities()) {
            const auto& script = entity.getComponent<ScriptComponent>();
            // check if the on_init function exists
            if (script.onInit != sol::lua_nil) {
                lua["this"] = entity;
                script.onInit();
            }
        }
    }
};

#endif // SCRIPT_SYSTEM_HPP