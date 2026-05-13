scene = {
  -- Tabla de imágenes y sprites
  sprites = {
      [0] =
      {assetId = "background", filePath = "./assets/images/background.png"}, 
  },

  animations = {},
  
    -- sounds table
  sounds = {
    },

    -- music table
  music = {
        [0] =
        {musicId = "menuMusic",filePath ="./assets/sounds/FUT.mp3"},
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

  },

  -- Tabla de Mapa
  maps = {
    -- width = 800,
    -- height = 600,
  },

  -- Tabla de Entidades
    entities = {
        [0] = 

         -- music player
        {
            components = {
                script = {
                    path = "./assets/scripts/musicMainMenu.lua"
                },
            }
        },
       -- background
        {
            components = {
                sprite = {
                    assetId = "background",
                    width = 800,
                    height = 600,
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
          text = "Froggie Forest",
          fontId = "font-02",
          r = 90, g = 120, b = 70, a = 255    
            },
        transform = {
          position = {x = 225.0, y = 50.0},
          scale = {x = 1.0, y = 1.0},
          rotation = 0.0,

        },
      }
    },
    -- level 01
    {
      components = {
        clickable = {},
        camera_follow = {},
        script = {
          path = "./assets/scripts/menuButton.lua",
        },
        text = {
          text = "Level 01",
          fontId = "font-01",
          r = 120,
          g = 40,
          b = 40,
          a = 255,
        },
        transform = {
          position = {x = 50.0, y = 150.0},
          scale = {x = 1.0, y = 1.0},
          rotation = 0.0,

        },
      }
    },
  }
}
