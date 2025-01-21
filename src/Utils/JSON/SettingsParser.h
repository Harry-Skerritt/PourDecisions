#ifndef SETTINGSPARSER_H
#define SETTINGSPARSER_H

#include <nlohmann/json.hpp>
#include "JsonParser.h"
#include <fstream>
#include <string>
#include <iostream>

class SettingsParser {
public:

	SettingsParser();
	~SettingsParser();


	void loadInSettings(std::string settingsLoc);

	//void saveSettings();

	//Getters
	std::string getResolution();
	bool getFullscreen();

	float getMusicVol();
	float getSfxVol();

	bool getNSFW();
	int getWinPoints();

	//Setters
	void setResolution(std::string res);
	void setFullscreen(bool state);
	
	void setMusicVol(float vol);
	void setSfxVol(float vol);

	void setNSFW(bool state);
	void setWinPoints(int points);

	//Helper function
	bool splitAndConvertToInt(const std::string& str, char delimiter, int& before, int& after);

private:
	std::string m_fileLoc;

	std::string resolution;
	bool fullscreen;

	float musicVol;
	float sfxVol;

	bool nsfwEnabled;
	int winPoints;

	
};


#endif