#include "MainGame.h"
#include "../Game.h"
#include "../Utils/GradientBackground.h"
#include "../Managers/AudioManager.h"
#include "../Utils/CustomMessageBox.h"
#include <stdlib.h>
#include <thread>
#include <chrono>

MainGame::MainGame(sf::RenderWindow& window, sf::Font& font1, sf::Font& font2, sf::Font& font3) : 
	window(window), righteousFont(font1), ryeFont(font2), lcdFont(font3), 
	pauseMenu(window, font1),
	gameOver(window, font1, font2),
	forfeitScreen(window, font1, font2, font3) {};
MainGame::~MainGame() {};

void MainGame::setGameInstance(Game* game) {
	m_game = game;
}

void MainGame::init() {

	std::cout << "In main game init" << std::endl; //DEBUG

	//Vars Set
	currentGo = 0;
	turnsPlayed = 0;
	lastTurnNo = turnsPlayed;
	playersPopulated = false;
	menu_visible = false;
	cardShown = false;
	forfeitCardShown = false;
	game_over = false;
	forfeitScreenShown = false;

	std::cout << "Passed var setting" << std::endl; //DEBUG

	cardDisplay.setMainGameInstance(this);
	forfeitCardDisplay.setMainGameInstance(this);

	std::cout << "Passed card displays instance setters" << std::endl; //DEBUG


	std::cout << "Checking m_game" << std::endl; //DEBUG
	if (!m_game) {
		std::cerr << "Error: m_game is nullptr!" << std::endl;
		return;
	}
	else {
		std::cout << "m_game is fine" << std::endl; //DEBUG
	}

	//Forfeit Screen
	forfeitScreen.setGameInstance(m_game);
	forfeitScreen.setMainGameInstance(this);
	forfeitScreen.setVisible(forfeitScreenShown);

	std::cout << "Passed forfeit screen instance setters" << std::endl; //DEBUG

	//Pause menu
	pauseMenu.setGameInstance(m_game);
	pauseMenu.init();
	pauseMenu.showMenu(false);

	std::cout << "Passed pause menu instance setters" << std::endl; //DEBUG

	//Game Over
	gameOver.setGameInstance(m_game);

	std::cout << "Passed game over instance setters" << std::endl; //DEBUG

	//Player Board
	playerBoard.setSize(sf::Vector2f(window.getSize().x * 0.23f, window.getSize().y * 0.9));
	playerBoard.setFillColor(sf::Color(44, 3, 60, 255));
	playerBoard.setPosition(window.getSize().x - playerBoard.getSize().x, window.getSize().y / 2 - playerBoard.getSize().y / 2);
	playerBoard.setOutlineThickness(8.0f);
	playerBoard.setOutlineColor(sf::Color(250, 0, 188, 255));

	std::cout << "Passed player board" << std::endl; //DEBUG

	//drawGradientBorder(window, playerBoard.getGlobalBounds(), 8.0f, sf::Color(252, 0, 189, 255), sf::Color(43, 3, 62, 255));

	playerBoardTitle.setFont(ryeFont);
	playerBoardTitle.setString("Players");
	playerBoardTitle.setCharacterSize(window.getSize().x * 0.04f);
	playerBoardTitle.setOrigin(playerBoardTitle.getGlobalBounds().width / 2, playerBoardTitle.getGlobalBounds().height / 2);
	playerBoardTitle.setPosition(playerBoard.getPosition().x + playerBoard.getGlobalBounds().width / 2, playerBoard.getPosition().y + playerBoardTitle.getGlobalBounds().height / 2);

	std::cout << "Passed player board title" << std::endl; //DEBUG

	playerBoardDivider.setSize(sf::Vector2f(playerBoard.getSize().x * 0.75f, playerBoard.getSize().y * 0.004f));
	playerBoardDivider.setFillColor(sf::Color::White);
	playerBoardDivider.setOrigin(playerBoardDivider.getSize().x / 2, playerBoardDivider.getSize().y / 2);
	playerBoardDivider.setPosition(playerBoard.getPosition().x + playerBoard.getGlobalBounds().width / 2, playerBoardTitle.getPosition().y + playerBoardTitle.getGlobalBounds().height);

	std::cout << "Passed player board divider" << std::endl; //DEBUG

	playerDisplay.reserve(m_game->getMaxPlayers());
	playerNames.reserve(m_game->getMaxPlayers());

	std::cout << "Passed player detail reservation" << std::endl; //DEBUG

	//Spin Button
	spinButton.setBackgroundImage(m_game->buttonRectTexture);
	spinButton.setBackgroundScale(m_game->scaleX * 0.4f, m_game->scaleX * 0.4f);
	spinButton.setText("SPIN!", righteousFont, window.getSize().y * 0.055f);
	spinButton.setTextColor(m_game->buttonNormalColour);
	spinButton.setHoverColor(m_game->buttonHoverColour);
	float buttonX = (playerBoard.getPosition().x - spinButton.getGlobalBounds().width - (window.getSize().x * 0.026f));
	float buttonY = (playerBoard.getPosition().y + playerBoard.getGlobalBounds().height) - spinButton.getGlobalBounds().height - (window.getSize().y * 0.01f);
	spinButton.setPosition(buttonX, buttonY);

	std::cout << "Passed spin setup" << std::endl; //DEBUG

	//Point notifer
	pointNotifier.init(righteousFont, 2.0f); //1.5 seconds
	pointNotiferPos = sf::Vector2f(playerBoard.getPosition().x - (window.getSize().x * 0.15f), window.getSize().y * 0.25f);

	std::cout << "Passed point notifier" << std::endl; //DEBUG

	//Spin Wheel
	if (m_game->nsfwEnabled) {
		//NSFW Enabled load the nsfw wheel
		if (!spinWheelTexture.loadFromFile("../Data/Assets/Wheels/nsfwCategorySpinwheel.png")) {
			std::cout << "NSFW Wheel failed to load" << std::endl;
		}
	}
	else {
		//Load the sfw wheel
		if (!spinWheelTexture.loadFromFile("../Data/Assets/Wheels/sfwCategorySpinwheel.png")) {
			std::cout << "SFW Wheel failed to load" << std::endl;
		}
	}

	if (!spinWheelClickerTexture.loadFromFile("../Data/Assets/Wheels/spinwheelPointer.png")) {
		std::cout << "Spinwheel Clicker failed to load" << std::endl;
	}

	std::cout << "Passed wheel texture importing" << std::endl; //DEBUG

	spinWheelSprite.setTexture(spinWheelTexture);
	spinWheelSprite.setScale(m_game->scaleX * 0.55f, m_game->scaleX * 0.55f);
	spinWheelSprite.setOrigin(spinWheelSprite.getLocalBounds().width / 2, spinWheelSprite.getLocalBounds().height / 2);
	spinWheelSprite.setPosition(window.getSize().x * 0.28f, window.getSize().y / 2);

	std::cout << "Passed spin wheel sprite setup" << std::endl; //DEBUG

	spinner.setSprite(spinWheelSprite);

	spinner.setOnSpinCompleteCallback([this]() {
		std::cout << "CALLBACK!!!" << std::endl;
		std::cout << "Spin Complete!" << std::endl;
		cardShown = true;
		});

	std::cout << "Passed spinner setup" << std::endl; //DEBUG
	
	spinwheelClickerSprite.setTexture(spinWheelClickerTexture);
	spinwheelClickerSprite.setScale(m_game->scaleX * 0.55f, m_game->scaleX * 0.55f);
	spinwheelClickerSprite.setOrigin(spinwheelClickerSprite.getLocalBounds().left, spinwheelClickerSprite.getLocalBounds().height / 2);
	spinwheelClickerSprite.setPosition(0 - spinwheelClickerSprite.getGlobalBounds().width / 2, window.getSize().y / 2);
	
	std::cout << "Passed clicker setup" << std::endl; //DEBUG

	//Forfeit Rock Transition
	forfeitRock.init(m_game->forfeitTexture, window);

	std::cout << "Passed transition setup" << std::endl; //DEBUG

	std::cout << "Main Game Init Done" << std::endl; //DEBUG

}

