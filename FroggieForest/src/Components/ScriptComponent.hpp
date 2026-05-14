/**
 * @file ScriptComponent.hpp
 * @brief Scripting component for Lua behavior
 */

#ifndef SCRIPT_COMPONENT_HPP
#define SCRIPT_COMPONENT_HPP

#include <sol/sol.hpp>

/**
 * @struct ScriptComponent
 * @brief Stores Lua script callbacks for entity behavior
 * 
 * Holds references to Lua functions that define entity behavior including
 * updates, input handling, collisions, and damage.
 */
struct ScriptComponent
{
  sol::function update;       ///< Called every frame to update entity
  sol::function onClick;      ///< Called when entity is clicked
  sol::function onInit;       ///< Called when entity is initialized
  sol::function onCollision;  ///< Called when entity collides with another
  sol::function onDamage;     ///< Called when entity takes damage
  sol::function onPerform;    ///< Called to perform a specific action

  /**
   * @brief Construct a ScriptComponent
   * @param update The update callback (default: nil)
   * @param onClick The click callback (default: nil)
   * @param onInit The init callback (default: nil)
   * @param onCollision The collision callback (default: nil)
   * @param onDamage The damage callback (default: nil)
   * @param onPerform The perform callback (default: nil)
   */
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