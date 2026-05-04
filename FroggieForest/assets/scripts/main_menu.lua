scene = {
  -- Tabla de imágenes y sprites
  sprites = {},

  animations = {},
  
  -- Tabla de fuentes
  fonts = {
    [0] = 
    {fontId = "font-01", filePath = "./assets/fonts/04B_11__.ttf", fontSize = 24,},
    {fontId = "font-02", filePath = "./assets/fonts/04B_11__.ttf", fontSize = 32,},
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

  -- Tabla de Mapa
  maps = {
    width = 800,
    height = 600,
  },

  -- Tabla de Entidades
  entities = {
    [0] = 
    {
      components = {
        clickable = {},
        text = {
          text = "Froggie Forest",
          fontId = "font-02",
          r = 23,
          g = 100,
          b = 45,
          a = 255,
        },
        transform = {
          position = {x = 50.0, y = 50.0},
          scale = {x = 1.0, y = 1.0},
          rotation = 0.0,

        },
      }
    },
    {
      components = {
        clickable = {},
        script = {
          path = "./assets/scripts/menu_button.lua",
        },
        text = {
          text = "Level 01",
          fontId = "font-01",
          r = 231,
          g = 100,
          b = 100,
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
