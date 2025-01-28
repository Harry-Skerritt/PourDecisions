#ifndef FORFEITPARSER_H
#define FORFEITPARSER_H

#include <string>
#include <vector>

#include <SFML/Graphics.hpp>

class ForfeitParser {
public:
	ForfeitParser();
	~ForfeitParser();

	struct ForfeitData {
		std::string contentName;
		int forfeitCount;
		sf::Color cardColour;
		std::vector<std::string> motifNames;
		std::vector<std::string> forfeitTitles;
		std::vector<std::string> forfeitCards;
		std::vector<std::string> forfeitTimer;
	};

	static ForfeitData readFromFile(const std::string& filePath);

private:
	//Helper funcs
	static sf::Color parseHexColour(const std::string& hexColour);
	static std::string extractValue(const std::string& json, const std::string& key);
	static std::vector<std::string> extractArray(const std::string& json, const std::string& key);
};


#endif // !FORFEITPARSER_H
