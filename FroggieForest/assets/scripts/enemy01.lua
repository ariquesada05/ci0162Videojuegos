-- Enemigo tipo "goomba": patrulla de lado a lado y se devuelve al chocar
-- con una pared o al llegar al borde de una plataforma (abismo).
--
-- La dirección se deduce del signo de la velocidad, que es propia de cada
-- entidad; así varios enemigos se mueven de forma independiente sin compartir
-- estado global.

enemy_speed = 60

-- Se llama una vez al crear el enemigo.
function on_init()
  -- Arranca caminando hacia la derecha con la animación de correr.
  set_velocity(this, enemy_speed, 0)
  change_animation(this, "enemy01_run")
  flip_sprite(this, false)
end

function update()
  local x, y = get_position(this)
  local w, h = get_size(this)

  -- Dirección actual según la velocidad (1 = derecha, -1 = izquierda).
  local vx = get_velocity(this)
  local dir = 1
  if vx < 0 then
    dir = -1
  end

  -- Punto de sondeo justo delante del enemigo (con un pequeño margen).
  local ahead_x
  if dir == 1 then
    ahead_x = x + w + 2
  else
    ahead_x = x - 2
  end

  local mid_y  = y + h * 0.5 -- altura media: detecta paredes
  local foot_y = y + h + 4   -- bajo los pies: detecta si hay suelo

  local wall_ahead   = is_solid_at(ahead_x, mid_y)
  local ground_ahead = is_solid_at(ahead_x, foot_y)

  -- Se devuelve si hay una pared delante o si no hay suelo (borde de abismo).
  if wall_ahead or not ground_ahead then
    dir = -dir
  end

  set_velocity(this, dir * enemy_speed, 0)
  flip_sprite(this, dir < 0)
end

function on_collision(other)
end
