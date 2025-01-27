#ifndef CREDITS_H
#define CREDITS_H

#include <SFML/Graphics.hpp>
#include "../Utils/Widgets/Button.h"
#include "../Utils/GradientText.h"
#include <SFML/Window.hpp>
#include <cstdlib> // For system()
#include <iostream>

class Game;

class CreditsScreen {

public:
	CreditsScreen(sf::RenderWindow& window, sf::Font& font1);
	~CreditsScreen();

	void setGameInstance(Game* game);

	void init();

	void update(sf::Vector2f clickPos);

	void handleMouse(sf::Vector2f clickPos);

	void draw(sf::RenderWindow& window);


private:

	Game* m_game;

	sf::RenderWindow& window;
	sf::Font& righteousFont;

	GradientText creditText;

	Button backButton;
	Button viewMoreButton;

	sf::Text gameText;
	sf::Text ideaText;
	sf::Text devText;

	sf::Text audioText;
	sf::Text menuText;
	sf::Text otherText;
	sf::Text sfxText;

	sf::Text graphicsText;
	sf::Text motifText;
	sf::Text assetText;
	sf::Text addAssetText;

	sf::Text playText;
	sf::Text pt1;
	sf::Text pt2;
	sf::Text pt3;

	sf::Text questionText;
	sf::Text q1;
	sf::Text q2;
	sf::Text q3;

	sf::Color gradientColour1 = sf::Color(251, 0, 188, 255);
	sf::Color gradientColour2 = sf::Color(0, 238, 255, 255);
	sf::Color blueColour = sf::Color(0, 208, 255, 255);

	void openLink(const std::string& url);


};

#endif