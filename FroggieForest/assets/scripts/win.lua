scene = {
  -- Tabla de imágenes y sprites
  sprites = {
      [0] =
      {assetId = "background", filePath = "./assets/images/background.png"}, 
  },

  animations = {},
  

    -- sounds table
  sounds = {},
    -- music table
  music = { [0] =
        {musicId = "menuMusic",filePath = "./assets/sounds/town.mp3"},
      },

  -- Tabla de fuentes
  fonts = {
    [0] = 
    {fontId = "font-01", filePath = "./assets/fonts/toad.otf", fontSize = 50},
    {fontId = "font-02", filePath = "./assets/fonts/toad.otf", fontSize = 70},
  },

  -- Tabla de acciones y teclas
keys = {
    [0] = 
    {action = "up", key = 1073741906},
    {action = "left", key = 1073741904},
    {action = "down", key = 1073741905},
    {action = "right", key = 1073741903},
    {action = "jump", key = 122},
    {action = "attack", key = 120},
  },

  -- Tabla de acciones y botones del ratón
  buttons = {
    [0] = 
    {name = "shoot", button = 1},
  },

  -- Tabla de Mapa
  maps = {
    -- width = 1600,
    -- height = 960,
  },

  -- Tabla de Entidades
    entities = {
        [0] = 
       -- background
        {
            components = {
                sprite = {
                    assetId = "background",
                    width = 1600,
                    height = 960,
                    src_rect = {x = 0, y = 0},
                },
                transform = {
                    position = {x = 0, y = 0},
                    scale = {x = 1.0, y = 1.0},
                    rotation = 0.0,
                },
            }
        },
    -- --title
    {
      components = {
        text = {
          text = "Winner!",
          fontId = "font-02",
          r = 52, g = 95, b = 87, a = 255  
        },
        transform = {
          position = {x = 225.0, y = 50.0},
          scale = {x = 1.0, y = 1.0},
          rotation = 0.0,

        },
      }
    },

    {
      components = {
        clickable = {},
        camera_follow = {},
        script = {
          path = "./assets/scripts/goToMain.lua",
        },
        text = {
          text = "Congratulations! You Win!",
          fontId = "font-01",
          r = 70, g = 140, b = 180, a = 255
        },
        transform = {
          position = {x = 200.0, y = 220.0},
          scale = {x = 1.0, y = 1.0},
          rotation = 0.0,

        },
      }
    },

    {
      components = {
        clickable = {},
        camera_follow = {},
        script = {
          path = "./assets/scripts/goToMain.lua",
        },
        text = {
          text = "Back to Main Menu",
          fontId = "font-01",
          r = 120,
          g = 40,
          b = 40,
          a = 255,
        },
        transform = {
          position = {x = 220.0, y = 350.0},
          scale = {x = 1.0, y = 1.0},
          rotation = 0.0,

        },
      }
    },
  }
}
