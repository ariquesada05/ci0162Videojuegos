-- ============================================================================
-- Enemigo "abeja": persigue al jugador dentro de un radio, no le afecta la
-- gravedad y no atraviesa objetos sólidos (paredes/suelo), igual que el jugador.
--
-- La lógica ya está lista. Para USARLA en un nivel, hay que añadir a ese nivel
-- (p. ej. level01.lua) lo siguiente:
--
--   sprites = {
--     {assetId = "bee_fly",    filePath = "./assets/images/bee_fly.png"},
--     {assetId = "bee_attack", filePath = "./assets/images/bee_attack.png"},
--     {assetId = "bee_hit",    filePath = "./assets/images/bee_hit.png"},
--   }
--   animations = {
--     {animation_id = "bee_fly",    texture_id = "bee_fly",    w = 64, h = 64, num_frames = 4, speed_rate = 6, is_loop = true},
--     {animation_id = "bee_attack", texture_id = "bee_attack", w = 64, h = 64, num_frames = 4, speed_rate = 8, is_loop = true},
--     {animation_id = "bee_hit",    texture_id = "bee_hit",    w = 64, h = 64, num_frames = 4, speed_rate = 8, is_loop = false},
--   }
--   stats = {
--     {tag = "bee", health = 10, points = 0, damage = 15},
--   }
--
-- Y en el mapa (.tmx), dentro del objectgroup "spawn", un objeto con
-- name="bee" en la posición donde deba aparecer. La entidad se arma sola
-- desde enemies.lua (tabla "bee").
-- ============================================================================

-- Estado por-entidad (permite varias abejas sin compartir variables).
bee_data = bee_data or {}

BEE_SPEED     = 120          -- px/segundo
local TILE    = 16           -- tamaño de tile del mapa (level01.tmx: 16px)
DETECT_RADIUS = 4 * TILE     -- radio de persecución: 4 tiles (súbelo si es poco)
ATTACK_RANGE  = 30           -- distancia a la que reproduce la animación de ataque

local function get_state(id)
  local d = bee_data[id]
  if d == nil then
    d = { anim = "" }
    bee_data[id] = d
  end
  return d
end

-- Cambia la animación solo si es distinta (evita reiniciar el frame cada cuadro).
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
  -- El daño al jugador y la muerte de la abeja los gestiona playerFrog.lua
  -- (rama del tag "bee"), igual que con enemy01.
end
