#ifndef GAMEOVER_H
#define GAMEOVER_H

#include <SFML/Graphics.hpp>
#include "../../Utils/Widgets/Button.h"
#include "../../Utils/GradientText.h"
#include <string>

class Game;

class GameOver {
public:
	GameOver(sf::RenderWindow& window, sf::Font& font1, sf::Font& font2);
	~GameOver();

	void setGameInstance(Game* game);

	void initialise(std::string winningPlayerName);

	void update(float dt, sf::Vector2f clickPos);

	void draw(sf::RenderWindow& window, float dt);

	void drawFadeComponents(
		sf::RenderWindow& window,
		sf::RectangleShape& screenDarken,
		GradientText& title,
		sf::Text& winText,
		sf::Text& playerName,
		Button credits,
		Button playAgain,
		Button quit,
		float dt,
		float speed,
		bool fadeIn
	);

	void setVisibility(bool state);
	bool getVisible();

	void handleMouse(sf::Event event, sf::Vector2f clickPos);

private:
	sf::RenderWindow& window;
	bool visible;
	Game* m_game;

	sf::RectangleShape screenDarken;

	sf::Font& righteousFont;
	sf::Font& ryeFont;

	GradientText gameOverText;
	sf::Text winningText;
	sf::Text winningPlayerText;

	sf::Color whiteColour = sf::Color::White;
	sf::Color gradientBottom = sf::Color(254, 214, 133, 255);
	sf::Color gradientTop = sf::Color(251, 233, 183, 255);
	sf::Color borderColour = sf::Color(107, 2, 100, 255);

	Button creditsButton;
	Button playAgainButton;
	Button quitToMenuButton;

};



#endif