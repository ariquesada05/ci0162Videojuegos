function on_init()
    print("[LUA] Stopping all sounds")
    stop_all_sounds()
    print("[LUA] playing game music")
   
    play_music("l01Music")
end