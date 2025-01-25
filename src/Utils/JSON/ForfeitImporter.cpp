#include "ForfeitImporter.h"
#include <iostream>
#include <fstream>

ForfeitImporter::ForfeitImporter() {};
ForfeitImporter::~ForfeitImporter() {};

void ForfeitImporter::initialise(int expectedForfeits) {
	m_motifNames.reserve(expectedForfeits);
	m_forfeitTitles.reserve(expectedForfeits);
	m_forfeitCards.reserve(expectedForfeits);
	m_forfeitTimers.reserve(expectedForfeits);
	m_forfeitQuantity = 0;
}

std::vector<std::string> ForfeitImporter::getMotifNames() {
	return m_motifNames;
}

std::vector<std::string> ForfeitImporter::getForfeitTitles() {
	return m_forfeitTitles;
}

std::vector<std::string> ForfeitImporter::getForfeitCards() {
	return m_forfeitCards;
}

std::vector<int> ForfeitImporter::getForfeitTimers() {
	return m_forfeitTimers;
}

int ForfeitImporter::getForfeitQuantity() {
	return m_forfeitQuantity;
}

bool ForfeitImporter::setForfeitDir(std::string& fileLoc) {
	m_fileLocation = fileLoc;
	std::fstream file(fileLoc);
	if (file.is_open()) {
		//File is there
		return true;
		file.close();
	}
	else {
		throw std::runtime_error("Could not open forfeit file to check file: " + fileLoc);
		return false;
	}
}

bool ForfeitImporter::importForfeits() {
	try {
		std::cout << "Opening File: " << m_fileLocation << std::endl;

		m_forfeitData = ForfeitParser::readFromFile(m_fileLocation);

		//Debug
		std::cout << "Content Name: " << m_forfeitData.contentName << "\n";
		std::cout << "Forfeit Count: " << m_forfeitData.forfeitCount << "\n";
		std::cout << "Forfeit Colour: " << (int)m_forfeitData.cardColour.r << ", "
			<< (int)m_forfeitData.cardColour.g << ", " << (int)m_forfeitData.cardColour.b << ")\n";

		std::cout << "Forfeit Titles:\n";
		for (const auto& title : m_forfeitData.forfeitTitles) {
			std::cout << "- " << title << "\n";
		}

		std::cout << "Forfeit Cards:\n";
		for (const auto& card : m_forfeitData.forfeitCards) {
			std::cout << "- " << card << "\n";
		}

		std::cout << "Forfeit Motif Names:\n";
		for (const auto& motif : m_forfeitData.motifNames) {
			std::cout << "- " << motif << "\n";
		}

		std::cout << "Forfeit Timers:\n";
		for (const auto& timer : m_forfeitData.forfeitTimer) {
			std::cout << "- " << timer << "\n";
		}

		//Populate the arrays
		m_forfeitQuantity = m_forfeitData.forfeitCount;

		m_forfeitTitles.resize(m_forfeitQuantity);
		m_forfeitCards.resize(m_forfeitQuantity);
		m_motifNames.resize(m_forfeitQuantity);
		m_forfeitTimers.resize(m_forfeitQuantity);

		m_forfeitTitles = m_forfeitData.forfeitTitles;
		m_forfeitCards = m_forfeitData.forfeitCards;
		m_motifNames = m_forfeitData.motifNames;


		for (int i = 0; i < m_forfeitData.forfeitTimer.size(); i++) {
			m_forfeitTimers.at(i) = std::stoi(m_forfeitData.forfeitTimer.at(i));
		}

		return true;
	}
	catch (const std::exception& e) {
		std::cerr << "Error: " << e.what() << std::endl;
		return false;
	}
	

}