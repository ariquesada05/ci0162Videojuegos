#include "AudioManager.hpp"
#include <iostream>

AudioManager::AudioManager() {
    // std::cout << "[AUDIOMANAGER] Constructor" << std::endl;
}

AudioManager::~AudioManager() {
    // std::cout << "[AUDIOMANAGER] Destructor" << std::endl;
    clearAudio();
}

void AudioManager::ClearAudio() {
    for (auto& music : musicTracks) {
        Mix_FreeMusic(music.second);
    }
    for (auto& sound : soundEffects) {
        Mix_FreeChunk(sound.second);
    }
    musicTracks.clear();
    soundEffects.clear();
}

void AudioManager::AddMusic(const std::string& musicID, const std::string& filePath) {
    Mix_Music* music = Mix_LoadMUS(filePath.c_str());
    if (music == nullptr) {
        std::cerr << "[AudioManager] Failed to load music: " << Mix_GetError() << std::endl;
        return;
    }
    musicTracks.emplace(musicID, music);
}

Mix_Music* AudioManager::GetMusic(const std::string& musicID) {
    auto it = musicTracks.find(musicID);
    if (it != musicTracks.end()) {
        return it->second;
    }
    std::cerr << "[AudioManager] Music ID not found: " << musicID << std::endl;
    return nullptr;
}

void AudioManager::AddSoundEffect(const std::string& soundID, const std::string& filePath) {
    Mix_Chunk* sound = Mix_LoadWAV(filePath.c_str());
    if (sound == nullptr) {
        std::cerr << "[AudioManager] Failed to load sound effect: " << Mix_GetError() << std::endl;
        return;
    }
    soundEffects.emplace(soundID, sound);
}

Mix_Chunk* AudioManager::GetSoundEffect(const std::string& soundID) {
    auto it = soundEffects.find(soundID);
    if (it != soundEffects.end()) {
        return it->second;
    }
    std::cerr << "[AudioManager] Sound ID not found: " << soundID << std::endl;
    return nullptr;
}

void AudioManager::PlayMusic(const std::string& musicID, int loops) {
    Mix_Music* music = GetMusic(musicID);
    if (music != nullptr) {
        if (Mix_PlayMusic(music, loops) == -1) {
            std::cerr << "[AudioManager] Failed to play music: " << Mix_GetError() << std::endl;
        }
    }
}

void AudioManager::PlaySoundEffect(const std::string& soundID, int loops) {
    Mix_Chunk* sound = GetSoundEffect(soundID);
    if (sound != nullptr) {
        if (Mix_PlayChannel(-1, sound, loops) == -1) {
            std::cerr << "[AudioManager] Failed to play sound effect: " << Mix_GetError() << std::endl;
        }
    }
}

void AudioManager::StopMusic(const std::string& musicID) {
    Mix_Music* music = GetMusic(musicID);
    if (music != nullptr) {
        Mix_HaltMusic();
    }
}

void AudioManager::StopSoundEffect(const std::string& soundID) {
    Mix_Chunk* sound = GetSoundEffect(soundID);
    if (sound != nullptr) {
        Mix_HaltChannel(-1);
    }
}

void AudioManager::StopAllSounds() {
    // std::cout << "[AUDIOMANAGER] Stopping all sounds" << std::endl;

    // stop all sound effects
    Mix_HaltChannel(-1);

    // stop all music
    Mix_HaltMusic();

}
