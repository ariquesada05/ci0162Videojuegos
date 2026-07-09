function on_init()
    print("[LUA] Stopping all sounds")
    stop_all_sounds()
    print("[LUA] playing game music")
   
    play_music("l02Music")

    -- Al superar este nivel (tocar la zona "win") se pasa al siguiente.
    next_scene = "level03"
end