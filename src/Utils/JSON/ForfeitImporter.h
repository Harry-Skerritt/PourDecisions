#ifndef FORFEITIMPORTER_H
#define FORFEITIMPORTER_H

#include <string>
#include <vector>
#include "ForfeitParser.h"

class ForfeitImporter {
public:
	ForfeitImporter();
	~ForfeitImporter();

	bool setForfeitDir(std::string& fileLoc);

	std::vector<std::string> getMotifNames();
	std::vector<std::string> getForfeitTitles();
	std::vector<std::string> getForfeitCards();
	std::vector<int> getForfeitTimers();
	int getForfeitQuantity();

	void initialise(int expectedForfeits);

	bool importForfeits();

private:
	std::string m_fileLocation = "";

	ForfeitParser::ForfeitData m_forfeitData;

	std::vector<std::string> m_motifNames;
	std::vector<std::string> m_forfeitTitles;
	std::vector<std::string> m_forfeitCards;
	std::vector<int> m_forfeitTimers;
	int m_forfeitQuantity;

};

#endif // !FORFEITIMPORTER_H
