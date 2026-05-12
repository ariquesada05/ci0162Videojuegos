function on_init()
    -- stop all sound from previous scene
    print("[LUA] Stopping all sounds")
    stop_all_sounds()

    print("[LUA] playing game music")
    -- ResetCamera()  -- solo si también la has expuesto a Lua
    play_music("menuMusic")
end
