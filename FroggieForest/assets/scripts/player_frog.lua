-- Variables globales
player_states = {
  IDLE = 0,
  RUN = 1,
  JUMP = 2,
  FALL = 3,
  DIE = 4,
  ATTACK = 5,
}

player_state = player_states["IDLE"]
player_can_jump = false
player_speed = 5.0 * 64.0
player_jump_force = -3200.0 * 64.0

-- Variables de ataque
player_is_attacking = false
attack_timer = 0          -- contador de frames
attack_max_frames = 20

----------------------------------------------------------------
-- UPDATE
----------------------------------------------------------------
function update()
  local vel_x, vel_y = get_velocity(this)
  vel_x = 0

  -- Salto 
  if is_action_activated("jump") then
    if player_can_jump then
      print("Jump")
      add_force(this, 0, player_jump_force)
    end
  end

  -- Iniciar ataque
  if is_action_activated("attack") then
    if not player_is_attacking and player_state ~= player_states["DIE"] then
      player_is_attacking = true
      attack_timer = 0
    end
  end

  -- Actualizar ataque
  if player_is_attacking then
    attack()
  end

  -- Movimiento (lo dejas activo incluso atacando; si no quieres, añade "and not player_is_attacking")
  if is_action_activated("left") then
    vel_x = vel_x - player_speed
  end
  if is_action_activated("right") then
    vel_x = vel_x + player_speed
  end

  if player_state == player_states["DIE"] then
    return
  end

  set_velocity(this, vel_x, vel_y)
  update_animation_state()
  player_can_jump = false
end

----------------------------------------------------------------
-- ATAQUE
----------------------------------------------------------------
function attack()
  -- aseguramos estado y animación de ataque
  if player_state ~= player_states["ATTACK"] then
    print("Attack start")
    player_state = player_states["ATTACK"]
    change_animation(this, "player_frog_attack")
  end

  -- avanzar contador de frames
  attack_timer = attack_timer + 1

  -- fin de ataque
  if attack_timer >= attack_max_frames then
    print("Attack end")
    player_is_attacking = false
    attack_timer = 0
  end
end

function do_attack_hit()
  if not player_is_attacking then
    return
  end
  -- lógica de daño
end

----------------------------------------------------------------
-- COLISIONES
----------------------------------------------------------------
function on_collision(other)
  if get_tag(other) == "floor" then
    local vel_x, vel_y = get_velocity(this)
    if vel_y == 0 then
      player_can_jump = true
    end
  end

  if get_tag(other) == "obs" or get_tag(other) == "obs" then
    local vel_x, vel_y = get_velocity(this)
    if vel_y == 0 then
      player_can_jump = true
    end
  end

  if get_tag(other) == "die" then
    print("Die")
    player_state = player_states["DIE"]
    change_animation(this, "player_frog_die")
    go_to_scene("game_over")
  end
end

----------------------------------------------------------------
-- MUERTE
----------------------------------------------------------------
function die()
  print("Die")
  player_state = player_states["DIE"]
  change_animation(this, "player_frog_die")
end

----------------------------------------------------------------
-- ANIMACIONES
----------------------------------------------------------------
function update_animation_state()
  local x_vel, y_vel = get_velocity(this)

  -- Mientras está atacando, mantener anim de ataque
  if player_is_attacking then
    if player_state ~= player_states["ATTACK"] then
      player_state = player_states["ATTACK"]
      change_animation(this, "player_frog_attack")
    end
    return
  end

  -- Si está muriendo, mantener anim de muerte
  if player_state == player_states["DIE"] then
    change_animation(this, "player_frog_die")
    return
  end

  -- Jugador cae
  if y_vel >= 0.001 then
    if player_state ~= player_states["FALL"] then
      player_state = player_states["FALL"]
      change_animation(this, "player_frog_fall")
    end
    return
  end

  -- Jugador salta
  if y_vel <= -0.001 then
    if player_state ~= player_states["JUMP"] then
      player_state = player_states["JUMP"]
      change_animation(this, "player_frog_jump")
    end
    return
  end

  -- Jugador no se mueve
  if -0.001 < x_vel and x_vel < 0.001 then
    if player_state ~= player_states["IDLE"] then
      player_state = player_states["IDLE"]
      change_animation(this, "player_frog_idle")
    end
    return
  end

  -- Jugador se mueve hacia la derecha
  if x_vel >= 0.001 then
    flip_sprite(this, false)
    if player_state ~= player_states["RUN"] then
      player_state = player_states["RUN"]
      change_animation(this, "player_frog_run")
    end
    return
  end

  -- Jugador se mueve hacia la izquierda
  if x_vel <= -0.001 then
    flip_sprite(this, true)
    if player_state ~= player_states["RUN"] then
      player_state = player_states["RUN"]
      change_animation(this, "player_frog_run")
    end
    return
  end
end
