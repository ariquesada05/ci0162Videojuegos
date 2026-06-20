enemy_states = {
  IDLE = 0,
  RUN = 1,
  DIE = 2,
}

enemy_state = enemy_states["IDLE"]
enemy_speed = 100

start_x = 0
direction = 1
range = 700.0

isDead = false
dieTimer = 0
dieFrames = 30

function update()

  if isDead then
    dieTimer = dieTimer + 1

    if dieTimer >= dieFrames then
      kill_entity(this)
    end

    return
  end

  local pos = get_position(this)

  if start_x == 0 then
    start_x = pos.x
  end

  if pos.x >= start_x + range then
    direction = -1
  elseif pos.x <= start_x - range then
    direction = 1
  end

  local vel_x = direction * enemy_speed

  set_velocity(this, vel_x, 0)

  update_animation_state()
end

function die()
  if isDead then
    return
  end

  print("Enemy Die")

  isDead = true
  enemy_state = enemy_states["DIE"]

  set_velocity(this, 0, 0)
  change_animation(this, "enemy01_die")
end

function on_collision(other)

end

function update_animation_state()
  local x_vel, y_vel = get_velocity(this)

  if enemy_state == enemy_states["DIE"] then
    change_animation(this, "enemy01_die")
    return
  end

  if -0.001 < x_vel and x_vel < 0.001 then
    if enemy_state ~= enemy_states["IDLE"] then
      enemy_state = enemy_states["IDLE"]
      change_animation(this, "enemy01_idle")
    end
    return
  end

  if x_vel >= 0.001 then
    flip_sprite(this, false)

    if enemy_state ~= enemy_states["RUN"] then
      enemy_state = enemy_states["RUN"]
      change_animation(this, "enemy01_run")
    end

    return
  end

  if x_vel <= -0.001 then
    flip_sprite(this, true)

    if enemy_state ~= enemy_states["RUN"] then
      enemy_state = enemy_states["RUN"]
      change_animation(this, "enemy01_run")
    end

    return
  end
end