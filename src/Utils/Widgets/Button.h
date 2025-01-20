#ifndef BUTTON_H
#define BUTTON_H
#pragma once

#include <SFML/Graphics.hpp>
#include <string>

class Button {
public:
	Button();
	~Button();

	void setBackgroundImage(const sf::Texture& texture);

	void setBackgroundScale(float x, float y);
	void setBackgroundScale(sf::Vector2f size);

	void setText(const std::string& text, const sf::Font& font, unsigned int characterSize);

	void setPosition(float x, float y);
	void setPosition(sf::Vector2f size);

	void setTextColor(sf::Color color);

	void setHoverColor(sf::Color color);
	
	bool isClicked(const sf::Vector2f& mousePos) const;

	void handleHover(const sf::Vector2f& mousePos);

	sf::FloatRect getGlobalBounds() const;
	sf::FloatRect getLocalBounds() const;

	void draw(sf::RenderWindow& window);

private:
	sf::Sprite backgroundSprite;
	sf::Text buttonText;
	sf::FloatRect bounds;

	sf::Color normalColor;
	sf::Color hoverColor;
};

#endif