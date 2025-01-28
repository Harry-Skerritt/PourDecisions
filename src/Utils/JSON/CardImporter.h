#ifndef CARDIMPORTER_H
#define CARDIMPORTER_H

#include <string>
#include <vector>
#include "CardParser.h"

class CardImporter {
public:
	CardImporter();
	~CardImporter();

	bool setCardDir(std::string& folderLoc);

	std::vector<std::string> getCardCategories();
	std::vector<sf::Color>  getCardColours();
	std::vector<int> getCardQuantity();
	std::vector<std::vector<std::string>> getCardQuestions();
	std::vector<std::string> getMotifLoc();

	void initialise(int expectedCategories, bool importCustom, int max_categories);

	int getNumberOfCards();

	bool importCards(bool nsfwEnabled);

private:
	std::string m_cardLocation = "";
	int m_expectedCategories;
	bool m_importCustom;
	int m_categoriesLoaded;

	int m_currentCardNo;

	CardParser::CategoryData m_cardCatData;

	std::vector<std::string> m_cardCategories;
	std::vector<sf::Color> m_cardColours;
	std::vector<int> m_cardQuantity;
	std::vector<std::vector<std::string>> m_cardQuestions;
	std::vector<std::string> m_motifLoc;


	//From Game.h
	/*
		std::vector<std::string> cardCategories;			 //Stores the names of the categories
		std::vector<sf::Color> cardColours;					 //Stores the colours of each category
		std::vector<int> cardQuantity;						 //Stores the amount of cards in each category
		std::vector<std::vector<std::string>> cardQuestions; //Stores the questions for each category
		std::vector<std::vector<int>> usedCards;			 //Stores the cards which have been played
		std::vector<std::string> motifLoc;					 //Stores the file location of the motif for each card 
	*/


};


#endif // !CARDIMPORTER_H
