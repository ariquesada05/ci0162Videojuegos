-- Comportamiento de la plataforma que desaparece.
--
-- Reglas:
--   * Solo empieza a desaparecer cuando el jugador está APOYADO ENCIMA
--     (no cuenta si la golpea de lado o desde abajo).
--   * La plataforma no se mueve (eso se garantiza con la masa alta en
--     platforms.lua; aquí no tocamos su posición).
--   * Tras desaparecer por completo, vuelve a aparecer después de 2 segundos.

local FULL_STATE       = 3    -- estados de desvanecimiento: 3 -> 2 -> 1 -> 0
local FRAMES_PER_STATE = 24   -- ~0.4 s por fase (juego a 60 FPS)
local REAPPEAR_FRAMES  = 120  -- 2 s a 60 FPS antes de reaparecer

-- Deben coincidir con el box_collider definido en platforms.lua.
local COLLIDER_W    = 58
local COLLIDER_H    = 14
local SURFACE_OFFSET = 0      -- la barra está en el borde superior del sprite

local state          = FULL_STATE
local timer          = 0
local activated      = false
local disappeared    = false
local reappear_timer = 0

-- Determina si el jugador está apoyado sobre la superficie de la plataforma.
local function player_is_on_top(other)
  local _, vy = get_velocity(other)

  -- Si viene subiendo es un golpe desde abajo: no cuenta.
  if vy < 0 then
    return false
  end

  local _, py = get_position(other)
  local _, ph = get_size(other)
  local _, ty = get_position(this)

  local player_center = py + ph / 2
  local surface       = ty + SURFACE_OFFSET

  -- El centro del jugador queda por encima de la superficie => está encima,
  -- no chocando de lado (donde el centro caería a la altura del collider).
  return player_center < surface
end

local function disappear()
  disappeared    = true
  reappear_timer = 0
  -- Desactiva el collider para que el jugador deje de apoyarse.
  set_collider_size(this, 0, 0)
end

local function reappear()
  disappeared    = false
  activated      = false
  state          = FULL_STATE
  timer          = 0
  reappear_timer = 0
  set_collider_size(this, COLLIDER_W, COLLIDER_H)
  change_animation(this, "platform_3")
end

function on_init()
  change_animation(this, "platform_3")
end

function on_collision(other)
  if disappeared or activated then
    return
  end

  if get_tag(other) ~= "player" then
    return
  end

  if player_is_on_top(other) then
    activated = true
  end
end

function update()
  -- Fase de reaparición: ya desapareció, esperar 2 s y volver.
  if disappeared then
    reappear_timer = reappear_timer + 1
    if reappear_timer >= REAPPEAR_FRAMES then
      reappear()
    end
    return
  end

  -- Todavía no la pisaron.
  if not activated then
    return
  end

  timer = timer + 1
  if timer < FRAMES_PER_STATE then
    return
  end

  timer = 0
  state = state - 1

  if state == 2 then
    change_animation(this, "platform_2")
  elseif state == 1 then
    change_animation(this, "platform_1")
  elseif state <= 0 then
    change_animation(this, "platform_0")
    disappear()
  end
end
