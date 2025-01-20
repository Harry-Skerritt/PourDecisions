#include "InputField.h"


InputField::InputField() {};
InputField::~InputField() {};

//Add rounded corner support

void InputField::setString(const std::string& text) {
	output.setString(text);
}

void InputField::setPlaceholder(const std::string& text) {
	placeholder = text;
	output.setString(placeholder);
	output.setColor(placeholderColour);
}

void InputField::setFont(const sf::Font& font) {
	output.setFont(font);
}

void InputField::setCharacterSize(unsigned int size) {
	output.setCharacterSize(size);
}

void InputField::setSize(float x, float y) {
	background.setSize(sf::Vector2f(x, y));
}

void InputField::setBackgroundColour(sf::Color backgroundColour) {
	background.setFillColor(backgroundColour);
}

void InputField::setTextColour(sf::Color textColourIn) {
	textColour = textColourIn;
}

void InputField::setPlaceholderColour(sf::Color placeholderColourIn) {
	placeholderColour = placeholderColourIn;
}

void InputField::setPosition(float x, float y) {
	sf::FloatRect outputBounds = output.getLocalBounds();
	output.setOrigin(outputBounds.left + outputBounds.width / 2, outputBounds.top + outputBounds.height / 2);

	background.setPosition(sf::Vector2f(x, y)); //Sets the background position

	output.setPosition(background.getPosition().x + background.getSize().x / 2,
		background.getPosition().y + background.getSize().y / 2);

}

void InputField::setBorder(float thickness, sf::Color colour) {
	borderThickness = thickness;
	borderColour = borderColour;
	background.setOutlineThickness(thickness);
	background.setOutlineColor(borderColour);
}

sf::FloatRect InputField::getGlobalBounds() {
	return background.getGlobalBounds();
}

sf::FloatRect InputField::getLocalBounds() {
	return background.getLocalBounds();
}

sf::Vector2f InputField::getPosition() {
	return background.getPosition();
}

bool InputField::isEmpty() {
	if (input_text.isEmpty()) {
		return true;
	}
	else {
		return false;
	}
}

void InputField::handleInput(sf::Event event) {
	if (event.text.unicode == 8) {
		//Backspace
		if (input_text.getSize() != 0) {
			input_text.erase(input_text.getSize() - 1, 1); //Removes last character
			output.setColor(textColour);
			output.setString(input_text);
		}
		else {
			//The string is empty 
			resetField();
		}
		
	}
	else {
		input_text += static_cast<char>(event.text.unicode); //Ammend the latest character
		output.setColor(textColour);
		output.setString(input_text);
	}
}

void InputField::resetField(bool usePlaceholder) {
	input_text = "";
	output.setColor(placeholderColour);
	output.setString(placeholder);
}

void InputField::draw(sf::RenderWindow& window) {
	window.draw(background);
	window.draw(output);
}