#include "SettingsParser.h"


SettingsParser::SettingsParser() {};

SettingsParser::~SettingsParser() {};

void SettingsParser::loadInSettings(std::string fileLoc) {

	m_fileLoc = fileLoc;

	JsonParser parser(fileLoc);

	// Loading JSON file
	if (parser.loadJson(fileLoc)) {
		std::cout << "Settings loaded successfully!" << std::endl;
	}
	else {
		std::cerr << "Failed to load settings.json" << std::endl;
	}

	// Get values
	try {

		int winPoints = parser.get<int>("win-points");
		std::cout << "Win Points: " << winPoints << std::endl;

		bool fullscreen = parser.get<bool>("fullscreen");
		std::cout << "Fullscreen: " << (fullscreen ? "True" : "False") << std::endl;

		float musicVol = parser.get<float>("music-volume");
		std::cout << "Music Volume: " << musicVol << std::endl;
	}
	catch (const std::exception& e) {
		std::cerr << "Error: " << e.what() << std::endl;
	}
}

std::string SettingsParser::getResolution() {
	return resolution;
}

bool SettingsParser::getFullscreen() {
	return fullscreen;
}

float SettingsParser::getMusicVol() {
	return musicVol;
}

float SettingsParser::getSfxVol() {
	return sfxVol;
}

bool SettingsParser::getNSFW() {
	return nsfwEnabled;
}

int SettingsParser::getWinPoints() {
	return winPoints;
}


bool SettingsParser::splitAndConvertToInt(const std::string& str, char delimiter, int& before, int& after) {
	size_t pos = str.find(delimiter);
	if (pos != std::string::npos) {
		// Extract the part before and after the delimiter
		std::string beforeStr = str.substr(0, pos);
		std::string afterStr = str.substr(pos + 1);

		// Convert the parts to integers
		std::istringstream beforeStream(beforeStr);
		std::istringstream afterStream(afterStr);

		if (beforeStream >> before && afterStream >> after) {
			return true; // Successfully converted both parts to integers
		}
	}

	return false; // Delimiter not found or conversion failed
}


void SettingsParser::setResolution(std::string res) {

}

void SettingsParser::setFullscreen(bool state) {
	
}

void SettingsParser::setMusicVol(float vol) {
	
}

void SettingsParser::setSfxVol(float vol) {
	
}

void SettingsParser::setNSFW(bool state) {
	
}

void SettingsParser::setWinPoints(int points) {
}

