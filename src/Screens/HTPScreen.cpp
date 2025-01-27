#include "HTPScreen.h"
#include "../Game.h"

HowToPlayScreen::HowToPlayScreen(sf::RenderWindow& window, sf::Font& font1, sf::Font& font2) : window(window), righteousFont(font1), ryeFont(font2) {};

HowToPlayScreen::~HowToPlayScreen() {};

void HowToPlayScreen::setGameInstance(Game* game) {
	m_game = game;
}

void HowToPlayScreen::init() {

}

void HowToPlayScreen::update(float dt) {

}

void HowToPlayScreen::handleMouse(sf::Vector2f clickPos) {

}

void HowToPlayScreen::draw(sf::RenderWindow& window) {
	GradientBackground::setBackgroundGradient(window);
}

