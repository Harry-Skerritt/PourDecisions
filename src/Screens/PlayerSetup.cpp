#include "PlayerSetup.h"
#include "../Game.h"
#include "../Utils/GradientBackground.h"
#include "../Managers/AudioManager.h"
#include <iostream>

PlayerSetup::PlayerSetup(sf::RenderWindow& window, sf::Font& font) : window(window), font(font) {};
PlayerSetup::~PlayerSetup() {};

void PlayerSetup::setGameInstance(Game* game) {
	m_game = game; //Sets the Game pointer
}

void PlayerSetup::initialise()
{
	//Title
	playerSetupTitle.setFont(font);
	playerSetupTitle.setString("PLAYER SETUP");
	playerSetupTitle.setCharacterSize(80);
	playerSetupTitle.setGradientColors(sf::Color(251, 0, 188, 255), sf::Color(0, 238, 255, 255));
	playerSetupTitle.setPosition(((window.getSize().x / 2) - (playerSetupTitle.getGlobalBounds().width / 2)), 60);


	//Text Entry
	playerNameEntry.setFont(font);
	playerNameEntry.setSize(400, 60);
	playerNameEntry.setBackgroundColour(sf::Color(66, 66, 66, 255));
	playerNameEntry.setPlaceholder("Enter Player Name");
	playerNameEntry.setPosition(((window.getSize().x / 2) - (playerNameEntry.getGlobalBounds().width / 2)), 150);
	playerNameEntry.setBorder(4.0f, sf::Color::Black);

	//Add Player Button
	addPlayerButton.setBackgroundImage(m_game->buttonCircleTexture);
	addPlayerButton.setBackgroundScale(0.6f, 0.6f);
	addPlayerButton.setText("+", font, 40);
	addPlayerButton.setTextColor(m_game->buttonNormalColour);
	addPlayerButton.setHoverColor(m_game->buttonHoverColour);
	addPlayerButton.setPosition(playerNameEntry.getPosition().x + playerNameEntry.getGlobalBounds().width + 20, 150);
}

void PlayerSetup::update(float dt, sf::Vector2f& windowClick) {
	addPlayerButton.handleHover(windowClick);
}

void PlayerSetup::handleMouse(sf::Event event, sf::Vector2f windowClick) {
	if (addPlayerButton.isClicked(windowClick)) {
		if (playerNameEntry.isEmpty()) {
			AudioManager::getInstance().playSoundEffect("wrongSF");
		}
		else {
			AudioManager::getInstance().playSoundEffect("addPlayerSF");
			//Other Code
		}
		std::cout << "Add Player Clicked" << std::endl;
		//Handle adding the player
		playerNameEntry.resetField(); //Reset for next name
	}
}

void PlayerSetup::handleTextEntry(sf::Event event) {
	playerNameEntry.handleInput(event);
}

void PlayerSetup::draw(sf::RenderWindow& window, ConfettiManager& confetti)
{
	GradientBackground::setBackgroundGradient(window);
	confetti.draw(window);
	window.draw(playerSetupTitle);
	playerNameEntry.draw(window);
	addPlayerButton.draw(window);
}
