platforms =
{
  disappearing_platform = {
    components = {

      sprite = {
        assetId = "platform1",
        width = 128,
        height = 128,
        src_rect = {x = 0, y = 0},
        z_index = 2,
      },

      animation = {
        num_frames = 1,
        speed_rate = 1,
        is_loop = true,
      },

      rigid_body = {
        is_dynamic = false,
        is_solid = true,
        mass = 0,
      },

      box_collider = {
        width = 96,
        height = 12,
        offset = {x = 0, y = 35},
      },

      script = {
        path = "./assets/scripts/disappearingPlatform.lua",
      },

      tag = {
        tag = "disappearing_platform",
      },

      transform = {
        position = {x = 0, y = 0},
        scale = {x = 1.0, y = 1.0},
        rotation = 0.0,
      },
    },
  },
}