scene = {
  -- Tabla de imágenes y sprites
  sprites = {
    [0] = 
    {assetId = "background", filePath = "./assets/images/back1.png",},
    {assetId = "frog_idle", filePath = "./assets/images/frog_idle.png",},
    {assetId = "frog_jump", filePath = "./assets/images/frog_jump.png",},
    {assetId = "frog_fall", filePath = "./assets/images/frog_fall.png",},
    {assetId = "frog_run", filePath = "./assets/images/frog_run.png",},
    {assetId = "frog_dash", filePath = "./assets/images/frog_run.png",},
    {assetId = "frog_die", filePath = "./assets/images/frog_die.png",},
    {assetId = "frog_attack", filePath = "./assets/images/frog_attack.png",},


    {assetId = "enemy01_idle", filePath = "./assets/images/enemy01_idle.png",},
    {assetId = "enemy01_run", filePath = "./assets/images/enemy01_run.png",},

    -- Abeja (enemigo volador que persigue) y sierra (peligro móvil).
    {assetId = "bee_fly", filePath = "./assets/images/bee_fly.png",},
    {assetId = "bee_attack", filePath = "./assets/images/bee_attack.png",},
    {assetId = "bee_hit", filePath = "./assets/images/bee_hit.png",},
    {assetId = "saw_on", filePath = "./assets/images/Saw/On (38x38).png",},


    {assetId = "forest", filePath = "./assets/images/forest.png",},

    {assetId = "coin", filePath = "./assets/images/coin.png"},
    {assetId = "possion", filePath = "./assets/images/item1.png"},
    {assetId = "diamond", filePath = "./assets/images/item3.png"},

    {assetId = "trap1", filePath = "./assets/images/trap1.png"},
    {assetId = "trap2", filePath = "./assets/images/trap2.png"},
    {assetId = "trap3", filePath = "./assets/images/trap3.png"},
    {assetId = "trap4", filePath = "./assets/images/trap4.png"},
    {assetId = "trap5", filePath = "./assets/images/trap5.png"},


    {assetId = "platform1", filePath = "./assets/images/platform1.png"},
    {assetId = "platform2", filePath = "./assets/images/platform2.png"},
    {assetId = "platform3", filePath = "./assets/images/platform3.png"},
    {assetId = "platform4", filePath = "./assets/images/platform4.png"},
  },
  

  -- Tabla con la Info de las animaciones
  animations = {
    [0] = 
    {animation_id = "player_frog_idle", texture_id = "frog_idle", w = 24, h = 24, num_frames = 4, speed_rate = 5, is_loop = true,},
    {animation_id = "player_frog_jump", texture_id = "frog_jump", w = 26, h = 26, num_frames = 01, speed_rate = 01, is_loop = true,},
    {animation_id = "player_frog_fall", texture_id = "frog_fall", w = 24, h = 24, num_frames = 01, speed_rate = 01, is_loop = true,},
    {animation_id = "player_frog_run" , texture_id = "frog_run",  w = 25, h = 24, num_frames = 10, speed_rate = 10, is_loop = true,},
    {animation_id = "player_frog_dash" , texture_id = "frog_dash",  w = 25, h = 24, num_frames = 10, speed_rate = 15, is_loop = true,},
    {animation_id = "player_frog_die" , texture_id = "frog_die",  w = 24, h = 24, num_frames = 3, speed_rate = 5, is_loop = true,},
    {animation_id = "player_frog_attack", texture_id = "frog_attack", w = 98, h = 24, num_frames = 7, speed_rate = 14, is_loop = true, offset_x = -38,},
    
    {animation_id = "enemy01_idle", texture_id = "enemy01_idle", w = 32, h = 32, num_frames = 9, speed_rate = 2, is_loop = true,},
    {animation_id = "enemy01_run" , texture_id = "enemy01_run",  w = 32, h = 32, num_frames = 9, speed_rate = 3, is_loop = true,},

    {animation_id = "bee_fly",    texture_id = "bee_fly",    w = 64, h = 64, num_frames = 4, speed_rate = 6, is_loop = true,},
    {animation_id = "bee_attack", texture_id = "bee_attack", w = 64, h = 64, num_frames = 4, speed_rate = 8, is_loop = true,},
    {animation_id = "bee_hit",    texture_id = "bee_hit",    w = 64, h = 64, num_frames = 4, speed_rate = 8, is_loop = false,},
    {animation_id = "saw_on",     texture_id = "saw_on",     w = 38, h = 38, num_frames = 8, speed_rate = 16, is_loop = true,},

    {animation_id = "platform_3", texture_id = "platform1", w = 100, h = 14, num_frames = 1, speed_rate = 1, is_loop = true},
    {animation_id = "platform_2", texture_id = "platform2", w = 100, h = 14, num_frames = 1, speed_rate = 1, is_loop = true},
    {animation_id = "platform_1", texture_id = "platform3", w = 100, h = 14, num_frames = 1, speed_rate = 1, is_loop = true},
    {animation_id = "platform_0", texture_id = "platform4", w = 100, h = 14, num_frames = 1, speed_rate = 1, is_loop = true},
  
  },

   -- sounds table
  sounds = {
        [0] =
        {soundId = "dieSound", filePath ="./assets/sounds/dieSound.mp3"},
    },

    -- music table
  music = { 
    [0] =
        {musicId = "l01Music" ,filePath ="./assets/sounds/journey.mp3"},
      },
  -- Tabla de fuentes
  fonts = {
    [0] = 
    {fontId = "mainFont", filePath = "./assets/fonts/VarelaRound-Regular.ttf", fontSize = 32},

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
    {action = "dash", key = 99},
  },

  -- Tabla de acciones y botones del ratón
  buttons = {},

  maps = {
    map_path = "./assets/maps/nivel01.tmx",
    tile_path = "./assets/maps/forest si.tsx",
    tile_name = "forest",
  },

  stats = {
    [0] =

    {tag = "player", health = 100, points = 0, damage = 1},
    {tag = "enemy01", health = 20, points = 0, damage = 1},
    {tag = "bee", health = 20, points = 0, damage = 15},
  },
  -- Tabla de Entidades
  entities = {
    [0] = 
    -- Music

    {
      components = {
        script = { 
          path = "./assets/scripts/level01Music.lua",
        },
      }
    },
    --level
    {
      components = {
        animation = {
          num_frames = 4,
          speed_rate = 10,
          is_loop = true,
        },
        camera_follow = {
        },
        box_collider = {
          width = 40,
          height = 48,
          offset = {x = 0, y = 0},
        },
        rigid_body = {
          is_dynamic = true,
          is_solid = true,
          mass = 10,
        },
        script = {
          path = "./assets/scripts/playerFrog.lua",
        },
        sprite = {
          assetId = "frog_idle",
          width = 24,
          height = 24,
          src_rect = {x = 0, y = 0},
          z_index = 3, -- el jugador se dibuja por encima de todo
        },
        transform = {
          position = {x = 40.0, y = 200.0},
          scale = {x = 2.0, y = 2.0},
          rotation = 0.0,
        },
        tag = {
          tag = "player",
        },
        lapse = {
          [0] = {
            name = "damage",
            seconds = 0.5,
          },
            {
              name = "attack",
              seconds = 0.6,
              }
        },
        -- Hitbox de ataque: más ancho que el cuerpo (box de 40) y centrado
        -- con el offset, para que el golpe alcance el doble de distancia a
        -- cada lado. Solo afecta al ataque; la física usa el box_collider.
        damage_collider = {
        width = 128,
        height = 48,
        offset = {x = -64, y = 0},
      },
      }
    },
  },
}
