function on_awake()
  set_velocity(this, -50, 0)
end


function on_collision(other)
  this_tag = get_tag(this)
  other_tag = get_tag(other)
  

  if other_tag == "Barrier Gem" then
    if left_collision(this, other) then
      print("Left collision with Barrier Gem")
      --* Evitar sobre posicion
      this_x, this_y = get_position(this)
      this_vel_x, this_vel_y = get_velocity(this)
      other_x, other_y = get_position(other)
      other_w, other_h = get_size(other)

      set_position(this, other_x + other_w + 1, this_y)

      --* Resolver la colision
      set_velocity(this, -this_vel_x, this_vel_y)
    end
    if right_collision(this, other) then
      print("Right collision with Barrier Gem")
      --* Evitar sobre posicion
      this_x, this_y = get_position(this)
      this_w, this_h = get_size(this)
      this_vel_x, this_vel_y = get_velocity(this)
      other_x, other_y = get_position(other)

      set_position(this, other_x - this_w - 1, this_y)

      --* Resolver la colision
      set_velocity(this, -this_vel_x, this_vel_y)
    end
  end
end