void MainGame::populatePlayers(std::vector<std::string> names) {
	//Player Names
	playerNames = names;

	playerAmt = static_cast<int>(playerNames.size());

	if (playerDisplay.size() != 0) {
		playerDisplay.clear();
	}

	if (playerPoints.size() != 0) {
		playerPoints.clear();
	}

	playerDisplay.resize(playerAmt);
	playerPoints.resize(playerAmt);

	



	float space = 20.0f;

	float spaceForNames = playerBoard.getSize().y - playerBoardTitle.getGlobalBounds().height - playerBoardDivider.getSize().y - space;
	float spacePerName = spaceForNames / m_game->getMaxPlayers(); //How much space each name has;
	float spacerY = spacePerName - playerBoard.getSize().y * 0.096;

	float initialY = playerBoard.getPosition().y + (playerBoardTitle.getGlobalBounds().height + playerBoardDivider.getSize().y) + space;

	for (int i = 0; i < playerAmt; i++) {
		playerPoints.at(i) = 0; //Initialise all points to 0
		if (i == 0) {
			//If first the set explicit position
			playerDisplay.at(i).initialise(playerNames.at(i), righteousFont, lcdFont, playerBoard.getPosition().x, initialY,
				playerBoard.getSize().x, playerBoard.getSize().y * 0.096, playerPoints.at(i));
		}
		else {
			//Set position dynamically
			playerDisplay.at(i).initialise(playerNames.at(i), righteousFont, lcdFont, playerBoard.getPosition().x, playerDisplay.at(i - 1).getPosition().y + playerDisplay.at(i - 1).getGlobalBounds().height + spacerY,
				playerBoard.getSize().x, playerBoard.getSize().y * 0.096, playerPoints.at(i));
		}
	}

	playerDisplay.at(currentGo).setSelected(true);
	playersPopulated = true;
}

