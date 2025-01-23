#include "PauseMenu.h"
#include "../../Game.h"
#include "../../Managers/AudioManager.h"
#include <iostream>

PauseMenu::PauseMenu(sf::RenderWindow& window, sf::Font& font) : window(window), font(font) {};
PauseMenu::~PauseMenu() {};

void PauseMenu::setGameInstance(Game* game) {
	m_game = game;
}

//MAKE IT ACTUALL PAUSE THE GAME

void PauseMenu::init() {

	menu_visible = false;

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
	pausedTitle.setCharacterSize(80);
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

void PauseMenu::draw(sf::RenderWindow& window) {
	if (menu_visible) {
		window.draw(screenDarken);
		window.draw(menuBackground);
		window.draw(pausedTitle);
		resumeButton.draw(window);
		optionsButton.draw(window);
		quitButton.draw(window);
	}
	
}

void PauseMenu::showMenu(bool state) {
	menu_visible = state;
}

void PauseMenu::handleMouse(sf::Event event, sf::Vector2f clickPos) {
	if (resumeButton.isClicked(clickPos)) {
		std::cout << "Resume Clicked" << std::endl;
		AudioManager::getInstance().playSoundEffect("buttonClick");
		menu_visible = false;
	}
	
	if (optionsButton.isClicked(clickPos)) {
		std::cout << "Options Clicked" << std::endl;
		AudioManager::getInstance().playSoundEffect("buttonClick");
		menu_visible = false;
	}
	
	if (quitButton.isClicked(clickPos)) {
		std::cout << "Quit Clicked" << std::endl;
		AudioManager::getInstance().playSoundEffect("buttonClick");
		menu_visible = false;
		m_game->backToMainMenu(3);
	}
}

bool PauseMenu::getVisible() {
	return menu_visible;
}