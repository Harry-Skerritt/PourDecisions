#ifndef FORFEITCARD_H
#define FORFEITCARD_H

#include <SFML/Graphics.hpp>
#include "../Utils/Widgets/SolidButton.h"
#include <string>

class MainGame;

class ForfeitCard {
public:
	ForfeitCard();
	~ForfeitCard();

	void setMainGameInstance(MainGame* game);

	void initialise(sf::Font& font1, sf::Font& font2, std::string title, std::string body, std::string imgLoc, float scaleX, sf::RenderWindow& window, bool group);

	void setPosition(float x, float y);

	void update(float dt, sf::Vector2f clickPos);

	void handleMouse(sf::Vector2f clickPos);

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
		sf::Text& cardHeaderText,
		sf::Text& cardTitle,
		sf::Text& cardMessage,
		sf::Sprite& cardMotif,
		SolidButton& doneButton,
		float deltaTime,
		float fadeSpeed,
		bool fadeIn // true for fade in, false for fade out
	);

	bool isCardVisible();

	sf::Color getColour() {
		return cardColour;
	}

private:

	MainGame* m_mainGame;

	bool groupCard;
	bool cardVisible;

	sf::Color cardColour = sf::Color(122, 122, 222, 255);
	sf::Color borderColour = sf::Color::Black;
	sf::Color cardBackColour = sf::Color::White;

	std::string headerText;
	std::string titleText;
	std::string messageText;

	sf::Font righteousFont;
	sf::Font ryeFont;

	sf::RectangleShape screenDarken;
	sf::RectangleShape cardBackground;
	sf::RectangleShape cardHeader;

	sf::Text cardHeaderText;
	sf::Text cardTitleText;
	sf::Text cardMessageText;

	sf::Texture motifTexture;
	sf::Sprite motifSprite;

	SolidButton doneButton;

	//Helper function
	void wrapText(sf::Text& text, float maxWidth);

	void adjustLayout(sf::Text& cardMessage, sf::RectangleShape& cardBackground, sf::Sprite& cardMotif, SolidButton& doneButton);

	void fitToWidth(sf::Text& text, const sf::RectangleShape& rectangle);

};


#endif