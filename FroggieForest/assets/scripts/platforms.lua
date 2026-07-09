-- Datos de las plataformas que se cargan desde el mapa (objectgroup "platforms").
-- La clave de cada plataforma debe coincidir con el "name" del objeto en el .tmx.
-- El objeto del nivel se llama "dissapears", así que esa es la clave aquí.
platforms =
{
  dissapears = {
    components = {

      sprite = {
        assetId = "platform1",
        width = 100,
        height = 14,
        src_rect = {x = 0, y = 0},
        z_index = 2,
      },

      animation = {
        num_frames = 1,
        speed_rate = 1,
        is_loop = true,
      },

      -- Masa enorme (igual que los "floor" del mapa) para que en la
      -- resolución de colisiones el jugador sea el que se reposiciona y la
      -- plataforma NO se mueva hacia abajo ni hacia los lados.
      rigid_body = {
        is_dynamic = false,
        is_solid = true,
        mass = 9999999999.0,
      },

      -- La imagen se recortó a 100x14 con la barra pegada arriba. La colisión
      -- usa la esquina superior del sprite (el offset se ignora en el motor),
      -- así que la rana se apoya justo sobre la barra visible.
      box_collider = {
        width = 58,
        height = 14,
        offset = {x = 0, y = 0},
      },

      script = {
        path = "./assets/scripts/disappearingPlatform.lua",
      },

      -- El jugador reconoce este tag para poder volver a saltar al apoyarse.
      tag = {
        tag = "dissappears",
      },

      transform = {
        position = {x = 0, y = 0},
        scale = {x = 1.0, y = 1.0},
        rotation = 0.0,
      },
    },
  },
}
