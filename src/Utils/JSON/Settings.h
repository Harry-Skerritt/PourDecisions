#ifndef SETTINGS_H
#define SETTINGS_H

#include <string>

struct GraphicsSettings {
    int resolutionX;
    int resolutionY;
    bool fullscreen;
};

struct AudioSettings {
    float musicVolume;
    float sfxVolume;
};

struct GameSettings {
    bool nsfwEnabled;
    int winPoints;
};

struct Settings {
    GraphicsSettings graphics;
    AudioSettings audio;
    GameSettings game;

    // Parse JSON string to fill the Settings structure
    static Settings fromFile(const std::string& fileLoc);

    // Getters for user-friendly formatted strings
    std::string getResolution() const;
    bool getFullscreen() const;
    float getMusicVolume() const;
    float getSFXVolume() const;
    bool getNSFWEnabled() const;
    int getWinPoints() const;

    // Save settings to a JSON file
    void saveToFile(const std::string& filename) const;

    // Setters to modify individual settings
    void setResolution(int width, int height);
    void setFullscreen(bool fullscreen);
    void setMusicVolume(float volume);
    void setSFXVolume(float volume);
    void setNSFWEnabled(bool enabled);
    void setWinPoints(int points);

private:
    static int extractInt(const std::string& json, const std::string& key);
    static float extractFloat(const std::string& json, const std::string& key);
    static bool extractBool(const std::string& json, const std::string& key);

    static std::string toJSONString(const Settings& settings);
};

#endif // SETTINGS_H
