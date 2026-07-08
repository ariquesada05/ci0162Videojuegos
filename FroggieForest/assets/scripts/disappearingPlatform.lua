local state = 3
local timer = 0
local activated = false
local disappeared = false

local time_per_state = 0.4

function on_collision(this, other)

  if disappeared then
    return
  end

  if get_tag(other) == "player" then
    activated = true
  end
end

function update(this, dt)

  if not activated or disappeared then
    return
  end

  timer = timer + dt

  if timer >= time_per_state then
    timer = 0
    state = state - 1

    local collider = get_box_collider(this)

    if state == 2 then
      change_animation(this, "platform_2")

      collider.width = 64
      collider.height = 12
      collider.offset.x = 0
      collider.offset.y = 35

    elseif state == 1 then
      change_animation(this, "platform_1")

      collider.width = 32
      collider.height = 12
      collider.offset.x = 0
      collider.offset.y = 35

    elseif state == 0 then
      change_animation(this, "platform_0")

      remove_component(this, "box_collider")
      remove_component(this, "rigid_body")

      disappeared = true
    end
  end
end