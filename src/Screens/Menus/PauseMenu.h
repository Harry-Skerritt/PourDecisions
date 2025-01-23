#ifndef PAUSEMENU_H
#define PAUSEMENU_H

#include <SFML/Graphics.hpp>
#include "../../Utils/Widgets/Button.h"
#include "../../Utils/GradientText.h"

class Game;

class PauseMenu {
public:

	PauseMenu(sf::RenderWindow& window, sf::Font& font);
	~PauseMenu();

	void setGameInstance(Game* game);

	void init();

	void update(float dt, sf::Vector2f clickPos);

	void draw(sf::RenderWindow& window);

	void handleMouse(sf::Event event, sf::Vector2f clickPos);

	void showMenu(bool state);

	bool getVisible();

private:

	sf::RenderWindow& window;
	sf::Font& font;
	Game* m_game;

	bool menu_visible;

	sf::RectangleShape screenDarken;
	sf::RectangleShape menuBackground;

	GradientText pausedTitle;

	Button resumeButton;
	Button optionsButton;
	Button quitButton;
	
};

#endif