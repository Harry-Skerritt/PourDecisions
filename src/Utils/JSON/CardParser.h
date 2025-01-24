#ifndef CARDPARSER_H
#define CARDPARSER_H

#include <string>
#include <vector>
#include <SFML/Graphics.hpp>

class CardParser {
public:
	CardParser();
	~CardParser();

	struct CategoryData {
		std::string contentName;
		int cardCount;
		sf::Color cardColour;
		std::vector<std::string> cards;
	};

	static CategoryData readFromFile(const std::string& filePath);

private:
	//Helper funcs
	static sf::Color parseHexColour(const std::string& hexColour);
	static std::string extractValue(const std::string& json, const std::string& key);
	static std::vector<std::string> extractArray(const std::string& json, const std::string& key);
};

#endif // !CARDPARSER_H
