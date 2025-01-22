#ifndef CARD_H
#define CARD_H

#include <SFML/Graphics.hpp>
#include "../Utils/Widgets/SolidButton.h"
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <cmath>

class Card {
public:
	Card();
	~Card();

	void initialise(sf::Color& colour, sf::Font& mainFont, sf::Font& secondaryFont, std::string title, std::string body, std::string imgLoc, float scaleX, sf::RenderWindow& window);

	void setPosition(float x, float y);

	void update(float dt, sf::Vector2f clickPos);


	sf::FloatRect getGlobalBounds() const;
	sf::FloatRect getLocalBounds() const;
	sf::Vector2f getPosition() const;


	void showCard(sf::RenderWindow& window, float dt);

	void hideCard(sf::RenderWindow& window, float dt);

	void drawFadeComponents(
		sf::RenderWindow& window,
		sf::RectangleShape& screenDarken,
		sf::RectangleShape& cardBackground,
		sf::RectangleShape& cardHeader,
		sf::Text& cardTitle,
		sf::Text& cardMessage,
		sf::Sprite& cardMotif,
		SolidButton& forfeitButton,
		SolidButton& passButton,
		float deltaTime,
		float fadeSpeed,
		bool fadeIn // true for fade in, false for fade out
	);

private:
	sf::RectangleShape cardBackground;
	sf::RectangleShape cardHeader;
	sf::RectangleShape screenDarken;

	sf::Font cardHeaderFont;
	sf::Font cardBodyFont;

	std::string cardHeaderText;
	std::string cardBodyText;

	sf::Text cardTitle;
	sf::Color cardColour;
	sf::Text cardMessage;
	sf::Texture cardMotifTex;
	sf::Sprite cardMotif;

	SolidButton forfeitButton;
	SolidButton passButton;

	sf::Color borderColour = sf::Color::Black;
	sf::Color cardBackColour = sf::Color::White;

	//Helper function
	void wrapText(sf::Text& text, float maxWidth);
};

#endif