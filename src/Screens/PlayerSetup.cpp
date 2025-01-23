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
	playerNameEntry.setSize(window.getSize().x * 0.37f, window.getSize().y * 0.08f);
	playerNameEntry.setCharacterSize(window.getSize().y * 0.041f);
	playerNameEntry.setBackgroundColour(purpleColour);
	playerNameEntry.setPlaceholder("Enter Player Name");
	playerNameEntry.setPosition(((window.getSize().x / 2) - (playerNameEntry.getGlobalBounds().width / 2)), 150);
	//playerNameEntry.setBorder(4.0f, pinkBorder);

	//Add Player Button
	addPlayerButton.setBackgroundImage(m_game->buttonCircleTexture);
	addPlayerButton.setBackgroundScale(m_game->scaleX * 0.4f, m_game->scaleX * 0.4f);
	addPlayerButton.setText("+", font, window.getSize().y * 0.055f);
	addPlayerButton.setTextColor(m_game->buttonNormalColour);
	addPlayerButton.setHoverColor(m_game->buttonHoverColour);
	addPlayerButton.setOrigin(addPlayerButton.getGlobalBounds().width / 2, addPlayerButton.getGlobalBounds().height / 2);
	addPlayerButton.setPosition(playerNameEntry.getPosition().x + playerNameEntry.getGlobalBounds().width + 20, playerNameEntry.getPosition().y);

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
	playerCountLabel.setCharacterSize(window.getSize().x * 0.027f);
	playerCountLabel.setFillColor(sf::Color::White);
	playerCountLabel.setPosition((window.getSize().x - playerCountLabel.getGlobalBounds().width) - 50, (window.getSize().y / 2) - (playerCountLabel.getGlobalBounds().height / 2));

	maxPlayerCount.setFont(font);
	std::string maxPlayerString = "/" + std::to_string(maxPlayers);
	maxPlayerCount.setString(maxPlayerString);
	maxPlayerCount.setCharacterSize(window.getSize().x * 0.047f);
	if (currentPlayers < allowedThreshold) {
		maxPlayerCount.setFillColor(disallowedPlayerColour); 
	}
	else {
		maxPlayerCount.setFillColor(allowedPlayerColour);
	}
	maxPlayerCount.setPosition((playerCountLabel.getPosition().x + playerCountLabel.getGlobalBounds().width) - maxPlayerCount.getGlobalBounds().width*2, playerCountLabel.getPosition().y + window.getSize().y * 0.041f);
	
	currentPlayerCount.setFont(font);
	std::string currentPlayerString = std::to_string(currentPlayers);
	currentPlayerCount.setString(currentPlayerString);
	currentPlayerCount.setCharacterSize(window.getSize().x * 0.047f);
	if (currentPlayers < allowedThreshold) {
		currentPlayerCount.setFillColor(disallowedPlayerColour);
	}
	else {
		currentPlayerCount.setFillColor(allowedPlayerColour);
	}
	currentPlayerCount.setPosition(maxPlayerCount.getPosition().x - maxPlayerCount.getGlobalBounds().width + window.getSize().x * 0.018f, playerCountLabel.getPosition().y + window.getSize().y * 0.041f);

	//Player Display
	currentPlayerDisplay.setSize(window.getSize().x * 0.37f, window.getSize().x * 0.37f);
	currentPlayerDisplay.setPosition((window.getSize().x / 2 - currentPlayerDisplay.getGlobalBounds().width / 2), 
		(playerNameEntry.getPosition().y + playerNameEntry.getGlobalBounds().height) + 40);
	currentPlayerDisplay.setBackgroundColor(purpleColour);
	currentPlayerDisplay.setTextColor(sf::Color::White);
	currentPlayerDisplay.setTextHoverColor(disallowedPlayerColour);
	currentPlayerDisplay.initialize(8, font, window.getSize().x * 0.037f, true);
	currentPlayerDisplay.setHeader("Current Player");
	//currentPlayerDisplay.setBorder(4.f, pinkBorder);
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

void PlayerSetup::reset() {
	currentPlayerDisplay.clearTextFields();
	currentPlayers = 0;
	inputAllowed = true;
	currentPlayerCount.setString("0");
	currentPlayerCount.setFillColor(disallowedPlayerColour);
	maxPlayerCount.setFillColor(disallowedPlayerColour);
}

// Handles mouse
void PlayerSetup::handleMouse(sf::Event event, sf::Vector2f windowClick) {
	currentPlayerDisplay.handleClick(windowClick); //Handle current player click

	//Handle Back Button
	if (backButton.isClicked(windowClick)) {
		AudioManager::getInstance().playSoundEffect("buttonClick");
		//Reset Screen
		reset();
		//Back to menu
		m_game->backToMainMenu(2);
	}

	//Handle Next Button
	if (nextButton.isClicked(windowClick)) {
		if (currentPlayers >= allowedThreshold) {
			//At least the allowed number of players
			AudioManager::getInstance().playSoundEffect("buttonClick");
			//Put the players names into an array in the order they were clicked
			for (int i = 0; i < (currentPlayers); i++) {
				//Loop through every player and add their name to the array
				m_game->addPlayer(currentPlayerDisplay.getText(i)); 
			}

			if (m_game->getSizeOfPlayerArray() == currentPlayers) {
				std::cout << "All players added successfully" << std::endl; // DEBUG
				std::cout << "Players in array: " << std::to_string(m_game->getSizeOfPlayerArray()) << std::endl; // DEBUG
			}
			else { 
				std::cout << "Error in adding players" << std::endl; // DEBUG
				std::cout << "Players in array: " << std::to_string(m_game->getSizeOfPlayerArray()) << std::endl; // DEBUG
				std::cout << "Players added: " << currentPlayers << std::endl; // DEBUG
			}

			m_game->setCurrentPlayers(currentPlayers); //Set the amount of players
			//Do more with passing player data to the game
			m_game->transitionToMainGame();
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

void PlayerSetup::handleEnter(sf::Event event) {
	//Handle Add Player function
	if (playerNameEntry.isEmpty() || currentPlayers == maxPlayers) {
		//Nothing in the field, or max number of players reached
		AudioManager::getInstance().playSoundEffect("wrongSF");
	}
	else {
		AudioManager::getInstance().playSoundEffect("addPlayerSF");
		increasePlayerCount();
		std::string currentPlayerName = playerNameEntry.getCurrentValue();
		currentPlayerDisplay.setText(currentPlayers - 1, currentPlayerName); // Add the name to the display
	}
	std::cout << "Add Player: " << playerNameEntry.getCurrentValue() << std::endl;
	playerNameEntry.resetField(); //Reset for next name
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
	//addPlayerButton.draw(window);
	backButton.draw(window);
	nextButton.draw(window);
	
	//Player Count
	window.draw(playerCountLabel);
	window.draw(maxPlayerCount);
	window.draw(currentPlayerCount);

	//Player Display
	window.draw(currentPlayerDisplay);

}
