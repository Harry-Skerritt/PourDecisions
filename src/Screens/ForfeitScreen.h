#ifndef FORFEITSCREEN_H
#define FORFEITSCREEN_H

#include <SFML/Graphics.hpp>
#include "../Utils/GradientBackground.h"
#include "../GameObjects/PlayerBoardDisplay.h"
#include "../Utils/Widgets/Button.h"
#include "../VisualAddons/SpinWheel.h"

class Game;
class MainGame;

class ForfeitScreen {
public:

	ForfeitScreen(sf::RenderWindow& window, sf::Font& font1, sf::Font& font2, sf::Font& font3);
	~ForfeitScreen();

	void init(std::string playerName, int playerPoints, bool groupCard);

	void setGameInstance(Game* game);
	void setMainGameInstance(MainGame* mainGame);

	void chooseForfeitCard();

	bool getVisible();
	void setVisible(bool state);

	void update(float dt, sf::Vector2f clickPos);

	void handleMouse(sf::Vector2f clickPos);
	void handleKeypress(sf::Event event);

	void draw(sf::RenderWindow& window);


private:

	Game* m_game;
	MainGame* m_mainGame;

	bool isVisible;
	bool group;

	sf::RenderWindow& window;
	sf::Font& righteousFont;
	sf::Font& ryeFont;
	sf::Font& lcdFont;

	sf::Sprite forfeitSign;

	PlayerBoardDisplay forfeitPlayer;

	Button spinButton;

	sf::Sprite spinWheelClicker;
	sf::Texture forfeitWheelTexture;
	sf::Sprite forfeitWheelSprite;
	SpinWheel forfeitSpinner;

};



#endif