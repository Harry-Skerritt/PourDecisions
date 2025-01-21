#include "PlayerSetup.h"
#include "../Game.h"
#include "../Utils/GradientBackground.h"
#include "../Managers/AudioManager.h"
#include "../Utils/CustomMessageBox.h"
#include <iostream>
#include <string>

PlayerSetup::PlayerSetup(sf::RenderWindow& window, sf::Font& font) : window(window), font(font) {};
PlayerSetup::~PlayerSetup() {};

// Links to game
void PlayerSetup::setGameInstance(Game* game) {
	m_game = game; //Sets the Game pointer
}

// Initialises everything
void PlayerSetup::initialise()
{
	//Settings vars
	maxPlayers = m_game->getMaxPlayers();			 //Should be 8
	currentPlayers = m_game->getCurrentPlayers();	 //Should be 0
	allowedThreshold = m_game->getPlayerThreshold(); //Should be 3
	inputAllowed = true;

	//Title
	playerSetupTitle.setFont(font);
	playerSetupTitle.setString("PLAYER SETUP");
	playerSetupTitle.setCharacterSize(80);
	playerSetupTitle.setGradientColors(sf::Color(251, 0, 188, 255), sf::Color(0, 238, 255, 255));
	playerSetupTitle.setPosition(((window.getSize().x / 2) - (playerSetupTitle.getGlobalBounds().width / 2)), 60);


	//Text Entry
	playerNameEntry.setFont(font);
	playerNameEntry.setSize(400, 60);
	playerNameEntry.setBackgroundColour(blueColour);
	playerNameEntry.setPlaceholder("Enter Player Name");
	playerNameEntry.setPosition(((window.getSize().x / 2) - (playerNameEntry.getGlobalBounds().width / 2)), 150);
	playerNameEntry.setBorder(4.0f, pinkBorder);

	//Add Player Button
	addPlayerButton.setBackgroundImage(m_game->buttonCircleTexture);
	addPlayerButton.setBackgroundScale(0.6f, 0.6f);
	addPlayerButton.setText("+", font, 40);
	addPlayerButton.setTextColor(m_game->buttonNormalColour);
	addPlayerButton.setHoverColor(m_game->buttonHoverColour);
	addPlayerButton.setPosition(playerNameEntry.getPosition().x + playerNameEntry.getGlobalBounds().width + 20, 150);

	//Back Button
	backButton.setBackgroundImage(m_game->buttonRectTexture);
	backButton.setBackgroundScale(0.5f, 0.5f);
	backButton.setText("< Back", font, 40);
	backButton.setTextColor(m_game->buttonNormalColour);
	backButton.setHoverColor(m_game->buttonHoverColour);
	backButton.setPosition(40, (window.getSize().y - backButton.getGlobalBounds().height) - 40);


	//Next Button
	nextButton.setBackgroundImage(m_game->buttonRectTexture);
	nextButton.setBackgroundScale(0.5f, 0.5f);
	nextButton.setText("Next >", font, 40);
	nextButton.setTextColor(m_game->buttonNormalColour);
	nextButton.setHoverColor(m_game->buttonHoverColour);
	nextButton.setPosition((window.getSize().x - nextButton.getGlobalBounds().width) - 40, (window.getSize().y - nextButton.getGlobalBounds().height) - 40);

	//Player Count
	playerCountLabel.setFont(font);
	playerCountLabel.setString("Player Count:");
	playerCountLabel.setCharacterSize(30);
	playerCountLabel.setFillColor(sf::Color::White);
	playerCountLabel.setPosition((window.getSize().x - playerCountLabel.getGlobalBounds().width) - 50, (window.getSize().y / 2) - (playerCountLabel.getGlobalBounds().height / 2));

	maxPlayerCount.setFont(font);
	std::string maxPlayerString = "/" + std::to_string(maxPlayers);
	maxPlayerCount.setString(maxPlayerString);
	maxPlayerCount.setCharacterSize(50);
	if (currentPlayers < allowedThreshold) {
		maxPlayerCount.setFillColor(disallowedPlayerColour); 
	}
	else {
		maxPlayerCount.setFillColor(allowedPlayerColour);
	}
	maxPlayerCount.setPosition((playerCountLabel.getPosition().x + playerCountLabel.getGlobalBounds().width) - maxPlayerCount.getGlobalBounds().width*2, playerCountLabel.getPosition().y + 30);
	
	currentPlayerCount.setFont(font);
	std::string currentPlayerString = std::to_string(currentPlayers);
	currentPlayerCount.setString(currentPlayerString);
	currentPlayerCount.setCharacterSize(50);
	if (currentPlayers < allowedThreshold) {
		currentPlayerCount.setFillColor(disallowedPlayerColour);
	}
	else {
		currentPlayerCount.setFillColor(allowedPlayerColour);
	}
	currentPlayerCount.setPosition(maxPlayerCount.getPosition().x - maxPlayerCount.getGlobalBounds().width + 20, playerCountLabel.getPosition().y + 30);

	//Player Display
	currentPlayerDisplay.setSize(400, 400);
	currentPlayerDisplay.setPosition((window.getSize().x / 2 - currentPlayerDisplay.getGlobalBounds().width / 2), 
		(playerNameEntry.getPosition().y + playerNameEntry.getGlobalBounds().height) + 40);
	currentPlayerDisplay.setBackgroundColor(blueColour);
	currentPlayerDisplay.setTextColor(sf::Color::White);
	currentPlayerDisplay.setTextHoverColor(disallowedPlayerColour);
	currentPlayerDisplay.initialize(8, font, 40, true);
	currentPlayerDisplay.setHeader("Current Player");
	currentPlayerDisplay.setBorder(4.f, pinkBorder);
	currentPlayerDisplay.setClickCallback([this]() {
		increasePlayerCount(-1);
		AudioManager::getInstance().playSoundEffect("addPlayerSF");
	});
}

