#include "Button.h"

Button::Button() {};

Button::~Button() {};

void Button::setBackgroundImage(const sf::Texture& texture) {
	backgroundSprite.setTexture(texture);
	bounds = backgroundSprite.getGlobalBounds();
}

void Button::setBackgroundScale(float x, float y) {
	backgroundSprite.setScale(x, y);
}

void Button::setBackgroundScale(sf::Vector2f size) {
	backgroundSprite.setScale(size.x, size.y);
}

void Button::setText(const std::string& text, const sf::Font& font, unsigned int characterSize) {
	buttonText.setFont(font);
	buttonText.setString(text);
	buttonText.setCharacterSize(characterSize);

	//Centre Text
	sf::FloatRect textBounds = buttonText.getLocalBounds();
	buttonText.setOrigin(textBounds.left + textBounds.width / 2, textBounds.top + textBounds.height / 2);
	buttonText.setPosition(bounds.left + bounds.width / 2, bounds.top + bounds.height / 2);
}

void Button::setPosition(float x, float y) {
	backgroundSprite.setPosition(x, y);
	bounds = backgroundSprite.getGlobalBounds();

	//Update Text
	buttonText.setPosition(bounds.left + bounds.width / 2, bounds.top + bounds.height / 2);
}

void Button::setPosition(sf::Vector2f size) {
	backgroundSprite.setPosition(size.x, size.y);
	bounds = backgroundSprite.getGlobalBounds();

	//Update Text
	buttonText.setPosition(bounds.left + bounds.width / 2, bounds.top + bounds.height / 2);
}

void Button::setTextColor(sf::Color color) {
	normalColor = color;
	buttonText.setFillColor(normalColor);
}

void Button::setHoverColor(sf::Color color) {
	hoverColor = color;
}

bool Button::isClicked(const sf::Vector2f& mousePos) const {
	return bounds.contains(mousePos); //Might need to convert to win pos
}

void Button::handleHover(const sf::Vector2f& mousePos) {
	if (bounds.contains(mousePos)) {
		buttonText.setFillColor(hoverColor);
	}
	else {
		buttonText.setFillColor(normalColor);
	}
}

sf::FloatRect Button::getGlobalBounds() const {
	return backgroundSprite.getGlobalBounds();
}

sf::FloatRect Button::getLocalBounds() const {
	return backgroundSprite.getLocalBounds();
}

sf::Vector2f Button::getPosition() const {
	return backgroundSprite.getPosition();
}

void Button::setOrigin(float x, float y) {
	backgroundSprite.setOrigin(x, y);
}

void Button::draw(sf::RenderWindow& window) {
	window.draw(backgroundSprite);
	window.draw(buttonText);
}