#include "GameOver.h"
#include "../../Game.h"

GameOver::GameOver(sf::RenderWindow& window, sf::Font& font1, sf::Font& font2) : window(window), righteousFont(font1), ryeFont(font2) {};
GameOver::~GameOver() {};


void GameOver::setGameInstance(Game* game) {
	m_game = game;
}

void GameOver::initialise(std::string winningPlayerName) {

	visible = false;

	screenDarken.setSize(sf::Vector2f(window.getSize().x, window.getSize().y));
	screenDarken.setFillColor(sf::Color(0, 0, 0, 179));

	//Title
	gameOverText.setFont(ryeFont);
	gameOverText.setString("GAME OVER");
	gameOverText.setCharacterSize(window.getSize().y * 0.23f);
	gameOverText.setGradientColors(gradientTop, gradientBottom);
	gameOverText.setPosition(window.getSize().x / 2 - (gameOverText.getGlobalBounds().width / 2), window.getSize().y * 0.24f);

	//Winning player text
	winningText.setFont(ryeFont);
	winningText.setString("The Winning Player Is:");
	winningText.setCharacterSize(window.getSize().y * 0.088f);
	winningText.setFillColor(gradientBottom);
	winningText.setPosition(window.getSize().x / 2 - (winningText.getGlobalBounds().width / 2), gameOverText.getPosition().y + window.getSize().y * 0.2f);

	//Winning player name
	winningPlayerText.setFont(righteousFont);
	winningPlayerText.setString(winningPlayerName);
	winningPlayerText.setCharacterSize(window.getSize().y * 0.11f);
	winningPlayerText.setFillColor(whiteColour);
	winningPlayerText.setPosition(window.getSize().x / 2 - (winningPlayerText.getGlobalBounds().width / 2), winningText.getPosition().y + window.getSize().y * 0.15f);

	//Credits
	creditsButton.setBackgroundImage(m_game->buttonThinRectTexture);
	creditsButton.setBackgroundScale(m_game->scaleX * 0.5f, m_game->scaleX * 0.6f);
	creditsButton.setText("Credits", righteousFont, window.getSize().y * 0.06f);
	creditsButton.setTextColor(m_game->buttonNormalColour);
	creditsButton.setHoverColor(m_game->buttonHoverColour);

	//Play Again
	playAgainButton.setBackgroundImage(m_game->buttonThinRectTexture);
	playAgainButton.setBackgroundScale(m_game->scaleX * 0.5f, m_game->scaleX * 0.6f);
	playAgainButton.setText("Play Again", righteousFont, window.getSize().y * 0.06f);
	playAgainButton.setTextColor(m_game->buttonNormalColour);
	playAgainButton.setHoverColor(m_game->buttonHoverColour);

	//Quit
	quitToMenuButton.setBackgroundImage(m_game->buttonThinRectTexture);
	quitToMenuButton.setBackgroundScale(m_game->scaleX * 0.5f, m_game->scaleX * 0.6f);
	quitToMenuButton.setText("Quit To Menu", righteousFont, window.getSize().y * 0.06f);
	quitToMenuButton.setTextColor(m_game->buttonNormalColour);
	quitToMenuButton.setHoverColor(m_game->buttonHoverColour);

	// Force textures to update their sizes
	float buttonSpacing = window.getSize().x * 0.02f; // Adjust spacing
	float totalWidth = 3 * playAgainButton.getGlobalBounds().width + 2 * buttonSpacing;
	float startX = (window.getSize().x - totalWidth) / 2.0f;

	// Set positions after ensuring all properties are set
	creditsButton.setPosition(startX, window.getSize().y * 0.85f);
	playAgainButton.setPosition(creditsButton.getPosition().x + creditsButton.getGlobalBounds().width + buttonSpacing, window.getSize().y * 0.85f);
	quitToMenuButton.setPosition(playAgainButton.getPosition().x + playAgainButton.getGlobalBounds().width + buttonSpacing, window.getSize().y * 0.85f);

}

void GameOver::update(float dt, sf::Vector2f clickPos) {
	creditsButton.handleHover(clickPos);
	playAgainButton.handleHover(clickPos);
	quitToMenuButton.handleHover(clickPos);
}

void GameOver::draw(sf::RenderWindow& window, float dt) {
	//Show the menu
	drawFadeComponents(window,
		screenDarken,
		gameOverText,
		winningText,
		winningPlayerText,
		creditsButton,
		playAgainButton,
		quitToMenuButton,
		dt,
		1.5f,
		visible);
}

void GameOver::drawFadeComponents(
	sf::RenderWindow& window,
	sf::RectangleShape& screenDarken,
	GradientText& title,
	sf::Text& winText,
	sf::Text& playerName,
	Button credits,
	Button playAgain,
	Button quit,
	float dt,
	float speed,
	bool fadeIn
) {
	static float fadeProgress = fadeIn ? 0.0f : 1.0f;

	//Update progress
	fadeProgress += (fadeIn ? speed : -speed) * dt;
	fadeProgress = std::clamp(fadeProgress, 0.0f, 1.0f);

	//Calc alpha
	sf::Uint8 alpha = static_cast<sf::Uint8>(fadeProgress * 255);
	sf::Uint8 darkenAlpha = static_cast<sf::Uint8>(fadeProgress * 179);

	//Screen darken
	sf::Color darkenColour = screenDarken.getFillColor();
	darkenColour.a = darkenAlpha;
	screenDarken.setFillColor(darkenColour);

	//Title
	title.setAlpha(alpha);

	//Win Text
	sf::Color winTextColour = winText.getFillColor();
	winTextColour.a = alpha;
	winText.setFillColor(winTextColour);

	//Player Name
	sf::Color playerNameColour = playerName.getFillColor();
	playerNameColour.a = alpha;
	playerName.setFillColor(playerNameColour);


	// Buttons
	credits.setAlpha(alpha);
	playAgain.setAlpha(alpha);
	quit.setAlpha(alpha);

	window.draw(screenDarken);
	window.draw(title);
	window.draw(winText);
	window.draw(playerName);
	credits.draw(window);
	playAgain.draw(window);
	quit.draw(window);
}

void GameOver::setVisibility(bool state) {
	visible = state;
}

void GameOver::handleMouse(sf::Event event, sf::Vector2f clickPos) {
	if (creditsButton.isClicked(clickPos)) {
		std::cout << "Credits Clicked" << std::endl;
		AudioManager::getInstance().playSoundEffect("buttonClick");
		setVisibility(false);
	}

	if (playAgainButton.isClicked(clickPos)) {
		std::cout << "Play Again Clicked" << std::endl;
		AudioManager::getInstance().playSoundEffect("buttonClick");
		setVisibility(false);
	}

	if (quitToMenuButton.isClicked(clickPos)) {
		std::cout << "Quit Clicked" << std::endl;
		AudioManager::getInstance().playSoundEffect("buttonClick");
		setVisibility(false);
		m_game->backToMainMenu(3);
	}
}

bool GameOver::getVisible() {
	return visible;
}
