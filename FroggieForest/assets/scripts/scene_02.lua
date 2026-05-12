scene = {
  -- Tabla de imágenes y sprites
  sprites = {
    [0] = 
   -- {assetId = "background", filePath = "./assets/images/backgroundl1.png",},
    {assetId = "frog_idle", filePath = "./assets/images/frog_idle.png",},
    {assetId = "frog_jump", filePath = "./assets/images/frog_jump.png",},
    {assetId = "frog_fall", filePath = "./assets/images/frog_fall.png",},
    {assetId = "frog_run", filePath = "./assets/images/frog_run.png",},
    {assetId = "frog_die", filePath = "./assets/images/frog_die.png",},
    {assetId = "frog_attack", filePath = "./assets/images/frog_attack.png",},
    {assetId = "mushroom_idle", filePath = "./assets/images/mushroom_idle.png",},
    {assetId = "mushroom_fall", filePath = "./assets/images/mushroom_fall.png",},
    {assetId = "mushroom_run", filePath = "./assets/images/mushroom_run.png",},
    {assetId = "terrain", filePath = "./assets/images/terrain.png",},
  },

  -- Tabla con la Info de las animaciones
  animations = {
    [0] = 
    {animation_id = "player_frog_idle", texture_id = "frog_idle", w = 32, h = 32, num_frames = 11, speed_rate = 5, is_loop = true,},
    {animation_id = "player_frog_jump", texture_id = "frog_jump", w = 32, h = 32, num_frames = 01, speed_rate = 01, is_loop = true,},
    {animation_id = "player_frog_fall", texture_id = "frog_fall", w = 32, h = 32, num_frames = 01, speed_rate = 01, is_loop = true,},
    {animation_id = "player_frog_run" , texture_id = "frog_run",  w = 32, h = 32, num_frames = 10, speed_rate = 10, is_loop = true,},
    {animation_id = "player_frog_die" , texture_id = "frog_die",  w = 32, h = 32, num_frames = 3, speed_rate = 10, is_loop = true,},
    {animation_id = "player_frog_attack", texture_id = "frog_attack", w = 42, h = 32, num_frames = 8, speed_rate = 10, is_loop = true,},
    {animation_id = "enemy01_idle", texture_id = "mushroom_idle", w = 80, h = 80, num_frames = 7, speed_rate = 5, is_loop = true,},
    {animation_id = "enemy01_run" , texture_id = "mushroom_run",  w = 80, h = 80, num_frames = 7, speed_rate = 5, is_loop = true,},
  
  },
  
  -- Tabla de fuentes
  fonts = {},


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
  buttons = {},

  maps = {
    map_path = "./assets/maps/level01.tmx",
    tile_path = "./assets/maps/terrain.tsx",
    tile_name = "terrain",
  },

  -- Tabla de Entidades
  entities = {
    [0] = 
    -- Player
    {
      components = {
        animation = {
          num_frames = 11,
          speed_rate = 10,
          is_loop = true,
        },
        camera_follow = {
        },
        box_collider = {
          width = 32,
          height = 32,
          offset = {x = 0, y = 0},
        },
        rigid_body = {
          is_dynamic = true,
          is_solid = true,
          mass = 10,
        },
        script = {
          path = "./assets/scripts/player_frog.lua",
        },
        sprite = {
          assetId = "frog_idle",
          width = 32,
          height = 32,
          src_rect = {x = 0, y = 0},
        },
        tag = {
          tag = "player",
        },
        transform = {
          position = {x = 50.0, y = 300.0},
          scale = {x = 1.0, y = 1.0},
          rotation = 0.0,
        },
      }
    },
}
}
