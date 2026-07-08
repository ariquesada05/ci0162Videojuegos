local state = 3
local timer = 0
local activated = false
local disappeared = false

local time_per_state = 24

function on_collision(other)

  if disappeared then
    return
  end

  if get_tag(other) ~= "player" then
    return
  end

  -- Verifica que el jugador venga cayendo o esté encima
  local vx, vy = get_velocity(other)

  if vy >= 0 then
    activated = true
  end
end

function update()

  if not activated or disappeared then
    return
  end

  timer = timer + 1

  if timer >= time_per_state then
    timer = 0
    state = state - 1

    if state == 2 then
      change_animation(this, "platform_2")

    elseif state == 1 then
      change_animation(this, "platform_1")

    elseif state == 0 then
      change_animation(this, "platform_0")
      disappeared = true
      kill_entity(this)
    end
  end
end