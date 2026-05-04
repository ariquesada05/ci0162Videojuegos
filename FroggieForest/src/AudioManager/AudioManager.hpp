#ifndef AUDIOMANAGER_HPP
#define AUDIOMANAGER_HPP

#include <SDL2/SDL.h> // SDL2 
#include <SDL2/SDL_mixer.h> // SDL2_mixer used for audio

#include <map> // std::map used to store music and sound effects
#include <string> // std::string used for music_id and sound_id

class AudioManager {
private:
    std::map<std::string, Mix_Music*> musicTracks;   // For long music tracks (streamed)
    std::map<std::string, Mix_Chunk*> soundEffects;  // For short sound effects (pre-loaded)

public:
    /**
     * @brief Construct a new AudioManager object
     */
    AudioManager();

    /**
     * @brief Destroy the AudioManager object
     */
    ~AudioManager();

    /**
     * @brief Add music to the audio manager
     * @param music_id The unique identifier for the music
     * @param file_path The file path to the music file
     */
    void AddMusic(const std::string& musicID, const std::string& filePath);

    /**
     * @brief Get music from the audio manager
     * @param music_id The unique identifier for the music
     * @return Mix_Music* The music track
     */
    Mix_Music* GetMusic(const std::string& musicID);

    /**
     * @brief Add sound effect to the audio manager
     * @param sound_id The unique identifier for the sound effect
     * @param file_path The file path to the sound effect file
     */
    void AddSoundEffect(const std::string& soundID, const std::string& filePath);

    /**
     * @brief Get sound effect from the audio manager
     * @param sound_id The unique identifier for the sound effect
     * @return Mix_Chunk* The sound effect
     */
    Mix_Chunk* GetSoundEffect(const std::string& soundID);

    /**
     * @brief Play music
     * @param music_id The unique identifier for the music
     * @param loops The number of times to loop the music (-1 for infinite loops)
     */
    void PlayMusic(const std::string& musicID, int loops = -1);

    /**
     * @brief Play sound effect
     * @param sound_id The unique identifier for the sound effect
     * @param loops The number of times to loop the sound effect (0 for play once)
     */
    void PlaySoundEffect(const std::string& soundID, int loops = 0);

    /**
     * @brief Pause music
     * @param music_id The unique identifier for the music
     */
    void StopMusic(const std::string& musicID);

    /**
     * @brief Pause sound effect
     * @param sound_id The unique identifier for the sound effect
     * @note will probably never be used because sound effects are short and are not looped
     */
    void StopSoundEffect(const std::string& soundID);

    /**
     * @brief Pause all music and sound effects
     */
    void StopAllSounds();

    /**
     * @brief Clear all audio
     */
    void ClearAudio();
};

#endif // AUDIO_MANAGER_HPP
