-- Variables globales
player_states = {
  IDLE = 0,
  RUN = 1,
  JUMP = 2,
  FALL = 3,
}
player_state = player_states["IDLE"]
player_can_jump = false
player_speed = 5.0 * 64.0
player_jump_force = -5500.0 * 64.0

function update()
  local vel_x, vel_y = get_velocity(this)
  vel_x = 0

  if is_action_activated("jump") then
    if player_can_jump then
      print("Jump")
      add_force(this, 0, player_jump_force)
    end
  end
  if is_action_activated("left") then
    vel_x = vel_x - player_speed
  end
  if is_action_activated("right") then
    vel_x = vel_x + player_speed
  end

  set_velocity(this, vel_x, vel_y)
  update_animation_state()
  player_can_jump = false
end

function on_collision(other)
  if get_tag(other) == "floor" then
    local vel_x, vel_y = get_velocity(this)
    if vel_y == 0 then
      player_can_jump = true
    end
  end
end

function update_animation_state()
  local x_vel, y_vel = get_velocity(this)

  -- jugador no se mueve
  if -0.001 < x_vel and x_vel < 0.001 then
    if player_state ~= player_states["IDLE"] then
      player_state = player_states["IDLE"]
      change_animation(this, "player_frog_idle")
    end
  end

  -- jugador se mueve hacia la derecha
  if x_vel >= 0.001 then 
    flip_sprite(this, false)
    if player_state ~= player_states["RUN"] then
      player_state = player_states["RUN"]
      change_animation(this, "player_frog_run")
    end
  end

  -- jugador se mueve hacia la izquierda
  if x_vel <= -0.001 then 
    flip_sprite(this, true)
    if player_state ~= player_states["RUN"] then
      player_state = player_states["RUN"]
      change_animation(this, "player_frog_run")
    end
  end

  -- jugador cae
  if y_vel >= 0.001 then
    if player_state ~= player_states["FALL"] then
      player_state = player_states["FALL"]
      change_animation(this, "player_frog_fall")
    end
  end

  -- jugador salta
  if y_vel <= -0.001 then
    if player_state ~= player_states["JUMP"] then
      player_state = player_states["JUMP"]
      change_animation(this, "player_frog_jump")
    end
  end


end