void MainGame::calculateWinningPlayer() {
	auto maxIt = std::max_element(playerPoints.begin(), playerPoints.end()); //Find the iterator of the max element

	int maxIndex = std::distance(playerPoints.begin(), maxIt); //Index of player with highest points

	//std::cout << "The largest number is " << *maxIt << " at index " << maxIndex << std::endl;
	
	for (int i = 0; i < playerAmt; i++) {
		if (i == maxIndex) {
			std::cout << "#####Winning Player Found" << std::endl;
			//If this is the winning player
			playerDisplay.at(i).setWinningPlayer(true);
		}
		else {
			//Any other player
			std::cout << "Other Player Found" << std::endl;
			playerDisplay.at(i).setWinningPlayer(false);
		}
	}
}

void MainGame::awardPoint(int pointAmount, int currentPlayer, sf::Color pointColour, bool allPlayers) {
	std::string pointNotifierText;
	if (pointAmount == 1) {
		//if one point
		pointNotifierText = "+" + std::to_string(pointAmount) + " point";
	}
	else {
		//More than 1 point
		pointNotifierText = "+" + std::to_string(pointAmount) + " points";
	}

	pointNotifier.reset(pointNotifierText, pointColour, 15.0f, pointNotiferPos); //Get colour from card
	AudioManager::getInstance().playSoundEffect("pointGot");
	pointNotifier.go();

	if (allPlayers) {
		//Award a point to all players
		for (int i = 0; i < playerAmt; i++) {
			int newPoints = playerPoints.at(i) + pointAmount;
			playerPoints.at(i) = newPoints;
			playerDisplay.at(i).changePoints(newPoints);
		}
	}
	else {
		int newPoints = playerPoints.at(currentPlayer) + pointAmount;
		playerPoints.at(currentPlayer) = newPoints;
		playerDisplay.at(currentPlayer).changePoints(newPoints);
	}
}
	
