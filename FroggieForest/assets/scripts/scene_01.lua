scene = {
  -- Tabla de imágenes y sprites
  sprites = {
    [0] = 
    {assetId = "enemy-alan", filePath = "./assets/images/enemy-alan.png",},
    {assetId = "enemy-bon", filePath = "./assets/images/enemy-bon.png",},
    {assetId = "enemy-lips", filePath = "./assets/images/enemy-lips.png",},
    {assetId = "player", filePath = "./assets/images/player-ship.png",},
    {assetId = "background", filePath = "./assets/images/background.png",},
    {assetId = "barrier_gem", filePath = "./assets/images/barrier_gem.png",},
  },

  animations = {},
  
  -- Tabla de fuentes
  fonts = {
    [0] = 
    {fontId = "font-01", filePath = "./assets/fonts/highway_gothic.ttf", fontSize = 16,},
  },

  -- Tabla de acciones y teclas
  keys = {
    [0] = {action = "up", key = 119},
    {action = "left", key = 97},
    {action = "down", key = 115},
    {action = "right", key = 100},
  },

  -- Tabla de acciones y botones del ratón
  buttons = {
    [0] = {name = "shoot", button = 1},
  },

  maps = {
    width = 2000,
    height = 2000,
  },
  -- Tabla de Entidades
  entities = {
    [0] = 
    -- Background
    {
      components = {
        sprite = {
          assetId = "background",
          width = 2000,
          height = 2000,
          src_rect = {x = 0, y = 0},
        },
        transform = {
          position = {x = 0, y = 0},
          scale = {x = 1.0, y = 1.0},
          rotation = 0.0,
        },
      }
    },
    -- Player
    {
      components = {
        camera_follow = {},
        circle_collider = {
          radius = 8,
          width = 16,
          height = 16,
        },
        rigid_body = {
          is_dynamic = false,
          mass = 1,
        },
        script = {
          path = "./assets/scripts/player.lua",
        },
        sprite = {
          assetId = "player",
          width = 16,
          height = 16,
          src_rect = {x = 16, y = 0},
        }, -- Faltaba esta coma aquí
        transform = {
          position = {x = 400.0, y = 200.0},
          scale = {x = 2.0, y = 2.0},
          rotation = 0.0,
        },
      }
    },
    -- Enemy 01
    {
      components = {
        animation = {
          num_frames = 6,
          speed_rate = 10,
          is_loop = true,
        },
        box_collider = {
          width = 16 * 2, -- Recordar que se escala por 2
          height = 16 * 2, -- Recordar que se escala por 2
          offset = {x = 0, y = 0},
        },
        rigid_body = {
          is_dynamic = false,
          is_solid = true,
          mass = 1,
        },
        script = {
          path = "./assets/scripts/enemy_alan.lua",
        },
        sprite = {
          assetId = "enemy-alan",
          width = 16,
          height = 16,
          src_rect = {x = 16, y = 0},
        },
        tag = {
          tag = "Enemy Alan",
        },
        transform = {
          position = {x = 150.0, y = 300.0},
          scale = {x = 2.0, y = 2.0},
          rotation = 0.0,
        },
      }
    },
    -- Enemy02
    -- {
    --   components = {
    --     animation = {
    --       num_frames = 6,
    --       speed_rate = 10,
    --       is_loop = true,
    --     },
    --     box_collider = {
    --       width = 16 * 2, -- Recordar que se escala por 2
    --       height = 16 * 2, -- Recordar que se escala por 2
    --       offset = {x = 0, y = 0},
    --     },
    --     rigid_body = {
        --   is_dynamic = false,
        --   mass = 1,
        -- },
    --     sprite = {
    --       assetId = "enemy-bon",
    --       width = 16,
    --       height = 16,
    --       src_rect = {x = 16, y = 0},
    --     },
    --     tag = {
    --       tag = "Enemy Bon",
    --     },
    --     transform = {
    --       position = {x = 500.0, y = 300.0},
    --       scale = {x = 2.0, y = 2.0},
    --       rotation = 0.0,
    --     },
    --   }
    -- barrera
    {
      components = {
        box_collider = {
          width = 16 * 2, -- Recordar que se escala por 2
          height = 16 * 2, -- Recordar que se escala por 2
          offset = {x = 0, y = 0},
        },
        sprite = {
          assetId = "barrier_gem",
          width = 16,
          height = 16,
          src_rect = {x = 0, y = 0},
        },
        tag = {
          tag = "Barrier Gem",
        },
        transform = {
          position = {x = 100.0, y = 300.0},
          scale = {x = 2.0, y = 2.0},
          rotation = 0.0,
        },
      }
    },
    -- barrera01
    {
      components = {
        box_collider = {
          width = 16 * 2, -- Recordar que se escala por 2
          height = 16 * 2, -- Recordar que se escala por 2
          offset = {x = 0, y = 0},
        },
        sprite = {
          assetId = "barrier_gem",
          width = 16,
          height = 16,
          src_rect = {x = 0, y = 0},
        },
        tag = {
          tag = "Barrier Gem",
        },
        transform = {
          position = {x = 200.0, y = 300.0},
          scale = {x = 2.0, y = 2.0},
          rotation = 0.0,
        },
      }
    },
    {
      components = {
        clickable = {},
        text = {
          text = "Hello World!",
          fontId = "font-01",
          r = 23,
          g = 100,
          b = 45,
          a = 255,
        },
        transform = {
          position = {x = 100.0, y = 300.0},
          scale = {x = 1.0, y = 1.0},
          rotation = 0.0,

        },
      }
    },
    
  }
}
