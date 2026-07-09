-- Variables globales
player_states = {
  IDLE = 0,
  RUN = 1,
  JUMP = 2,
  FALL = 3,
  DIE = 4,
  ATTACK = 5,
  DASH = 6,
}

player_state = player_states["IDLE"]
player_can_jump = false
-- Doble salto: 1 salto desde el piso + 1 salto en el aire. Se recargan al
-- volver a tocar el piso. jump_was_pressed detecta el flanco de la tecla para
-- que cada pulsación cuente como un solo salto (si no, mantenerla gastaría
-- ambos saltos de golpe).
jumps_max = 2
jumps_left = 0
jump_was_pressed = false
player_speed = 5.0 * 64.0
player_jump_force = -3200.0 * 64.0
damage_cooldown = 0
invulnerable = false
damage_timer = 1.0
-- Variables de ataque
player_is_attacking = false
attack_timer = 0          -- contador de frames
-- Duración del ataque: medio segundo (30 frames a 60 FPS)
attack_max_frames = 30
dieFrames = 30
dieTimer = 0
isDead = false  

diamond_timer = 0
invulnerable = false

player_dash_force = 600
dash_duration = 10
dash_cooldown_max = 40

is_dashing = false
dash_timer = 0
dash_cooldown = 0
dash_direction = 1
----------------------------------------------------------------
-- UPDATE
----------------------------------------------------------------
function update()
  local vel_x, vel_y = get_velocity(this)
  vel_x = 0

  if dash_cooldown > 0 then
    dash_cooldown = dash_cooldown - 1
  end

  -- Salto (con doble salto)
  local jump_pressed = is_action_activated("jump")
  local jump_just_pressed = jump_pressed and not jump_was_pressed

  -- Al estar en el piso se recargan los saltos disponibles.
  if player_can_jump then
    jumps_left = jumps_max
  end

  -- Salta solo en el flanco de subida de la tecla y si quedan saltos:
  -- el primero desde el piso, el segundo en el aire.
  if jump_just_pressed and jumps_left > 0 then
    print("Jump")
    vel_y = 0  -- reinicia la caída para que el salto en el aire sea consistente
    add_force(this, 0, player_jump_force)
    jumps_left = jumps_left - 1
  end

  jump_was_pressed = jump_pressed

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

  -- Iniciar dash
if is_action_activated("dash") then
  if not is_dashing and dash_cooldown <= 0 and player_state ~= player_states["DIE"] then
    print("Dash")
    is_dashing = true
    dash_timer = 0
    dash_cooldown = dash_cooldown_max
  end
end

-- Actualizar dash
  if is_dashing then
    dash_timer = dash_timer + 1
    vel_x = dash_direction * player_dash_force
    vel_y = 0

    if dash_timer >= dash_duration then
      is_dashing = false
      dash_timer = 0
    end
  end

  -- Contador de invulnerabilidad del diamante
  if invulnerable then
      diamond_timer = diamond_timer - 1

      if diamond_timer <= 0 then
          invulnerable = false
          print("Diamante terminado")
      end
  end

  if isDead then
    dieTimer = dieTimer + 1

    if dieTimer >= dieFrames then
        go_to_scene("gameOver")
    end

    return
end

  if is_action_activated("left") then
    vel_x = vel_x - player_speed
    dash_direction = -1
  end
  if is_action_activated("right") then
    vel_x = vel_x + player_speed
    dash_direction = 1
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

  if get_tag(other) == "floor" or get_tag(other) == "dissappears" then
 local vel_x, vel_y = get_velocity(this)
    if vel_y == 0 then
      player_can_jump = true
    end
  end

  if get_tag(other) == "obs" then
    local vel_x, vel_y = get_velocity(this)
    if vel_y == 0 then
      player_can_jump = true
    end
  end
  if get_tag(other) == "coin" then
    local points = get_score(this)

    increment_score(this, points + 10)

    kill_entity(other)
  end

  if get_tag(other) == "possion" then
    local health = get_health(this)

    increment_health(this, health + 5)

    kill_entity(other)
  end 

  if get_tag(other) == "diamond" then
        invulnerable = true
        diamond_timer = 180      

        kill_entity(other)
    end
  
  if get_tag(other) == "die" then
    die()
  end

  -- El golpe al enemigo lo aplica on_damage (hitbox de ataque ancho). Aquí, al
  -- contacto con el cuerpo, el jugador solo recibe daño si NO está atacando.
  if get_tag(other) == "enemy01" then
    if not player_is_attacking then
      receive_damage(other)
    end
  end

  if get_tag(other) == "bee" then
    if not player_is_attacking then
      receive_damage(other)
    end
  end

   if get_tag(other) == "trap" then
    receive_damage(other)
  end

  -- Sierra: peligro móvil que hace mucho daño (30). No se puede matar.
  if get_tag(other) == "saw" then
    receive_damage(other)
  end


  if get_tag(other) == "win" then
    go_to_scene("win")
  end
end

-- on_damage lo dispara el DamageCollisionSystem con el "damage_collider", que
-- en el jugador es un hitbox de ataque más ancho que el cuerpo. Por eso aquí
-- SOLO golpeamos a los enemigos mientras se ataca; el daño que RECIBE el
-- jugador se maneja en on_collision (con el box_collider, de alcance normal).
function on_damage(other)
  if not player_is_attacking then
    return
  end

  local otherTag = get_tag(other)

  if otherTag == "enemy01" or otherTag == "bee" then
    take_damage_enemy(other)
  end
end

-- Daño que recibe el jugador. Se llama desde on_collision (box_collider), así
-- la zona vulnerable sigue siendo del tamaño del cuerpo y no del ataque.
function receive_damage(other)

  local otherTag = get_tag(other)

  -- Daño según el tipo de enemigo
  local dmg = 0
  if otherTag == "enemy01" or otherTag == "trap" then
    dmg = 10
  elseif otherTag == "bee" then
    dmg = 15
  elseif otherTag == "saw" then
    dmg = 30
  else
    return
  end

  if damage_cooldown > 0 then
    return
  end

  damage_cooldown = 60

  local health = get_health(this)

  print("Health received:", health)

  health = health - dmg

  increment_health(this, health)

  print("Vida player:", health)

  if health <= 0 then
    die()
  end
end


function take_damage_enemy(enemy)
  local health = get_health(enemy)

  print("Vida enemigo antes:", health)

  health = health - 10

  increment_health(enemy, health)

  print("Vida enemigo despues:", health)

  if health <= 0 then
    kill_entity(enemy)
  elseif get_tag(enemy) == "bee" then
    -- Si la abeja sobrevive al golpe, muestra su animación de daño.
    change_animation(enemy, "bee_hit")
  end
end

----------------------------------------------------------------
-- MUERTE
----------------------------------------------------------------
function die()
  if isDead then
    return
  end

  print("Die")

  isDead = true
  player_state = player_states["DIE"]

  change_animation(this, "player_frog_die")
  play_sound("dieSound")
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

  if damage_cooldown > 0 then
  damage_cooldown = damage_cooldown - 1
  end

  -- Si está muriendo, mantener anim de muerte
  if player_state == player_states["DIE"] then
    change_animation(this, "player_frog_die")
    return
  end

  -- Dash
  if is_dashing then
    if player_state ~= player_states["DASH"] then
      player_state = player_states["DASH"]
      change_animation(this, "player_frog_dash")
    end

    if dash_direction > 0 then
      flip_sprite(this, false)
    else
      flip_sprite(this, true)
    end

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