void MainGame::pickCard() {
	std::cout << "Turns Played: " << turnsPlayed << "/" << m_game->cardImporter.getNumberOfCards() << std::endl;
	std::cout << "Check Used Cards State: " << m_game->checkAllCardsUsed() << std::endl;
	cardShown = false;

	// Check if all cards have been used
	if (m_game->checkAllCardsUsed()) {
		// If all cards have been used, display a message
		CustomMessageBox restartWarning("Pour Decisions", "All Cards have been used, would you like to start the cards again?", 2, window);
		MessageBoxButton result = restartWarning.showMessageBox(); // Show the message box

		if (result == MessageBoxButton::Ok) {
			std::cout << "Yes button clicked" << std::endl;
			m_game->resetUsedCards(); // Reset used cards
		}
		else {
			std::cout << "Any other button clicked" << std::endl;

			//Find the winning number
			auto maxIt = std::max_element(playerPoints.begin(), playerPoints.end());
			int index = std::distance(playerPoints.begin(), maxIt);

			std::cout << "A player has won" << std::endl;
			gameOver.initialise(playerNames.at(index));
			game_over = true;
			gameOver.setVisibility(true);
			return; // Exit early as there are no more cards
		}
	}

	// Pick a category, ensuring it is not full
	int catMax;
	if (m_game->usingCustomCards) {
		catMax = m_game->MAX_CATEGORIES;
	}
	else {
		catMax = m_game->DEFAULT_CATEGORIES_AMOUNT;
	}

	int category = -1;
	bool categoryPicked = false;
	std::string catName;

	// Loop to find a category with unused cards
	while (!categoryPicked) {
		category = rand() % catMax;
		catName = m_game->cardCategories.at(category);

		// Check if there are still unused cards in the chosen category
		if (m_game->usedCards[category].size() < m_game->cardQuantity.at(category)) {
			categoryPicked = true;
		}
		else {
			std::cout << "Category " << catName << " is full, picking another category..." << std::endl;
		}
	}

	std::cout << "Category Picked: " + catName << std::endl;

	bool cardPicked = false;
	int card = -1;

	// Loop to try picking a card from the chosen category
	while (!cardPicked) {
		int cardMax = m_game->cardQuantity.at(category); // Number of cards in the chosen category
		card = rand() % cardMax; // Randomly select a card

		// Check if the card has been used already
		bool cardAlreadyUsed = std::count(m_game->usedCards[category].begin(), m_game->usedCards[category].end(), card) > 0;

		if (cardAlreadyUsed) {
			// If the card has been used, pick another one
			std::cout << "Card already picked, selecting another card..." << std::endl;
		}
		else {
			// If the card hasn't been used, use it
			std::cout << "Found an unused card: " << card << std::endl;
			m_game->usedCards[category].push_back(card); // Mark this card as used
			cardPicked = true; // Successfully picked a new card
		}
	}

	// Display the picked card
	currentCardColour = m_game->cardColours.at(category);
	std::string cardTitleToShow = m_game->cardCategories.at(category);
	std::transform(cardTitleToShow.begin(), cardTitleToShow.end(), cardTitleToShow.begin(), ::toupper);
	std::string cardMessageToShow = m_game->cardQuestions[category][card];
	std::string motifLocation = MOTIF_BASE_LOCATION + m_game->motifLoc.at(category);
	bool groupCard = false;
	if (cardTitleToShow == "GROUP") {
		//Group Card
		groupCard = true;
	}

	// Display the card
	std::cout << "Scale X b4 nc call: " << m_game->scaleX << std::endl;
	cardDisplay.initialise(currentCardColour, righteousFont, ryeFont, cardTitleToShow, cardMessageToShow, motifLocation, m_game->scaleX, window, groupCard);
	cardShown = false;


	if (!spinner.isSpinning()) {
		spinner.spinToCategory(category, 1, 500.f, 8.f);
	}
	
}

void MainGame::cardPass(bool group) {
	if (group) {
		//It is a group card - award everyone 1 points
		cardShown = false;

		waitingForCardToBeHiddenPass = true;

		backToGameDeferredAction = [this]() {
			std::cout << "Card is hidden!" << std::endl;

			awardPoint(1, 0, currentCardColour, true);
			moveToNextPlayer();
		};
	}
	else {
		//Not a group card - award the player 2 points
		cardShown = false;

		waitingForCardToBeHiddenPass = true;

		backToGameDeferredAction = [this]() {
			std::cout << "Card is hidden!" << std::endl;

			awardPoint(2, currentGo, currentCardColour);
			moveToNextPlayer();
		};
	}
}

void MainGame::cardForfeit(bool group) {
	std::cout << "Forfeit Picked" << std::endl;

	cardShown = false;
	waitingForCardToBeHiddenForfeit = true;

	showForfeitDeferredAction = [this, group]() {
		std::cout << "Card is hidden!" << std::endl;
		AudioManager::getInstance().playSoundEffect("forfeitRock");
		forfeitRock.startRocking(); //Change this transition to make it fill the screen as a proper transition
		forfeitScreen.init(playerNames.at(currentGo), playerPoints.at(currentGo), group);
		forfeitScreen.setVisible(true);
	};
}

void MainGame::initForfeitCard(std::string title, std::string body, std::string motifName, bool group) {
	std::cout << "Scale X b4 fc call: " << m_game->scaleX << std::endl;
	std::string motifFileLocation = m_game->FORFEIT_MOTIF_LOC + motifName;
	forfeitCardDisplay.initialise(righteousFont, ryeFont, title, body, motifFileLocation, m_game->scaleX, window, group);
}

