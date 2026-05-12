-- Variables globales
enemy_states = {
  IDLE = 0,
  RUN = 1,
  DIE = 2,
}

enemy_state = enemy_states["IDLE"]
enemy_speed = 5.0 * 64.0

---------------------------------------------------------------
-- UPDATE
----------------------------------------------------------------
function update()
  local vel_x, vel_y = get_velocity(this)
  vel_x = 0

  vel_y = 0 --solo se mueve horizontalmente
  
  if is_action_activated("left") then
    vel_x = vel_x - enemy_speed
  end
  if is_action_activated("right") then
    vel_x = vel_x + enemy_speed
  end

  if enemy_state == enemy_states["DIE"] then
    return
  end

  set_velocity(this, vel_x, vel_y)
  update_animation_state()
end

----------------------------------------------------------------
-- COLISIONES
----------------------------------------------------------------
-- function on_collision(other)
  
--   if get_tag(other) == "die" then
--     print("Die")
--     enemy_state = enemy_states["DIE"]
--     go_to_scene("game_over")
--   end
-- end

----------------------------------------------------------------
-- MUERTE
----------------------------------------------------------------
-- function die()
--   print("Die")
--   enemy_state = enemy_states["DIE"]
--   change_animation(this, "enemy01_die")
-- end

----------------------------------------------------------------
-- ANIMACIONES
----------------------------------------------------------------
function update_animation_state()
  local x_vel, y_vel = get_velocity(this)


  -- Si está muriendo, mantener anim de muerte
--   if enemy_state == enemy_states["DIE"] then
--     change_animation(this, "enemy_frog_die")
--     return
--   end

  -- Jugador no se mueve
  if -0.001 < x_vel and x_vel < 0.001 then
    if enemy_state ~= enemy_states["IDLE"] then
      enemy_state = enemy_states["IDLE"]
      change_animation(this, "enemy01_idle")
    end
    return
  end

  -- Jugador se mueve hacia la derecha
  if x_vel >= 0.001 then
    flip_sprite(this, false)
    if enemy_state ~= enemy_states["RUN"] then
      enemy_state = enemy_states["RUN"]
      change_animation(this, "enemy01_run")
    end
    return
  end

  -- Jugador se mueve hacia la izquierda
  if x_vel <= -0.001 then
    flip_sprite(this, true)
    if enemy_state ~= enemy_states["RUN"] then
      enemy_state = enemy_states["RUN"]
      change_animation(this, "enemy01_run")
    end
    return
  end
end
