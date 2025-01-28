#include "ForfeitParser.h"
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <algorithm>
#include <iostream>

ForfeitParser::ForfeitParser() {};
ForfeitParser::~ForfeitParser() {};

ForfeitParser::ForfeitData ForfeitParser::readFromFile(const std::string& filePath) {
	//Open File
	std::ifstream file(filePath);
	if (!file.is_open()) {
		throw std::runtime_error("Could not open forfeit file: " + filePath);
	}

	//Read into string
	std::ostringstream oss;
	oss << file.rdbuf();
	std::string json = oss.str();

	//Parse
	ForfeitData data;
	data.contentName = extractValue(json, "content-name");
	data.forfeitCount = std::stoi(extractValue(json, "card-count"));
	data.cardColour = parseHexColour(extractValue(json, "card-color"));
	data.motifNames = extractArray(json, "motifs");
	data.forfeitTitles = extractArray(json, "titles");
	data.forfeitCards = extractArray(json, "cards");
	data.forfeitTimer = extractArray(json, "timers");

	return data;
}

//Parse hex colour into sf::Color
sf::Color ForfeitParser::parseHexColour(const std::string& hexColour) {
	if (hexColour.size() != 7 || hexColour[0] != '#') {
		//Incorrect format
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

//Extracts value at the key
std::string ForfeitParser::extractValue(const std::string& json, const std::string& key) {
	std::string searchKey = "\"" + key + "\":";

	size_t keyPos = json.find(searchKey);
	if (keyPos == std::string::npos) {
		throw std::invalid_argument("Key not found: " + key);
	}

	size_t start = json.find_first_of("\"", keyPos + searchKey.length()) + 1;
	size_t end = json.find_first_of("\"", start);

	return json.substr(start, end - start);
}

// Extracts an array of string at the key
std::vector<std::string> ForfeitParser::extractArray(const std::string& json, const std::string& key) {
	std::string searchKey = "\"" + key + "\":";
	size_t keyPos = json.find(searchKey);
	if (keyPos == std::string::npos) {
		throw std::invalid_argument("Key not found: " + key);
	}

	size_t start = json.find("[", keyPos);
	size_t end = json.find("]", start);
	if (start == std::string::npos || end == std::string::npos) {
		throw std::invalid_argument("Invalid array format for key: " + key);
	}

	std::vector<std::string> values;
	size_t current = start + 1; // Skip the opening bracket

	while (current < end) {
		// Skip over any whitespace or commas
		current = json.find_first_not_of(" ,", current);
		if (current >= end) break;

		size_t valueStart = json.find("\"", current);
		if (valueStart == std::string::npos || valueStart >= end) break;
		valueStart++; // Skip the opening quote

		size_t valueEnd = json.find("\"", valueStart);
		if (valueEnd == std::string::npos || valueEnd > end) break;

		values.push_back(json.substr(valueStart, valueEnd - valueStart));
		current = valueEnd + 1; // Move past the closing quote

		// Skip over any commas or spaces after the value
		current = json.find_first_not_of(" ,", current);
	}

	// Validate there's no unexpected data
	size_t leftover = json.find_first_not_of(" ,]", current);
	if (leftover != std::string::npos && leftover < end) {
		std::cerr << "Warning: Extra data found in the array after processing: "
			<< json.substr(leftover, end - leftover) << std::endl;
	}

	return values;
}