void MainGame::setForfeitCardVisible(bool visible) {
	//Show the card
	forfeitCardShown = visible;
}

void MainGame::forfeitComplete(bool group) {
	//The forfeit is complete
	if (group) {
		//the forfeit was for a group card - no one gets a point
		forfeitCardShown = false;

		waitingForCardToBeHiddenComplete = true;

		std::cout << "BEFORE THE DEFFERED ACTION FUNCTION" << std::endl;

		awardPointForForfeitCompleteAction = [this]() {
			std::cout << "Forfeit Card is hidden!" << std::endl;

			moveToNextPlayer();
		};
	}
	else {
		//The card was for an invidiual player
		forfeitCardShown = false;

		waitingForCardToBeHiddenComplete = true;

		std::cout << "BEFORE THE DEFFERED ACTION FUNCTION" << std::endl;

		awardPointForForfeitCompleteAction = [this]() {
			std::cout << "Forfeit Card is hidden!" << std::endl;

			awardPoint(1, currentGo, forfeitCardDisplay.getColour());
			moveToNextPlayer();
		};
	}
}

void MainGame::moveToNextPlayer() {
	turnsPlayed++;
	if (currentGo == playerAmt - 1) {
		currentGo = 0;
	}
	else {
		currentGo++;
	}

	for (int i = 0; i < playerAmt; i++) {
		if (i == currentGo) {
			playerDisplay.at(i).setSelected(true);
		}
		else {
			playerDisplay.at(i).setSelected(false);
		}
	}

}

void MainGame::update(float dt, sf::Vector2f clickPos) {

	spinner.update(dt);
	forfeitRock.update(dt);


	//Card
	if (cardShown) {
		cardDisplay.update(dt, clickPos);
	}

	//Changing from card back to game play - pass
	if (waitingForCardToBeHiddenPass && !cardDisplay.isCardVisible()) {
		waitingForCardToBeHiddenPass = false;
		if (backToGameDeferredAction) {
			backToGameDeferredAction();
			backToGameDeferredAction = nullptr;
		}
	}

	if (cardShown && !wasCardVisible) {
		AudioManager::getInstance().playSoundEffect("cardPick");
		wasCardVisible = true;
	}
	else if (!cardShown && wasCardVisible) {
		wasCardVisible = false;
	}

	//Forfeit Card
	if (forfeitCardShown) {
		forfeitCardDisplay.update(dt, clickPos);
	}

	//Changing from card to forfeit card - forfeit
	if (waitingForCardToBeHiddenForfeit && !cardDisplay.isCardVisible()) {
		waitingForCardToBeHiddenForfeit = false;
		if (showForfeitDeferredAction) {
			showForfeitDeferredAction();
			showForfeitDeferredAction = nullptr;
		}
	}

	//Changing from forfiet card to game play - forfeit complete
	if (waitingForCardToBeHiddenComplete && !forfeitCardDisplay.isCardVisible()) {
		waitingForCardToBeHiddenComplete = false;
		if (awardPointForForfeitCompleteAction) {
			awardPointForForfeitCompleteAction();
			awardPointForForfeitCompleteAction = nullptr;
		}
	}

	if (forfeitCardShown && !wasForfeitCardVisible) {
		AudioManager::getInstance().playSoundEffect("cardPick");
		wasForfeitCardVisible = true;
	}
	else if (!forfeitCardShown && wasForfeitCardVisible) {
		wasForfeitCardVisible = false;
	}

	
	//Spin Button
	if (!cardShown && !forfeitCardShown) {
		spinButton.handleHover(clickPos);
		pointNotifier.update(dt);
	}

	//Winning Player
	if (playersPopulated && turnsPlayed != 0 && currentGo != lastTurnNo) {
		//If players are present, and its not the first go workout who is winning - should only run once per turn
		calculateWinningPlayer();
		lastTurnNo = currentGo;

		//Get the winning player and check if their score has won, if so game over;
	}

	for (int i = 0; i < playerAmt; i++) {
		if (playerPoints.at(i) >= m_game->winPoints) {
			//This player has won
			std::cout << "A player has won" << std::endl;
			gameOver.initialise(playerNames.at(i));
			game_over = true;
			gameOver.setVisibility(true);
			break; //Exit
		}
	}

	//Game Over
	if (gameOver.getVisible()) {
		gameOver.update(dt, clickPos);
	}

	//Pause Menu
	if (pauseMenu.getVisible()) {
		pauseMenu.update(dt, clickPos);
	}

	//Forfeit Screen
	if (forfeitScreen.getVisible()) {
		forfeitScreen.update(dt, clickPos);
	}
}

