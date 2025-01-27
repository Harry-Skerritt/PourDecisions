#include "SolidButton.h"

SolidButton::SolidButton() {};

SolidButton::~SolidButton() {};

void SolidButton::setBackgroundColor(const sf::Color& color, float x, float y) {
	buttonBackground.setSize(sf::Vector2f(x, y));
	buttonBackground.setFillColor(color);
	bounds = buttonBackground.getGlobalBounds();

	centerText();
}

void SolidButton::setBorder(sf::Color& color, float thickness) {
	buttonBackground.setOutlineColor(color);
	buttonBackground.setOutlineThickness(thickness);
}


void SolidButton::setText(const std::string& text, const sf::Font& font, unsigned int characterSize) {
	buttonText.setFont(font);
	buttonText.setString(text);
	buttonText.setCharacterSize(characterSize);

	// Adjust text size to fit within the button's width
	sf::FloatRect textBounds = buttonText.getLocalBounds();
	while (textBounds.width > bounds.width && characterSize > 5) {
		characterSize--; // Reduce the font size
		buttonText.setCharacterSize(characterSize);
		textBounds = buttonText.getLocalBounds();
	}

	//Centre Text
	centerText();
}

void SolidButton::setPosition(float x, float y) {
	buttonBackground.setPosition(x, y);
	bounds = buttonBackground.getGlobalBounds();

	//Update Text
	centerText();
}

void SolidButton::setPosition(sf::Vector2f size) {
	buttonBackground.setPosition(size.x, size.y);
	bounds = buttonBackground.getGlobalBounds();

	//Update Text
	centerText();
}

void SolidButton::setTextColor(sf::Color color) {
	normalColor = color;
	buttonText.setFillColor(normalColor);
}

void SolidButton::setHoverColor(sf::Color color) {
	hoverColor = color;
}

bool SolidButton::isClicked(const sf::Vector2f& mousePos) const {
	return bounds.contains(mousePos); //Might need to convert to win pos
}

void SolidButton::handleHover(const sf::Vector2f& mousePos) {
	if (bounds.contains(mousePos)) {
		buttonText.setFillColor(hoverColor);
	}
	else {
		buttonText.setFillColor(normalColor);
	}
}

sf::FloatRect SolidButton::getGlobalBounds() const {
	return buttonBackground.getGlobalBounds();
}

sf::FloatRect SolidButton::getLocalBounds() const {
	return buttonBackground.getLocalBounds();
}

sf::Vector2f SolidButton::getPosition() const {
	return buttonBackground.getPosition();
}

void SolidButton::setOrigin(float x, float y) {
	buttonBackground.setOrigin(x, y);
}

void SolidButton::draw(sf::RenderWindow& window) {
	window.draw(buttonBackground);
	window.draw(buttonText);
}

void SolidButton::setAlpha(sf::Uint8 alpha) {
	sf::Color bgColor = buttonBackground.getFillColor();
	bgColor.a = alpha;
	buttonBackground.setFillColor(bgColor);

	sf::Color borderColor = buttonBackground.getOutlineColor();
	borderColor.a = alpha;
	buttonBackground.setOutlineColor(borderColor);

	sf::Color textColor = buttonText.getFillColor();
	textColor.a = alpha;
	buttonText.setFillColor(textColor);
}

void SolidButton::centerText() {
	sf::FloatRect textBounds = buttonText.getLocalBounds();
	buttonText.setOrigin(textBounds.left + textBounds.width / 2, textBounds.top + textBounds.height / 2);
	buttonText.setPosition(bounds.left + bounds.width / 2, bounds.top + bounds.height / 2);
}