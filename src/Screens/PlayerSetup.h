#ifndef PLAYERSETUP_H
#define PLAYERSETUP_H
#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "../VisualAddons/Confetti.h"
#include "../Utils/GradientText.h"
#include "../Utils/Widgets/Button.h"
#include "../Utils/Widgets/InputField.h"
#include "../Utils/Widgets/TextGrid.h"

//Continue moving player setup into this

class Game;

class PlayerSetup {
public:
	PlayerSetup(sf::RenderWindow&, sf::Font& font);
	~PlayerSetup();

	void setGameInstance(Game* game);

	void initialise();

	void update(float dt, sf::Vector2f& windowClick);

	void handleMouse(sf::Event event, sf::Vector2f windowClick);

	void handleEnter(sf::Event event);

	void handleTextEntry(sf::Event event);

	void draw(sf::RenderWindow& window, ConfettiManager& confetti);

	void repopulatePlayers(std::vector<std::string> i_playerNames);

	void reset();

private:
	sf::RenderWindow& window;
	sf::Font& font;

	int maxPlayers;
	int currentPlayers;
	int allowedThreshold;
	bool inputAllowed;

	sf::Color allowedPlayerColour = sf::Color(76, 233, 16, 255);
	sf::Color disallowedPlayerColour = sf::Color(255, 1, 67, 255);
	sf::Color purpleColour = sf::Color(44, 3, 60, 255);
	sf::Color pinkBorder = sf::Color(164, 26, 162, 255);

	Game* m_game;

	GradientText playerSetupTitle;
	InputField playerNameEntry;
	Button addPlayerButton;
	Button backButton;
	Button nextButton;

	sf::Text playerCountLabel;
	sf::Text maxPlayerCount;
	sf::Text currentPlayerCount;

	TextGrid currentPlayerDisplay;

	void increasePlayerCount(int valueBy = 1);

};

#endif