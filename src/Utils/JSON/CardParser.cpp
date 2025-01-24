#include "CardParser.h"
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <algorithm>


CardParser::CardParser() {};
CardParser::~CardParser() {};

CardParser::CategoryData CardParser::readFromFile(const std::string& filePath) {
	//Open file
	std::ifstream file(filePath);
	if (!file.is_open()) {
		throw std::runtime_error("Could not open card file: " + filePath);
	}

	//Read the file into a string
	std::ostringstream oss;
	oss << file.rdbuf();
	std::string json = oss.str();

	//Parse data
	CategoryData catData;
	catData.contentName = extractValue(json, "content-name");
	catData.cardCount = std::stoi(extractValue(json, "card-count"));
	catData.cardColour = parseHexColour(extractValue(json, "card-color"));
	catData.cards = extractArray(json, "cards");

	return catData;
}


// Parse hex colour into sf::Color
sf::Color CardParser::parseHexColour(const std::string& hexColour) {
	if (hexColour.size() != 7 || hexColour[0] != '#') {
		//In incorrect format
		throw std::invalid_argument("Invalid hex colour format: " + hexColour);
	}

	unsigned int r, g, b;
	std::stringstream ss;

	ss << std::hex << hexColour.substr(1, 2); //Red
	ss >> r;
	ss.clear();

	ss << std::hex << hexColour.substr(3, 2); //Green
	ss >> g;
	ss.clear();

	ss << std::hex << hexColour.substr(5, 2); //Blue
	ss >> b;

	return sf::Color(r, g, b);
}

// Extracts the value at the key
std::string CardParser::extractValue(const std::string& json, const std::string& key) {
	std::string searchKey = "\"" + key + "\":";

	size_t keyPos = json.find(searchKey);
	if (keyPos == std::string::npos) {
		throw std::invalid_argument("Key not found: " + key);
	}

	size_t start = json.find_first_of("\"", keyPos + searchKey.length()) + 1;
	size_t end = json.find_first_of("\"", start);

	return json.substr(start, end - start);
}

// Extracts an array of strings at the key
std::vector<std::string> CardParser::extractArray(const std::string& json, const std::string& key) {
	std::string searchKey = "\"" + key + "\":";
	size_t keyPos = json.find(searchKey);
	if (keyPos == std::string::npos) {
		throw std::invalid_argument("Key not found: " + key);
	}

	size_t start = json.find("[", keyPos) + 1;
	size_t end = json.find("]", start);

	std::vector<std::string> values;
	size_t current = start;

	while (current < end) {
		size_t valueStart = json.find("\"", current) + 1;
		size_t valueEnd = json.find("\"", valueStart);

		if (valueStart == std::string::npos || valueEnd == std::string::npos) {
			break;
		}

		values.push_back(json.substr(valueStart, valueEnd - valueStart));
		current = valueEnd + 1;
	}

	return values;

}

