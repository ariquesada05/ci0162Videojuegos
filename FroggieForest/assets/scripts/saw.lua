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