void MainGame::handleKeypress(sf::Event event) {

	if (event.key.code == sf::Keyboard::Escape) {
		menu_visible = pauseMenu.getVisible();
		menu_visible = !menu_visible;
		pauseMenu.showMenu(menu_visible);
	}

	forfeitScreen.handleKeypress(event);
	
}

void MainGame::handleMouse(sf::Event event, sf::Vector2f clickPos) {
	
	if (menu_visible) {
		pauseMenu.handleMouse(event, clickPos);
	}
	else {
		menu_visible = pauseMenu.getVisible();
	}

	if (game_over) {
		gameOver.handleMouse(event, clickPos);
	}
	else {
		game_over = gameOver.getVisible();
	}

	//Forfeit Screen
	if (forfeitScreenShown) {
		forfeitScreen.handleMouse(clickPos);
	}
	else {
		forfeitScreenShown = forfeitScreen.getVisible();
	}

	if (!cardShown && !forfeitCardShown) {
		//Cant click the spin button if the card is displaying
		if (spinButton.isClicked(clickPos)) {
			pickCard();
		}
	}
	else if (cardShown) {
		//The card is shown
		cardDisplay.handleMouse(clickPos);
	}
	else if (forfeitCardShown) {
		//The forfeit card is shown
		forfeitCardDisplay.handleMouse(clickPos);
	}
	
}

void MainGame::draw(sf::RenderWindow& window, float dt) {
	GradientBackground::setBackgroundGradient(window);
	window.draw(playerBoard);
	window.draw(playerBoardTitle);

	for (int i = 0; i < playerAmt; i++) {
		playerDisplay.at(i).draw(window);
	}

	spinButton.draw(window);

	pointNotifier.draw(window);

	spinner.draw(window);
	window.draw(spinwheelClickerSprite);

	

	if (cardShown) {
		cardDisplay.showCard(window, dt);
	}
	else {
		cardDisplay.hideCard(window, dt);
	}

	if (forfeitCardShown) {
		forfeitCardDisplay.showCard(window, dt);
	}
	else {
		forfeitCardDisplay.hideCard(window, dt);
	}

	if (forfeitRock.getCompleted()) {
		forfeitScreen.draw(window);
	}

	forfeitRock.draw(window);

	pauseMenu.draw(window, dt);

	gameOver.draw(window, dt);

	
}


void MainGame::drawGradientBorder(sf::RenderWindow& window, const sf::FloatRect& rect, float borderThickness, sf::Color color1, sf::Color color2) {
	sf::VertexArray gradientBorder(sf::TriangleStrip, 8);

	// Outer rectangle vertices
	gradientBorder[0].position = sf::Vector2f(rect.left - borderThickness, rect.top - borderThickness);
	gradientBorder[1].position = sf::Vector2f(rect.left + rect.width + borderThickness, rect.top - borderThickness);
	gradientBorder[2].position = sf::Vector2f(rect.left - borderThickness, rect.top + rect.height + borderThickness);
	gradientBorder[3].position = sf::Vector2f(rect.left + rect.width + borderThickness, rect.top + rect.height + borderThickness);

	// Inner rectangle vertices
	gradientBorder[4].position = sf::Vector2f(rect.left, rect.top);
	gradientBorder[5].position = sf::Vector2f(rect.left + rect.width, rect.top);
	gradientBorder[6].position = sf::Vector2f(rect.left, rect.top + rect.height);
	gradientBorder[7].position = sf::Vector2f(rect.left + rect.width, rect.top + rect.height);

	// Assign gradient colors
	gradientBorder[0].color = color1;
	gradientBorder[1].color = color1;
	gradientBorder[2].color = color1;
	gradientBorder[3].color = color1;

	gradientBorder[4].color = color2;
	gradientBorder[5].color = color2;
	gradientBorder[6].color = color2;
	gradientBorder[7].color = color2;

	// Draw gradient border
	window.draw(gradientBorder);
}
