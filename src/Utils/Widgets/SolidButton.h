#ifndef SOLIDBUTTON_H
#define SOLIDBUTTON_H
#pragma once

#include <SFML/Graphics.hpp>
#include <string>


class SolidButton {
public:
	SolidButton();
	~SolidButton();

	void setBackgroundColor(const sf::Color& color, float x, float y);

	void setBorder(sf::Color& color, float thickness);


	void setText(const std::string& text, const sf::Font& font, unsigned int characterSize);

	void setPosition(float x, float y);
	void setPosition(sf::Vector2f size);

	void setTextColor(sf::Color color);

	void setHoverColor(sf::Color color);

	bool isClicked(const sf::Vector2f& mousePos) const;

	void handleHover(const sf::Vector2f& mousePos);

	sf::FloatRect getGlobalBounds() const;
	sf::FloatRect getLocalBounds() const;

	void setOrigin(float x, float y);

	sf::Vector2f getPosition() const;

	void draw(sf::RenderWindow& window);

	void setAlpha(sf::Uint8 alpha);

	

private:
	sf::RectangleShape buttonBackground;
	sf::Text buttonText;
	sf::FloatRect bounds;

	sf::Color normalColor;
	sf::Color hoverColor;

	void centerText(); // Helper Func
};

#endif //SOLIDBUTTON_H