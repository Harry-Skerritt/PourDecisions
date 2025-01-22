#include "Settings.h"
#include <fstream>
#include <stdexcept>
#include <sstream>

Settings Settings::fromFile(const std::string& fileLoc) {
    std::ifstream inputFile(fileLoc);
    if (!inputFile) {
        throw std::runtime_error("Failed to open: " + fileLoc);
    }

    std::ostringstream oss;
    oss << inputFile.rdbuf();
    std::string json = oss.str();

    Settings settings;

    // Extract values manually
    settings.graphics.resolutionX = extractInt(json, "\"resolution-x\":");
    settings.graphics.resolutionY = extractInt(json, "\"resolution-y\":");
    settings.graphics.fullscreen = extractBool(json, "\"fullscreen\":");

    settings.audio.musicVolume = extractFloat(json, "\"music-volume\":");
    settings.audio.sfxVolume = extractFloat(json, "\"sfx-volume\":");

    settings.game.nsfwEnabled = extractBool(json, "\"nsfw-enabled\":");
    settings.game.winPoints = extractInt(json, "\"win-points\":");

    return settings;
}

void Settings::saveToFile(const std::string& fileLoc) const {
    std::ofstream file(fileLoc);
    if (!file) {
        throw std::runtime_error("Failed to open file for writing: " + fileLoc);
    }

    file << toJSONString(*this);
}

//Setters
void Settings::setResolution(int width, int height) {
    graphics.resolutionX = width;
    graphics.resolutionY = height;
}

void Settings::setFullscreen(bool fullscreen) {
    graphics.fullscreen = fullscreen;
}

void Settings::setMusicVolume(float volume) {
    audio.musicVolume = volume;
}

void Settings::setSFXVolume(float volume) {
    audio.sfxVolume = volume;
}

void Settings::setNSFWEnabled(bool enabled) {
    game.nsfwEnabled = enabled;
}

void Settings::setWinPoints(int points) {
    game.winPoints = points;
}

//Extractors
int Settings::extractInt(const std::string& json, const std::string& key) {
    size_t start = json.find(key);
    if (start == std::string::npos) throw std::runtime_error("Key not found: " + key);
    start += key.length();
    size_t end = json.find_first_of(",}", start);
    return std::stoi(json.substr(start, end - start));
}

float Settings::extractFloat(const std::string& json, const std::string& key) {
    size_t start = json.find(key);
    if (start == std::string::npos) throw std::runtime_error("Key not found: " + key);
    start += key.length();
    size_t end = json.find_first_of(",}", start);
    return std::stof(json.substr(start, end - start));
}

bool Settings::extractBool(const std::string& json, const std::string& key) {
    size_t start = json.find(key);
    if (start == std::string::npos) throw std::runtime_error("Key not found: " + key);
    start += key.length();
    size_t end = json.find_first_of(",}", start);
    std::string value = json.substr(start, end - start);
    return value.find("true") != std::string::npos;
}

std::string Settings::toJSONString(const Settings& settings) {
    std::ostringstream oss;

    oss << "{\n";
    oss << "  \"graphics-settings\": {\n";
    oss << "    \"resolution-x\": " << settings.graphics.resolutionX << ",\n";
    oss << "    \"resolution-y\": " << settings.graphics.resolutionY << ",\n";
    oss << "    \"fullscreen\": " << (settings.graphics.fullscreen ? "true" : "false") << "\n";
    oss << "  },\n";
    oss << "  \"audio-settings\": {\n";
    oss << "    \"music-volume\": " << settings.audio.musicVolume << ",\n";
    oss << "    \"sfx-volume\": " << settings.audio.sfxVolume << "\n";
    oss << "  },\n";
    oss << "  \"game-settings\": {\n";
    oss << "    \"nsfw-enabled\": " << (settings.game.nsfwEnabled ? "true" : "false") << ",\n";
    oss << "    \"win-points\": " << settings.game.winPoints << "\n";
    oss << "  }\n";
    oss << "}";

    return oss.str();
}

// Getter implementations
std::string Settings::getResolution() const {
    return std::to_string(graphics.resolutionX) + "x" + std::to_string(graphics.resolutionY);
}

bool Settings::getFullscreen() const {
    return graphics.fullscreen;
}

float Settings::getMusicVolume() const {
    return audio.musicVolume;
}

float Settings::getSFXVolume() const {
    return audio.sfxVolume;
}

bool Settings::getNSFWEnabled() const {
    return game.nsfwEnabled;
}

int Settings::getWinPoints() const {
    return game.winPoints;
}
