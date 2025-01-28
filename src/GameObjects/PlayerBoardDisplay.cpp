#include "PlayerBoardDisplay.h"


PlayerBoardDisplay::PlayerBoardDisplay() {};
PlayerBoardDisplay::~PlayerBoardDisplay() {};

void PlayerBoardDisplay::initialise(std::string& playerName, sf::Font& playerNameFont, sf::Font& pointsFont, 
	float posX, float posY, float sizeX, float sizeY, int startPoints, int charSize)
{
	m_playerName = playerName;
	m_playerNameFont = playerNameFont;
	m_pointsFont = pointsFont;
	m_points = startPoints;

	if (charSize != 0) {
		m_playerNameCharSize = charSize;
		m_playerPointsCharSize = m_playerNameCharSize * 0.75f; //Points are 25% smaller than the name
	}


	//Setup background
	displayBackground.setSize(sf::Vector2f(sizeX, sizeY));
	displayBackground.setPosition(posX, posY);
	displayBackground.setFillColor(sf::Color::Transparent);
	displayBackground.setOutlineColor(sf::Color::Transparent);

	//Set character size based of background if not set in params
	m_playerNameCharSize = displayBackground.getSize().x * 0.14f;
	m_playerPointsCharSize = m_playerNameCharSize * 0.75f; //Points are 25% smaller than the name

	//Points box
	pointBox.setSize(sf::Vector2f(displayBackground.getSize().x * 0.22f, displayBackground.getSize().y * 0.60f));
	pointBox.setFillColor(m_pointsBackground);
	pointBox.setOutlineColor(sf::Color::White);
	pointBox.setOutlineThickness(displayBackground.getSize().x * 0.004f);
	pointBox.setOrigin(pointBox.getSize().x / 2, pointBox.getSize().y / 2);
	pointBox.setPosition((displayBackground.getPosition().x + displayBackground.getGlobalBounds().width * 0.82), displayBackground.getPosition().y + displayBackground.getGlobalBounds().height / 2);

	//Points text
	playerPoints.setFont(m_pointsFont);
	playerPoints.setString(std::to_string(m_points));
	playerPoints.setCharacterSize(m_playerPointsCharSize);
	playerPoints.setFillColor(m_pointsColour);

	sf::FloatRect pointsBounds = playerPoints.getLocalBounds();
	playerPoints.setOrigin(
		pointsBounds.left + pointsBounds.width / 2,  // Center horizontally
		pointsBounds.top + pointsBounds.height / 2  // Center vertically
	);
	playerPoints.setPosition(pointBox.getPosition().x, pointBox.getPosition().y);

	//Player Name
	playerNameText.setFont(m_playerNameFont);
	playerNameText.setString(m_playerName);
	playerNameText.setCharacterSize(m_playerNameCharSize);
	playerNameText.setFillColor(m_pointsColour);

	sf::FloatRect bounds = playerNameText.getLocalBounds();
	playerNameText.setOrigin(bounds.left + bounds.width / 2, bounds.top + bounds.height / 2);

	playerNameText.setPosition(
		pointBox.getPosition().x - (displayBackground.getSize().x * 0.47f),
		displayBackground.getPosition().y + displayBackground.getSize().y / 2
	);
}

void PlayerBoardDisplay::resizeObjects() {
	//Set character size based of background if not set in params
	m_playerNameCharSize = displayBackground.getSize().x * 0.14f;
	m_playerPointsCharSize = m_playerNameCharSize * 0.75f; //Points are 25% smaller than the name

	//Points box
	pointBox.setSize(sf::Vector2f(displayBackground.getSize().x * 0.22f, displayBackground.getSize().y * 0.60f));

	//Points text
	playerPoints.setCharacterSize(m_playerPointsCharSize);

	//Player name
	playerNameText.setCharacterSize(m_playerNameCharSize);
}

