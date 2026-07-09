ANT_SPEED = 100
ANT_RANGE = 200
ANT_ATTACK_RANGE = 40

function update()
  local ax, ay = get_position(this)
  local px, py = get_player_position()

  local dx = px - ax

  if math.abs(dx) <= ANT_RANGE then
    if math.abs(dx) <= ANT_ATTACK_RANGE then
      set_velocity(this, 0, 0)
      change_animation(this, "ant_attack")
    else
      if dx < 0 then
        set_velocity(this, -ANT_SPEED, 0)
        flip_sprite(this, true)
      else
        set_velocity(this, ANT_SPEED, 0)
        flip_sprite(this, false)
      end

      change_animation(this, "ant_walk")
    end
  else
    set_velocity(this, 0, 0)
    change_animation(this, "ant_idle")
  end
end