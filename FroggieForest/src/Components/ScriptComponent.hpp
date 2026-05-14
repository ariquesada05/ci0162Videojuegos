#ifndef SCRIPT_COMPONENT_HPP
#define SCRIPT_COMPONENT_HPP

#include <sol/sol.hpp>

struct ScriptComponent
{
  sol::function update;
  sol::function onClick;
  sol::function onInit;
  sol::function onCollision;
  sol::function onDamage;
  sol::function onPerform;

  ScriptComponent(sol::function update = sol::lua_nil, sol::function onClick = sol::lua_nil, sol::function onInit = sol::lua_nil, sol::function onCollision = sol::lua_nil, sol::function onDamage = sol::lua_nil, sol::function onPerform = sol::lua_nil)
  {
    this->update = update;
    this->onClick = onClick;
    this->onInit = onInit;
    this->onCollision = onCollision;
    this->onDamage = onDamage;
    this->onPerform = onPerform;
  }
};

#endif // SCRIPT_COMPONENT_HPP