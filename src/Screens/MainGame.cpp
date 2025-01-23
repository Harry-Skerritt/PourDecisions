#include "MainGame.h"
#include "../Game.h"
#include "../Utils/GradientBackground.h"
#include "../Managers/AudioManager.h"

MainGame::MainGame(sf::RenderWindow& window, sf::Font& font1, sf::Font& font2, sf::Font& font3) : 
	window(window), righteousFont(font1), ryeFont(font2), lcdFont(font3), pauseMenu(window, righteousFont) {};
MainGame::~MainGame() {};

void MainGame::setGameInstance(Game* game) {
	m_game = game;
}

void MainGame::init() {
	//Vars Set
	currentGo = 0;
	turnsPlayed = 0;
	lastTurnNo = turnsPlayed;
	playersPopulated = false;
	menu_visible = false;
	pointNotiferPos = sf::Vector2f(400, 300); //Make Dyanmic

	//Pause menu
	pauseMenu.setGameInstance(m_game);
	pauseMenu.init();
	

	//Player Board
	playerBoard.setSize(sf::Vector2f(window.getSize().x * 0.23f, window.getSize().y * 0.9));
	playerBoard.setFillColor(sf::Color(44, 3, 60, 255));
	playerBoard.setPosition(window.getSize().x - playerBoard.getSize().x, window.getSize().y / 2 - playerBoard.getSize().y / 2);
	playerBoard.setOutlineThickness(8.0f);
	playerBoard.setOutlineColor(sf::Color(250, 0, 188, 255));

	//drawGradientBorder(window, playerBoard.getGlobalBounds(), 8.0f, sf::Color(252, 0, 189, 255), sf::Color(43, 3, 62, 255));

	playerBoardTitle.setFont(ryeFont);
	playerBoardTitle.setString("Players");
	playerBoardTitle.setCharacterSize(window.getSize().x * 0.04f);
	playerBoardTitle.setOrigin(playerBoardTitle.getGlobalBounds().width / 2, playerBoardTitle.getGlobalBounds().height / 2);
	playerBoardTitle.setPosition(playerBoard.getPosition().x + playerBoard.getGlobalBounds().width / 2, playerBoard.getPosition().y + playerBoardTitle.getGlobalBounds().height / 2);

	playerBoardDivider.setSize(sf::Vector2f(playerBoard.getSize().x * 0.75f, playerBoard.getSize().y * 0.004f));
	playerBoardDivider.setFillColor(sf::Color::White);
	playerBoardDivider.setOrigin(playerBoardDivider.getSize().x / 2, playerBoardDivider.getSize().y / 2);
	playerBoardDivider.setPosition(playerBoard.getPosition().x + playerBoard.getGlobalBounds().width / 2, playerBoardTitle.getPosition().y + playerBoardTitle.getGlobalBounds().height);

	playerDisplay.reserve(m_game->getMaxPlayers());
	playerNames.reserve(m_game->getMaxPlayers());

	//Spin Button
	spinButton.setBackgroundImage(m_game->buttonRectTexture);
	spinButton.setBackgroundScale(m_game->scaleX * 0.4f, m_game->scaleX * 0.4f);
	spinButton.setText("SPIN!", righteousFont, window.getSize().y * 0.055f);
	spinButton.setTextColor(m_game->buttonNormalColour);
	spinButton.setHoverColor(m_game->buttonHoverColour);
	float buttonX = (playerBoard.getPosition().x - spinButton.getGlobalBounds().width - (window.getSize().x * 0.026f));
	float buttonY = (playerBoard.getPosition().y + playerBoard.getGlobalBounds().height) - spinButton.getGlobalBounds().height - (window.getSize().y * 0.01f);
	spinButton.setPosition(buttonX, buttonY);

	//Point notifer
	pointNotifier.init(righteousFont, 1.5f); //1.5 seconds
	pointNotifier.reset("+1 Point", sf::Color::Red, 15.0f, pointNotiferPos);



}

void MainGame::populatePlayers(std::vector<std::string> names) {
	//Player Names
	playerNames = names;

	playerAmt = static_cast<int>(playerNames.size());
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

void MainGame::awardPoint(int pointAmount, int currentPlayer, bool allPlayers) {
	std::string pointNotifierText;
	if (pointAmount == 1) {
		//if one point
		pointNotifierText = "+" + std::to_string(pointAmount) + "point";
	}
	else {
		//More than 1 point
		pointNotifierText = "+" + std::to_string(pointAmount) + "points";
	}

	pointNotifier.reset(pointNotifierText, sf::Color::Blue, 15.0f, pointNotiferPos); //Get colour from card
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

void MainGame::update(float dt, sf::Vector2f clickPos) {
	spinButton.handleHover(clickPos);
	pointNotifier.update(dt);
	pauseMenu.update(dt, clickPos);

	if (playersPopulated && turnsPlayed != 0 && currentGo != lastTurnNo) {
		//If players are present, and its not the first go workout who is winning - should only run once per turn
		calculateWinningPlayer();
		lastTurnNo = currentGo;
	}
}

void MainGame::handleKeypress(sf::Event event) {
	//Debug
	if (event.key.code == sf::Keyboard::N) {
		awardPoint(2, currentGo);

		turnsPlayed++;
		if (currentGo == playerAmt - 1) {
			currentGo = 0;
		}
		else {
			currentGo++;
		}

	}

	if (event.key.code == sf::Keyboard::Escape) {
		menu_visible = !menu_visible;
		pauseMenu.showMenu(menu_visible);
	}
}

void MainGame::handleMouse(sf::Event event, sf::Vector2f clickPos) {
	
	if (menu_visible) {
		pauseMenu.handleMouse(event, clickPos);
	}
	else {
		menu_visible = pauseMenu.getVisible();
	}
}

void MainGame::draw(sf::RenderWindow& window) {
	GradientBackground::setBackgroundGradient(window);
	window.draw(playerBoard);
	window.draw(playerBoardTitle);

	for (int i = 0; i < playerAmt; i++) {
		playerDisplay.at(i).draw(window);
	}

	spinButton.draw(window);

	pointNotifier.draw(window);

	pauseMenu.draw(window);
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