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

        // Debugging size prints
        std::cout << "Content Name: " << m_forfeitData.contentName << "\n";
        std::cout << "Forfeit Count: " << m_forfeitData.forfeitCount << "\n";
        std::cout << "Forfeit Titles Size: " << m_forfeitData.forfeitTitles.size() << "\n";
        std::cout << "Forfeit Cards Size: " << m_forfeitData.forfeitCards.size() << "\n";
        std::cout << "Forfeit Motif Names Size: " << m_forfeitData.motifNames.size() << "\n";
        std::cout << "Forfeit Timers Size: " << m_forfeitData.forfeitTimer.size() << "\n";

        // Check if sizes match the expected forfeit count
        if (m_forfeitData.forfeitTitles.size() != m_forfeitData.forfeitCount ||
            m_forfeitData.forfeitCards.size() != m_forfeitData.forfeitCount ||
            m_forfeitData.motifNames.size() != m_forfeitData.forfeitCount ||
            m_forfeitData.forfeitTimer.size() != m_forfeitData.forfeitCount) {
            std::cerr << "Error: Data size does not match forfeit count!" << std::endl;
            return false;
        }

        // Resize vectors based on forfeitCount
        m_forfeitTitles.resize(m_forfeitData.forfeitCount);
        m_forfeitCards.resize(m_forfeitData.forfeitCount);
        m_motifNames.resize(m_forfeitData.forfeitCount);
        m_forfeitTimers.resize(m_forfeitData.forfeitCount);

        m_forfeitQuantity = m_forfeitData.forfeitCount;

        // Manually copy data from m_forfeitData to the resized vectors
        for (size_t i = 0; i < m_forfeitData.forfeitTitles.size(); ++i) {
            m_forfeitTitles.at(i) = m_forfeitData.forfeitTitles.at(i);
        }

        for (size_t i = 0; i < m_forfeitData.forfeitCards.size(); ++i) {
            m_forfeitCards.at(i) = m_forfeitData.forfeitCards.at(i);
        }

        for (size_t i = 0; i < m_forfeitData.motifNames.size(); ++i) {
            m_motifNames.at(i) = m_forfeitData.motifNames.at(i);
        }

        for (size_t i = 0; i < m_forfeitData.forfeitTimer.size(); ++i) {
            try {
                m_forfeitTimers.at(i) = std::stoi(m_forfeitData.forfeitTimer.at(i));
            }
            catch (const std::invalid_argument& e) {
                std::cerr << "Invalid timer value at index " << i << std::endl;
                return false;
            }
        }

        std::cout << "JSON Parsing/Importing Finished" << std::endl;

        return true;
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return false;
    }
}