void PlayerBoardDisplay::repositionObjects() {
	resizeObjects();
	//Points box
	pointBox.setOrigin(pointBox.getSize().x / 2, pointBox.getSize().y / 2);
	pointBox.setPosition((displayBackground.getPosition().x + displayBackground.getGlobalBounds().width * 0.82), displayBackground.getPosition().y + displayBackground.getGlobalBounds().height / 2);

	//Points text
	sf::FloatRect pointsBounds = playerPoints.getLocalBounds();
	playerPoints.setOrigin(
		pointsBounds.left + pointsBounds.width / 2,  // Center horizontally
		pointsBounds.top + pointsBounds.height / 2  // Center vertically
	);
	playerPoints.setPosition(pointBox.getPosition().x, pointBox.getPosition().y);

	//Player name
	sf::FloatRect bounds = playerNameText.getLocalBounds();
	playerNameText.setOrigin(bounds.left + bounds.width / 2, bounds.top + bounds.height / 2);

	playerNameText.setPosition(
		pointBox.getPosition().x - (displayBackground.getSize().x * 0.47f),
		displayBackground.getPosition().y + displayBackground.getSize().y / 2
	);
}

void PlayerBoardDisplay::changePoints(int newPointValue) {
	m_points = newPointValue;
	playerPoints.setString(std::to_string(m_points));
	playerPoints.setCharacterSize(m_playerPointsCharSize);

	sf::FloatRect pointsBounds = playerPoints.getLocalBounds();
	playerPoints.setOrigin(
		pointsBounds.left + pointsBounds.width / 2,  // Center horizontally
		pointsBounds.top + pointsBounds.height / 2  // Center vertically
	);
	playerPoints.setPosition(pointBox.getPosition().x, pointBox.getPosition().y);
}

void PlayerBoardDisplay::update(float dt) {
	//Not needed
}

void PlayerBoardDisplay::draw(sf::RenderWindow& window) {
	window.draw(displayBackground);
	window.draw(pointBox);
	window.draw(playerPoints);
	window.draw(playerNameText);
}

//Setters
void PlayerBoardDisplay::setPointsColour(sf::Color& pointsColour, sf::Color& winningColour) {
	m_pointsColour = pointsColour;
	m_winningColour = winningColour;
}

void PlayerBoardDisplay::setSelectedColour(sf::Color& selectedColour) {
	m_selectedColour = selectedColour;
}

void PlayerBoardDisplay::setPointsBackgroundColour(sf::Color& colour) {
	m_pointsBackground = colour;
}

void PlayerBoardDisplay::setPosition(float x, float y) {
	displayBackground.setPosition(x, y);
	repositionObjects();
}

void PlayerBoardDisplay::setSize(float x, float y) {
	displayBackground.setSize(sf::Vector2f(x, y));
	repositionObjects();
}

void PlayerBoardDisplay::setSelected(bool state) {
	m_isSelected = state;

	if (m_isSelected) {
		//If selected
		displayBackground.setOutlineThickness(4.0f);
		displayBackground.setOutlineColor(m_winningColour);
		displayBackground.setFillColor(m_selectedColour);
	}
	else {
		//Not selected
		displayBackground.setOutlineColor(sf::Color::Transparent);
		displayBackground.setFillColor(sf::Color::Transparent);
	}
}

void PlayerBoardDisplay::setWinningPlayer(bool state) {
	m_isWinning = state;
	
	if (m_isWinning) {
		//If winning
		//playerPoints.setFillColor(m_winningColour);
		playerPoints.setColor(m_winningColour);
	}
	else {
		//Not winning
		//playerPoints.setFillColor(m_pointsColour);
		playerPoints.setColor(m_pointsColour);
	}
}

//Getters
sf::FloatRect PlayerBoardDisplay::getGlobalBounds() const {
	return displayBackground.getGlobalBounds();
}

sf::FloatRect PlayerBoardDisplay::getLocalBounds() const {
	return displayBackground.getLocalBounds();
}

sf::Vector2f PlayerBoardDisplay::getPosition() const {
	return displayBackground.getPosition();
}