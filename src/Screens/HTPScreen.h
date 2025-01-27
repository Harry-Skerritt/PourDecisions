#ifndef HTP_SCREEN_H
#define HTP_SCREEN_H

#include <SFML/Graphics.hpp>
#include "../Utils/GradientText.h"
#include "../Utils/Widgets/Button.h"

class Game;

class HowToPlayScreen {
public: 

	HowToPlayScreen(sf::RenderWindow& window, sf::Font& font1, sf::Font& font);
	~HowToPlayScreen();

	void setGameInstance(Game* game);

	void init();

	void update(float dt);

	void handleMouse(sf::Vector2f clickPos);

	void draw(sf::RenderWindow& window);

private:

	Game* m_game;

	sf::RenderWindow& window;
	sf::Font& righteousFont;
	sf::Font& ryeFont;

	GradientText titleText;
	sf::RectangleShape rulesBackground;
	sf::RectangleShape gameplayBackground;

	sf::Text rulesTitle;
	sf::Text gameplayTitle;

	sf::Text rule1;
	sf::Text rule2;
	sf::Text rule3;
	sf::Text rule4;
	sf::Text rule5;

	sf::Text gameplay1;
	sf::Text gameplay2;
	sf::Text gameplay3;
	sf::Text gameplay4;
};


#endif