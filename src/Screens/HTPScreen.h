#ifndef HTP_SCREEN_H
#define HTP_SCREEN_H

#include <SFML/Graphics.hpp>
#include "../Utils/GradientText.h"
#include "../Utils/Widgets/Button.h"
#include <string>
#include <vector>

class Game;

class HowToPlayScreen {
public: 

	HowToPlayScreen(sf::RenderWindow& window, sf::Font& font1, sf::Font& font);
	~HowToPlayScreen();

	void setGameInstance(Game* game);

	void init();

	void update(float dt, sf::Vector2f clickPos);

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

	Button backButton;

	sf::Text rulesTitle;
	sf::Text gameplayTitle;

	std::vector<std::string> rules = {
		"1. The order you input players is the order of play",
		"2. Everyone needs something to drink",
		"3. Cards are worth 2 points, group cards are worth 1. If you forfeit a card you get 1 points, unless it's a group card then you get 0",
		"4. First to x points wins",
		"5. Regardless of how many people reach the winning point value, the first one to do so, will be declared the winner"
	};

	std::vector<std::string> gameplay = {
		"- The game is for 3 - 8 people",
		"- Player names are inputted on the player setup screen, you can click a name to remove them",
		"- Spin the wheel to get a card, if you do the card, you click pass and awarded points. If you dont, you click forfeit and spin for a forfeit card",
		"- If a card requries something to be done within a time limit, you will need to use a stopwatch to keep time. - If you fail to complete within the time, it's an automatic forfeit"
	};

	std::vector<sf::Text> rulesText;
	std::vector<sf::Text> gameplayText;

	sf::Color purpleColour = sf::Color(44, 3, 60, 255);
	sf::Color gradientColour1 = sf::Color(251, 0, 188, 255);
	sf::Color gradientColour2 = sf::Color(0, 238, 255, 255);

	std::string wrapText(const sf::Text& text, const sf::RectangleShape& rectangle, const sf::Font& font, unsigned int characterSize);

	void positionTextList(
		const sf::Text& headerText,
		std::vector<sf::Text>& textList,
		const sf::RectangleShape& rectangle,
		const sf::Font& font
	);

};


#endif