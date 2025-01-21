#ifndef INPUTFIELD_H
#define INPUTFIELD_H

#include <SFML/Graphics.hpp>

class InputField
{
public:
	InputField();
	~InputField();

	void setString(const std::string& text);
	void setPlaceholder(const std::string& text);
	void setFont(const sf::Font& font);
	void setCharacterSize(unsigned int size);
	void setSize(float x, float y);
	void setTextColour(sf::Color textColourIn);
	void setPlaceholderColour(sf::Color placeholderColourIn);
	void setBackgroundColour(sf::Color backgroundColour);
	void setPosition(float x, float y);
	void setBorder(float thickness, sf::Color colour);

	sf::FloatRect getGlobalBounds();
	sf::FloatRect getLocalBounds();
	sf::Vector2f getPosition();

	bool isEmpty();

	std::string getCurrentValue();

	void handleInput(sf::Event event, bool inputAllowed = true);
	void resetField(bool usePlaceholder = true);
	void draw(sf::RenderWindow& window);

private:
	

	sf::String input_text;
	sf::String placeholder;

	sf::Color placeholderColour = sf::Color(176, 176, 176, 255);
	sf::Color textColour = sf::Color::White;
	float borderThickness = 0;
	sf::Color borderColour = sf::Color::Black;

	sf::Text output;
	sf::RectangleShape background;




};

#endif