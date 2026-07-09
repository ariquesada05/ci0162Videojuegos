-- ============================================================================
-- Trampa "sierra": gira sobre sí misma y se desplaza de un lado a otro sobre un
-- tramo fijo, haciendo 30 de daño al jugador. No le afecta la gravedad
-- (is_dynamic=false) ni empuja al jugador (is_solid=false): es un peligro que
-- hay que esquivar o saltar.
--
-- El DAÑO al jugador lo aplica playerFrog.lua (rama del tag "saw"), igual que
-- con las trampas de pinchos. Aquí solo gestionamos el vaivén y el giro.
--
-- Para USARLA en un nivel hay que añadir a ese nivel (p. ej. level01.lua):
--
--   sprites = {
--     {assetId = "saw_on", filePath = "./assets/images/Saw/On (38x38).png"},
--   }
--   animations = {
--     {animation_id = "saw_on", texture_id = "saw_on", w = 38, h = 38, num_frames = 8, speed_rate = 16, is_loop = true},
--   }
--
-- Y en el mapa (.tmx), dentro del objectgroup "spawn", un objeto con
-- name="saw" en la posición donde deba aparecer. La entidad se arma sola
-- desde enemies.lua (tabla "saw").
-- ============================================================================

-- Estado por-entidad (permite varias sierras sin compartir variables).
saw_data = saw_data or {}

SAW_SPEED = 90            -- px/segundo
SAW_RANGE = 120          -- distancia (px) que recorre a cada lado del origen

local function get_state(id)
  local d = saw_data[id]
  if d == nil then
    d = {}
    saw_data[id] = d
  end
  return d
end

function on_init()
  local id = get_id(this)
  local x, y = get_position(this)
  saw_data[id] = { start_x = x, dir = 1 }
  change_animation(this, "saw_on")
  set_velocity(this, SAW_SPEED, 0)
end

function update()
  local id = get_id(this)
  local d = get_state(id)

  -- Primer update tras un reinicio: fija el origen si aún no existe.
  if d.start_x == nil then
    local x = get_position(this)
    d.start_x = x
    d.dir = 1
  end

  local x = get_position(this)

  -- Invertir la dirección al llegar a los límites del recorrido.
  if x > d.start_x + SAW_RANGE then
    d.dir = -1
  elseif x < d.start_x - SAW_RANGE then
    d.dir = 1
  end

  set_velocity(this, d.dir * SAW_SPEED, 0)
end

function on_collision(other)
  -- El daño al jugador lo gestiona playerFrog.lua (tag "saw").
end
