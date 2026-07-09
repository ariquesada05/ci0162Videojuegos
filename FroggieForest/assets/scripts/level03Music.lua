function on_init()
    print("[LUA] Stopping all sounds")
    stop_all_sounds()
    print("[LUA] playing game music")
   
    play_music("l03Music")

    -- Es el último nivel: al superarlo (tocar la zona "win") se vuelve al menú.
    next_scene = "mainMenu"
end