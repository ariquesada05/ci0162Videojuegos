-- ============================================================================
-- Enemigo "jabalí" (boar). Tres comportamientos:
--
--   1. PATRULLA: camina de lado a lado con la animación "boar_walk", girando al
--      chocar con una pared o al llegar al borde de un abismo (igual que el
--      hongo/enemy01). Caminar NO hace daño.
--   2. EMBESTIDA: si detecta al jugador dentro de un radio (un poco mayor que el
--      de la abeja) y a una altura parecida, corre hacia él con "boar_run" hasta
--      chocar con una pared, un abismo o el propio jugador.
--   3. RECUPERACIÓN: tras terminar una embestida se queda un instante quieto con
--      "boar_idle" y luego vuelve a patrullar.
--
-- Si la embestida choca con el jugador, este pierde 8 de vida y sale empujado
-- en la dirección a la que mira el jabalí. La embestida tiene 4 s de cooldown.
--
-- El DAÑO y el EMPUJE los aplica playerFrog.lua (a través de los globales
-- boar_hit_damage / boar_hit_dir), porque la velocidad del jugador se reescribe
-- cada frame en su propio update; así el empujón respeta invulnerabilidad,
-- i-frames y muerte.
--
-- Para USARLO en un nivel: declarar en ese nivel los sprites boar_idle/boar_walk/
-- boar_run y sus animaciones, y colocar en el mapa (.tmx), dentro del
-- objectgroup "spawn", un objeto con name="boar".
-- ============================================================================

-- Estado por-entidad (permite varios jabalíes sin compartir variables).
boar_data = boar_data or {}

BOAR_WALK_SPEED      = 55         -- px/segundo al patrullar
BOAR_CHARGE_SPEED    = 260        -- px/segundo al embestir
local TILE           = 16
BOAR_DETECT_RADIUS   = 14 * TILE  -- 224px: un poco más que la abeja (176px)
BOAR_VERTICAL_TOL    = 48         -- solo embiste si el jugador está a altura similar
BOAR_ATTACK_COOLDOWN = 4 * 60     -- 4 segundos (frames a 60 FPS)
BOAR_RECOVER_FRAMES  = 30         -- pausa quieto (idle) tras cada embestida

-- Estados
local S_PATROL  = 0
local S_CHARGE  = 1
local S_RECOVER = 2

local function get_state(id)
  local d = boar_data[id]
  if d == nil then
    d = { st = S_PATROL, dir = 1, cd = 0, recover = 0, anim = "" }
    boar_data[id] = d
  end
  return d
end

-- Cambia la animación solo si es distinta (no reinicia el frame cada cuadro).
local function set_anim(d, name)
  if d.anim ~= name then
    d.anim = name
    change_animation(this, name)
  end
end

-- ¿Hay una pared delante o falta suelo (borde de abismo) en la dirección dir?
-- Igual que enemy01: sondea un punto justo delante, a media altura (pared) y
-- bajo los pies (suelo).
local function blocked_ahead(dir)
  local x, y = get_position(this)
  local w, h = get_size(this)

  local ahead_x
  if dir == 1 then
    ahead_x = x + w + 2
  else
    ahead_x = x - 2
  end

  local mid_y  = y + h * 0.5
  local foot_y = y + h + 4

  local wall_ahead   = is_solid_at(ahead_x, mid_y)
  local ground_ahead = is_solid_at(ahead_x, foot_y)

  return wall_ahead or (not ground_ahead)
end

function on_init()
  local id = get_id(this)
  boar_data[id] = { st = S_PATROL, dir = 1, cd = 0, recover = 0, anim = "" }
  local d = boar_data[id]
  set_anim(d, "boar_walk")
  set_velocity(this, d.dir * BOAR_WALK_SPEED, 0)
  -- El arte mira a la izquierda por defecto (como el hongo): se voltea al ir a
  -- la derecha.
  flip_sprite(this, d.dir > 0)
end

function update()
  local id = get_id(this)
  local d = get_state(id)

  if d.cd > 0 then
    d.cd = d.cd - 1
  end

  -- Distancia al jugador (centro a centro).
  local bx, by = get_position(this)
  local bw, bh = get_size(this)
  local bcx = bx + bw * 0.5
  local bcy = by + bh * 0.5
  local px, py = get_player_position()
  local dx = px - bcx
  local dy = py - bcy
  local dist = math.sqrt(dx * dx + dy * dy)

  if d.st == S_PATROL then
    -- Caminar de lado a lado; girar en pared/abismo.
    if blocked_ahead(d.dir) then
      d.dir = -d.dir
    end
    set_velocity(this, d.dir * BOAR_WALK_SPEED, 0)
    flip_sprite(this, d.dir > 0)
    set_anim(d, "boar_walk")

    -- Detectar al jugador y embestir (si el cooldown lo permite y está a una
    -- altura parecida, para no cargar contra jugadores en otra plataforma).
    if d.cd <= 0 and dist <= BOAR_DETECT_RADIUS and math.abs(dy) <= BOAR_VERTICAL_TOL then
      if dx >= 0 then d.dir = 1 else d.dir = -1 end
      d.st = S_CHARGE
      d.cd = BOAR_ATTACK_COOLDOWN  -- la habilidad entra en cooldown al iniciar
      flip_sprite(this, d.dir > 0)
      set_anim(d, "boar_run")
    end

  elseif d.st == S_CHARGE then
    -- Correr hasta chocar con pared/abismo. El choque con el jugador lo maneja
    -- on_collision.
    if blocked_ahead(d.dir) then
      set_velocity(this, 0, 0)
      d.st = S_RECOVER
      d.recover = BOAR_RECOVER_FRAMES
      set_anim(d, "boar_idle")
    else
      set_velocity(this, d.dir * BOAR_CHARGE_SPEED, 0)
      flip_sprite(this, d.dir > 0)
      set_anim(d, "boar_run")
    end

  elseif d.st == S_RECOVER then
    set_velocity(this, 0, 0)
    set_anim(d, "boar_idle")
    d.recover = d.recover - 1
    if d.recover <= 0 then
      d.st = S_PATROL
    end
  end
end

function on_collision(other)
  if get_tag(other) ~= "player" then
    return
  end

  local id = get_id(this)
  local d = get_state(id)

  -- Solo la embestida hace daño; caminar (patrulla) no.
  if d.st == S_CHARGE then
    -- Pide a playerFrog.lua que aplique 8 de daño y empuje al jugador en la
    -- dirección a la que mira el jabalí.
    boar_hit_damage = 8
    boar_hit_dir = d.dir

    -- Termina la embestida y se queda un momento quieto.
    set_velocity(this, 0, 0)
    d.st = S_RECOVER
    d.recover = BOAR_RECOVER_FRAMES
    set_anim(d, "boar_idle")
  end
end
