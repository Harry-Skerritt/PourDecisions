#include "CardImporter.h"
#include <filesystem> // C++17
#include <iostream>
#include <fstream>

CardImporter::CardImporter() {};

CardImporter::~CardImporter() {};

namespace fs = std::filesystem;

//Add support for a non-nsfw mode

void CardImporter::initialise(int expectedCategories, bool importCustom, int max_categories) {
	m_expectedCategories = expectedCategories;
	m_importCustom = importCustom;
	m_currentCardNo = 0;

	m_cardCategories.reserve(max_categories);
	m_cardColours.reserve(max_categories);
	m_cardQuantity.reserve(max_categories);
	m_cardQuestions.reserve(max_categories);
	m_motifLoc.reserve(max_categories);
}

int CardImporter::getNumberOfCards() {
	int totalCards = 0;
	for (int i = 0; i < m_cardQuantity.size(); i++) {
		totalCards += m_cardQuantity.at(i);
	}

	return totalCards;
}

std::vector<std::string> CardImporter::getCardCategories() {
	return m_cardCategories;
}

std::vector<sf::Color>  CardImporter::getCardColours() {
	return m_cardColours;
}

std::vector<int> CardImporter::getCardQuantity() {
	return m_cardQuantity;
}

std::vector<std::vector<std::string>> CardImporter::getCardQuestions() {
	return m_cardQuestions;
}

std::vector<std::string> CardImporter::getMotifLoc() {
	return m_motifLoc;
}

bool CardImporter::setCardDir(std::string& folderLoc) {
	m_cardLocation = folderLoc;

	//Get the amount of files
	int fileCount = 0;

	try {
		//Iterate over every direcotry entry
		for (const auto& entry : fs::directory_iterator(m_cardLocation)) {
			if (fs::is_regular_file(entry.status())) {
				++fileCount;
			}
		}
	}
	catch (const std::exception& e) {
		std::cerr << "Error accessing directory: " << e.what() << std::endl;
		return 0;
	}

	if ((fileCount - 1) != m_expectedCategories) {
		//There is not enough card files (-1 as forfeits isn't imported here)
		return 0;
	}
	else {
		if (m_importCustom) {
			//If importing the custom card data
			m_cardCategories.resize(m_expectedCategories + 1);
			m_cardColours.resize(m_expectedCategories + 1);
			m_cardQuantity.resize(m_expectedCategories + 1);
			m_cardQuestions.resize(m_expectedCategories + 1);
			m_motifLoc.resize(m_expectedCategories + 1);
		}
		else {
			//If not importing the custom card data
			m_cardCategories.resize(m_expectedCategories);
			m_cardColours.resize(m_expectedCategories);
			m_cardQuantity.resize(m_expectedCategories);
			m_cardQuestions.resize(m_expectedCategories);
			m_motifLoc.resize(m_expectedCategories);
		}
		return 1; //Expected amount of files = 7 or 8
	}

}

bool CardImporter::importCards() {
	try {
		//Go through every file in the directory
		for (const auto& entry : fs::directory_iterator(m_cardLocation)) {
			// Check if the entry is a file
			if (fs::is_regular_file(entry.status())) {
				// Get the file name
				std::string fileName = entry.path().filename().string();

				// Skip the forfeits file
				if (fileName != "forfeits.json") {
					std::cout << "Opening file: " << fileName << std::endl;

					// Parse the file
					m_cardCatData = CardParser::readFromFile(entry.path().string());

					//DEBUG
					std::cout << "Content Name: " << m_cardCatData.contentName << "\n";
					std::cout << "Card Count: " << m_cardCatData.cardCount << "\n";
					std::cout << "Card Color: (" << (int)m_cardCatData.cardColour.r << ", "
						<< (int)m_cardCatData.cardColour.g << ", " << (int)m_cardCatData.cardColour.b << ")\n";

					std::cout << "Cards:\n";
					for (const auto& card : m_cardCatData.cards) {
						std::cout << "- " << card << "\n";
					}

					std::cout << "Motif Loc: " << m_cardCatData.motifLoc << "\n";
					
					//Populate the arrays with the data
					std::string cardCategory = m_cardCatData.contentName;
					m_cardCategories.at(m_currentCardNo) = cardCategory;

					int cardCount = m_cardCatData.cardCount;
					m_cardQuantity.at(m_currentCardNo) = cardCount;

					sf::Color cardColour = m_cardCatData.cardColour;
					m_cardColours.at(m_currentCardNo) = cardColour;

					std::vector<std::string> cards = m_cardCatData.cards;
					m_cardQuestions.at(m_currentCardNo) = cards;

					std::string motif = m_cardCatData.motifLoc;
					m_motifLoc.at(m_currentCardNo) = motif;

					m_currentCardNo += 1; //Inc current card counter

				}
			}
		}
		return true;
	}
	catch (const std::exception& e) {
		std::cerr << "Error: " << e.what() << std::endl;
		return false;
	}
}