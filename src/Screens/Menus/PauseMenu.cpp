#include "PauseMenu.h"
#include "../../Game.h"
#include "../../Managers/AudioManager.h"
#include <iostream>

PauseMenu::PauseMenu(sf::RenderWindow& window, sf::Font& font) : window(window), font(font) 
{
	menu_visible = false;
};
PauseMenu::~PauseMenu() {};

void PauseMenu::setGameInstance(Game* game) {
	m_game = game;
}

//MAKE IT ACTUALL PAUSE THE GAME

void PauseMenu::init() {

	//Darken Screen
	screenDarken.setSize(sf::Vector2f(window.getSize().x, window.getSize().y));
	screenDarken.setFillColor(sf::Color(0, 0, 0, 179));

	//Menu Background
	menuBackground.setSize(sf::Vector2f(window.getSize().x * 0.45f, window.getSize().y * 0.89f));
	menuBackground.setFillColor(sf::Color(44, 3, 60, 255));
	menuBackground.setPosition(window.getSize().x / 2 - menuBackground.getGlobalBounds().width / 2, window.getSize().y / 2 - menuBackground.getGlobalBounds().height / 2); //Centre to the screen

	//Title
	pausedTitle.setFont(font);
	pausedTitle.setString("PAUSED");
	pausedTitle.setCharacterSize(window.getSize().x * 0.11f);
	pausedTitle.setGradientColors(sf::Color(251, 0, 188, 255), sf::Color(0, 238, 255, 255));
	pausedTitle.setPosition(menuBackground.getPosition().x + ((menuBackground.getSize().x / 2) - (pausedTitle.getGlobalBounds().width / 2)), 60);
	//pausedTitle.setPosition(((menuBackground.getSize().x / 2) - (pausedTitle.getGlobalBounds().width / 2)), 60);

	//Resume Button
	resumeButton.setBackgroundImage(m_game->buttonThinRectTexture);
	resumeButton.setBackgroundScale(m_game->scaleX * 0.6f, m_game->scaleX * 0.6f);
	resumeButton.setText("Resume", font, window.getSize().y * 0.078f);
	resumeButton.setTextColor(m_game->buttonNormalColour);
	resumeButton.setHoverColor(m_game->buttonHoverColour); 
	resumeButton.setPosition(menuBackground.getPosition().x + (menuBackground.getSize().x / 2 - resumeButton.getGlobalBounds().width / 2), (pausedTitle.getPosition().y + resumeButton.getGlobalBounds().height /2) + menuBackground.getSize().y * 0.14f);

	//Options Button
	optionsButton.setBackgroundImage(m_game->buttonThinRectTexture);
	optionsButton.setBackgroundScale(m_game->scaleX * 0.6f, m_game->scaleX * 0.6f);
	optionsButton.setText("Options", font, window.getSize().y * 0.059f);
	optionsButton.setTextColor(m_game->buttonNormalColour);
	optionsButton.setHoverColor(m_game->buttonHoverColour);
	optionsButton.setPosition(menuBackground.getPosition().x + (menuBackground.getSize().x / 2 - optionsButton.getGlobalBounds().width / 2), (resumeButton.getPosition().y + optionsButton.getGlobalBounds().height / 2) + menuBackground.getSize().y * 0.4f);


	//Quit Button
	quitButton.setBackgroundImage(m_game->buttonThinRectTexture);
	quitButton.setBackgroundScale(m_game->scaleX * 0.6f, m_game->scaleX * 0.6f);
	quitButton.setText("Quit to Menu", font, window.getSize().y * 0.059f);
	quitButton.setTextColor(m_game->buttonNormalColour);
	quitButton.setHoverColor(m_game->buttonHoverColour);
	quitButton.setPosition(menuBackground.getPosition().x + (menuBackground.getSize().x / 2 - quitButton.getGlobalBounds().width / 2), (optionsButton.getPosition().y + quitButton.getGlobalBounds().height / 2) + menuBackground.getSize().y * 0.1f);
}

void PauseMenu::update(float dt, sf::Vector2f clickPos) {
	resumeButton.handleHover(clickPos);
	optionsButton.handleHover(clickPos);
	quitButton.handleHover(clickPos);
}

void PauseMenu::draw(sf::RenderWindow& window, float dt) {
	//Show the menu
	drawFadeComponents(window,
		screenDarken,
		menuBackground,
		pausedTitle,
		resumeButton,
		optionsButton,
		quitButton,
		dt,
		1.5f,
		menu_visible);

	
}

void PauseMenu::drawFadeComponents(
	sf::RenderWindow& window,
	sf::RectangleShape& screenDarken,
	sf::RectangleShape& menuBackground,
	GradientText& title,
	Button resume,
	Button options,
	Button quit,
	float dt,
	float speed,
	bool fadeIn
) {
	// Update progress
	fadeProgress += (fadeIn ? speed : -speed) * dt;
	fadeProgress = std::clamp(fadeProgress, 0.0f, 1.0f);

	// If fully faded out and fadeIn is false, stop rendering
	if (!fadeIn && fadeProgress <= 0.0f) {
		return;
	}

	// Calculate alpha
	sf::Uint8 alpha = static_cast<sf::Uint8>(fadeProgress * 255);
	sf::Uint8 darkenAlpha = static_cast<sf::Uint8>(fadeProgress * 179);

	// Update colors
	sf::Color darkenColour = screenDarken.getFillColor();
	darkenColour.a = darkenAlpha;
	screenDarken.setFillColor(darkenColour);

	sf::Color backgroundColour = menuBackground.getFillColor();
	backgroundColour.a = alpha;
	menuBackground.setFillColor(backgroundColour);

	title.setAlpha(alpha);
	resume.setAlpha(alpha);
	options.setAlpha(alpha);
	quit.setAlpha(alpha);

	// Draw components
	window.draw(screenDarken);
	window.draw(menuBackground);
	window.draw(title);
	resume.draw(window);
	options.draw(window);
	quit.draw(window);
}

void PauseMenu::showMenu(bool state) {
	menu_visible = state;
}

void PauseMenu::handleMouse(sf::Event event, sf::Vector2f clickPos) {
	if (resumeButton.isClicked(clickPos)) {
		std::cout << "Resume Clicked" << std::endl;
		AudioManager::getInstance().playSoundEffect("buttonClick");
		showMenu(false);
	}
	
	if (optionsButton.isClicked(clickPos)) {
		std::cout << "Options Clicked" << std::endl;
		AudioManager::getInstance().playSoundEffect("buttonClick");
		showMenu(false);
		m_game->toOptions(3);
	}
	
	if (quitButton.isClicked(clickPos)) {
		std::cout << "Quit Clicked" << std::endl;
		AudioManager::getInstance().playSoundEffect("buttonClick");
		showMenu(false);
		m_game->backToMainMenu(3);
	}
}

bool PauseMenu::getVisible() {
	return menu_visible;
}