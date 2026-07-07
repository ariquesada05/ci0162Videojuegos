enemies = 
{
  enemy01 = {
    components = {
       sprite = {
          assetId = "enemy01_idle",
          width = 32,
          height = 32,
          src_rect = {x = 0, y = 0},
          z_index = 2, -- por encima de las monedas
        },
    animation = {
          num_frames = 9,
          speed_rate = 3,
          is_loop = true,
        },
    rigid_body = {
          is_dynamic = false,
          is_solid = false,
          mass = 0,
        },
    box_collider = {
          width = 32,
          height = 32,
          offset = {x = 0, y = 0},
        },
    script = {
            path = "./assets/scripts/enemy01.lua",
        },
        tag = {
          tag = "enemy01",
        },
        damage_collider = {
        width = 32,
        height = 32,
        offset = {x = 0, y = 0},
      },
      transform = {
      position = {x = 0, y = 0},
      scale = {x = 2.0, y = 2.0},
      rotation = 0.0,
    },
     
  },
}
}