// Increases the player count
void PlayerSetup::increasePlayerCount(int valueBy) {	
	currentPlayers += valueBy; //Inc by 1
	currentPlayerCount.setString(std::to_string(currentPlayers));
	if (currentPlayers < allowedThreshold) {
		maxPlayerCount.setFillColor(disallowedPlayerColour);
		currentPlayerCount.setFillColor(disallowedPlayerColour);
	}
	else {
		maxPlayerCount.setFillColor(allowedPlayerColour);
		currentPlayerCount.setFillColor(allowedPlayerColour);
	}
	if (currentPlayers == maxPlayers) {
		//Now at max players
		currentPlayers = maxPlayers;
		inputAllowed = false; //Stops the typing for extra names
	}
	else {
		//Not at max Players
		inputAllowed = true;
	}
}


// Update Loop
void PlayerSetup::update(float dt, sf::Vector2f& windowClick) {
	addPlayerButton.handleHover(windowClick);
	backButton.handleHover(windowClick);
	nextButton.handleHover(windowClick);
	currentPlayerDisplay.handleHover(windowClick);
}

// Handles mouse
void PlayerSetup::handleMouse(sf::Event event, sf::Vector2f windowClick) {
	currentPlayerDisplay.handleClick(windowClick); //Handle current player click

	//Handle Add Player Button
	if (addPlayerButton.isClicked(windowClick)) {
		if (playerNameEntry.isEmpty() || currentPlayers == maxPlayers) {
			//Nothing in the field, or max number of players reached
			AudioManager::getInstance().playSoundEffect("wrongSF");
		}
		else {
			AudioManager::getInstance().playSoundEffect("addPlayerSF");
			increasePlayerCount();
			std::string currentPlayerName = playerNameEntry.getCurrentValue(); 
			currentPlayerDisplay.setText(currentPlayers - 1, currentPlayerName); // Add the name to the display
			//Other Code
		}
		std::cout << "Add Player Clicked" << std::endl;
		//Handle adding the player
		playerNameEntry.resetField(); //Reset for next name
	}

	//Handle Back Button
	if (backButton.isClicked(windowClick)) {
		AudioManager::getInstance().playSoundEffect("buttonClick");
		//Reset Screen
		currentPlayerDisplay.clearTextFields();
		currentPlayers = 0;
		inputAllowed = true;
		currentPlayerCount.setString("0");
		currentPlayerCount.setFillColor(disallowedPlayerColour);
		maxPlayerCount.setFillColor(disallowedPlayerColour);
		//Back to menu
		m_game->backToMainMenu(2);
	}

	//Handle Next Button
	if (nextButton.isClicked(windowClick)) {
		if (currentPlayers >= allowedThreshold) {
			//At least the allowed number of players
			AudioManager::getInstance().playSoundEffect("buttonClick");
			//Put the players names into an array in the order they were clicked
			m_game->setCurrentPlayers(currentPlayers); //Set the amount of players
			//Change screen
		}
		else {
			//Not the allowed number of players
			AudioManager::getInstance().playSoundEffect("wrongSF");

			//Create and show a OS-specific message box
			std::string warningMsg = "You need at least " + std::to_string(allowedThreshold) + " players!";
			CustomMessageBox playerWarning("Pour Decisions", warningMsg, 1);
			MessageBoxButton result = playerWarning.showMessageBox();
		}
	}
}

// Handles text entry
void PlayerSetup::handleTextEntry(sf::Event event) {
	playerNameEntry.handleInput(event, inputAllowed);
}

// Draws to the window
void PlayerSetup::draw(sf::RenderWindow& window, ConfettiManager& confetti)
{
	GradientBackground::setBackgroundGradient(window);
	confetti.draw(window);
	window.draw(playerSetupTitle);

	//Player Entry
	playerNameEntry.draw(window);
	addPlayerButton.draw(window);
	backButton.draw(window);
	nextButton.draw(window);
	
	//Player Count
	window.draw(playerCountLabel);
	window.draw(maxPlayerCount);
	window.draw(currentPlayerCount);

	//Player Display
	window.draw(currentPlayerDisplay);

}
