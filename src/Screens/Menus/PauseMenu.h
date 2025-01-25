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

	void draw(sf::RenderWindow& window, float dt);

	void drawFadeComponents(sf::RenderWindow& window, sf::RectangleShape& screenDarken,
		sf::RectangleShape& menuBackground, GradientText& title, Button resume, Button options, Button quit, float dt, float speed, bool fadeIn);

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

	float fadeProgress = 0.0f; // Tracks the fade-in/out progress
	
};

#endif