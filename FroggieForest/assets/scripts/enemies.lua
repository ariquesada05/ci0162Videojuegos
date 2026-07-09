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
  },

  -- Abeja: persigue al jugador (ver bee.lua). No le afecta la gravedad
  -- (is_dynamic=false) pero es sólida (is_solid=true) con masa baja, así los
  -- muros/suelo (masa enorme) la bloquean igual que al jugador.
  bee = {
    components = {
      sprite = {
        assetId = "bee_fly",
        width = 64,
        height = 64,
        src_rect = {x = 0, y = 0},
        z_index = 2, -- por encima de las monedas
      },
      animation = {
        num_frames = 4,
        speed_rate = 6,
        is_loop = true,
      },
      rigid_body = {
        is_dynamic = false,
        is_solid = true,
        mass = 1,
      },
      box_collider = {
        width = 48,
        height = 48,
        offset = {x = 0, y = 0},
      },
      script = {
        path = "./assets/scripts/bee.lua",
      },
      tag = {
        tag = "bee",
      },
      damage_collider = {
        width = 48,
        height = 48,
        offset = {x = 0, y = 0},
      },
      transform = {
        position = {x = 0, y = 0},
        scale = {x = 1.0, y = 1.0},
        rotation = 0.0,
      },
    },
  },

  -- Sierra: gira y se mueve de un lado a otro (ver saw.lua). Hace 30 de daño.
  -- No le afecta la gravedad (is_dynamic=false) ni empuja al jugador
  -- (is_solid=false): es un peligro que hay que esquivar.
  saw = {
    components = {
      sprite = {
        assetId = "saw_on",
        width = 38,
        height = 38,
        src_rect = {x = 0, y = 0},
        z_index = 2, -- por encima de las monedas
      },
      animation = {
        num_frames = 8,
        speed_rate = 16,
        is_loop = true,
      },
      rigid_body = {
        is_dynamic = false,
        is_solid = false,
        mass = 0,
      },
      box_collider = {
        width = 50,
        height = 50,
        offset = {x = 0, y = 0},
      },
      script = {
        path = "./assets/scripts/saw.lua",
      },
      tag = {
        tag = "saw",
      },
      transform = {
        position = {x = 0, y = 0},
        scale = {x = 1.5, y = 1.5},
        rotation = 0.0,
      },
    },
  },
}