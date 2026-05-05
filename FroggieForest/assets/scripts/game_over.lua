print("GAME OVER start")
scene = {
    -- sprites table
    sprites = {
        [0] = 
        {assetId = "background", filePath = "./assets/images/background.png"},
    },

    -- animations table
    animations = {},

   
    -- font table
    fonts = {
        [0] = 
        {fontId = "font-01", filePath = "./assets/fonts/highway_gothic.ttf", fontSize = 32},
        {fontId = "font-02", filePath = "./assets/fonts/highway_gothic.ttf", fontSize = 24},

    },
    
    -- actions and keys table
   keys = {
    [0] = 
    {action = "up", key = 119},
    {action = "left", key = 97},
    {action = "down", key = 115},
    {action = "right", key = 100},
  },

    -- actions and mouse button table
  buttons = {
    [0] = 
    {name = "shoot", button = 1},
  },

    -- entities table
    entities = {
        [0] =
      
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
        -- title
        {
            components = {
                text = {
                    text = "Game over",
                    fontId = "font-02",
                    r = 255, g = 215, b = 0, a = 255                
                },
                transform = {
                    position = { x = 50, y = 50},
                    scale = { x = 1.5, y = 1.5},
                    rotation = 0.0
                },
            }
        },
        -- level 01
       {
        components = {
        clickable = {},
        camera_follow = {},
        script = {
          path = "./assets/scripts/menu_button.lua",
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
print("GAME OVER END")