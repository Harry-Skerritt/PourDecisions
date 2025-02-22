//-------------------------------------------------------------------------------------------------------------
//|                                      Written by Harry Skerritt - 2025                                     |
//|  Available from: https://github.com/Harry-Skerritt/PourDecisions/blob/master/src/Managers/AudioManager.h  |
//-------------------------------------------------------------------------------------------------------------

#ifndef AUDIOMANAGER_H
#define AUDIOMANAGER_H

#include <SFML/Audio.hpp>
#include <map>
#include <memory>
#include <string>

class AudioManager {
public:
    // Singleton access
    static AudioManager& getInstance();

    // Load music or sound effect
    bool loadMusic(const std::string& name, const std::string& filepath);
    bool loadSoundEffect(const std::string& name, const std::string& filepath);

    // Control music
    void playMusic(const std::string& name, bool loop = true);
    void pauseMusic();
    void stopMusic();
    void setMusicVolume(float volume);

    float getMusicVolume();


    // Control sound effects
    void playSoundEffect(const std::string& name, float volume = 100.0f);
    void stopAllSoundEffects();
    void setSoundEffectVolume(const std::string& name, float volume);
    void setGlobalSoundEffectVolume(float volume);

    float getSoundEffectVolume();

private:
    AudioManager() = default;
    ~AudioManager() = default;

    float musicVolume = 50.0f;
    float soundEffectVolume = 100.0f;

    // Prevent copy/move constructors
    AudioManager(const AudioManager&) = delete;
    AudioManager& operator=(const AudioManager&) = delete;

    std::map<std::string, std::unique_ptr<sf::Music>> musicMap;  // Store music as unique_ptr
    std::map<std::string, sf::SoundBuffer> soundBuffers;         // Store sound buffers
    std::map<std::string, sf::Sound> sounds;                    // Store sound effects


};

#endif // AUDIOMANAGER_H
