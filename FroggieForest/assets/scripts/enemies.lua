enemies = 
{
  enemy01 = {
    components = {
       sprite = {
          assetId = "enemy01_idle",
          width = 16,
          height = 48,
          src_rect = {x = 0, y = 0}, 
        },
    animation = {
          num_frames = 8,
          speed_rate = 3,
          is_loop = true,
        },
    rigid_body = {
          is_dynamic = false,
          is_solid = false,
          mass = 0,
        },
    box_collider = {
          width = 16,
          height = 48,
          offset = {x = 0, y = 0},
        },
    script = {
            path = "./assets/scripts/enemy01.lua",
        },
        tag = {
          tag = "enemy01",
        },
        
    }
  },
}