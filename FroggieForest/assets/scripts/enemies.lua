enemies = 
{
  enemy01 = {
    components = {
       sprite = {
          assetId = "enemy01_idle",
          width = 48,
          height = 48,
          src_rect = {x = 0, y = 0}, 
        },
    animation = {
          num_frames = 8,
          speed_rate = 5,
          is_loop = true,
        },
    rigid_body = {
          is_dynamic = true,
          is_solid = true,
          mass = 10,
        },
    box_collider = {
          width = 48,
          height = 48,
          offset = {x = 0, y = 0},
        },
    script = {
            path = "./assets/scripts/enemy01.lua",
        },
        
    }
  },
}