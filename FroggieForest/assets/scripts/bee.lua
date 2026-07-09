bee_data = bee_data or {}

BEE_SPEED     = 120          -- px/segundo
local TILE    = 16           -- tamaño de tile del mapa (level01.tmx: 16px)
DETECT_RADIUS = 11 * TILE    -- radio de persecución: ~11 tiles (176px)
ATTACK_RANGE  = 20           -- distancia a la que reproduce la animación de ataque

local function get_state(id)
  local d = bee_data[id]
  if d == nil then
    d = { anim = "" }
    bee_data[id] = d
  end
  return d
end

local function set_anim(id, name)
  local d = get_state(id)
  if d.anim ~= name then
    d.anim = name
    change_animation(this, name)
  end
end

function on_init()
  local id = get_id(this)
  bee_data[id] = { anim = "" }
  set_anim(id, "bee_fly")
end

function update()
  local id = get_id(this)

  -- Centro de la abeja
  local bx, by = get_position(this)
  local bw, bh = get_size(this)
  local bcx = bx + bw * 0.5
  local bcy = by + bh * 0.5

  -- Centro del jugador
  local px, py = get_player_position()

  local dx = px - bcx
  local dy = py - bcy
  local dist = math.sqrt(dx * dx + dy * dy)

  if dist <= DETECT_RADIUS then
    -- Perseguir: moverse en línea recta hacia el jugador.
    if dist > 0.001 then
      local nx = dx / dist
      local ny = dy / dist
      set_velocity(this, nx * BEE_SPEED, ny * BEE_SPEED)
      flip_sprite(this, dx < 0) -- mira hacia el jugador (invierte si el arte va al revés)
    end

    if dist <= ATTACK_RANGE then
      set_anim(id, "bee_attack")
    else
      set_anim(id, "bee_fly")
    end
  else
    -- Fuera de rango: se queda flotando en el sitio.
    set_velocity(this, 0, 0)
    set_anim(id, "bee_fly")
  end
end

function on_collision(other)

end
