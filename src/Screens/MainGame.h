#ifndef MAINGAME_H
#define MAINGAME_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <algorithm>
#include <functional>

#include "../GameObjects/PlayerBoardDisplay.h"
#include "../GameObjects/Card.h"
#include "../GameObjects/ForfeitCard.h"

#include "../Utils/Widgets/Button.h"
#include "../Utils/Widgets/GrowFadeText.h"

#include "../Screens/Menus/PauseMenu.h"
#include "../Screens/Menus/GameOver.h"

#include "../VisualAddons/SpinWheel.h"

class Game;

class MainGame {
public:

	MainGame(sf::RenderWindow& window, sf::Font& font1, sf::Font& font2, sf::Font& font3);
	~MainGame();

	void setGameInstance(Game* game);

	void init();

	void populatePlayers(std::vector<std::string> names);
	void calculateWinningPlayer();
	void awardPoint(int pointValue, int currentPlayer, sf::Color pointColour, bool allPlayers = false);

	void update(float dt, sf::Vector2f clickPos);

	void handleKeypress(sf::Event event);
	void handleMouse(sf::Event event, sf::Vector2f clickPos);

	void pickCard();

	void cardPass(bool group);

	void cardForfeit(bool group);

	void forfeitComplete(bool group);

	void moveToNextPlayer();

	void draw(sf::RenderWindow& window, float dt);


private:

	Game* m_game;
	sf::RenderWindow& window;
	sf::Font& righteousFont;
	sf::Font& ryeFont;
	sf::Font& lcdFont;

	PauseMenu pauseMenu;
	bool menu_visible;

	GameOver gameOver;
	bool game_over;

	//Player List
	sf::RectangleShape playerBoard;
	sf::Text playerBoardTitle;
	sf::RectangleShape playerBoardDivider;

	//Gameplay
	int currentGo; //Which player is currently playing rotates from 0 - MAX-1 (7)
	std::vector<int> playerPoints;
	sf::Vector2f pointNotiferPos;


	//Cards
	bool waitingForCardToBeHiddenPass = false;
	bool waitingForCardToBeHiddenForfeit = false;
	bool waitingForCardToBeHiddenComplete = false;

	bool wasCardVisible = false;
	bool wasForfeitCardVisible = false;

	//Forfeit card
	std::function<void()> showForfeitDeferredAction;
	ForfeitCard forfeitCardDisplay;
	bool forfeitCardShown;

	//Card
	Card cardDisplay;
	const std::string MOTIF_BASE_LOCATION = "../Data/Assets/Motifs/";
	bool cardShown;
	sf::Color currentCardColour;
	std::function<void()> backToGameDeferredAction;

	GrowFadeText pointNotifier;

	Button spinButton;

	//Spin Wheel
	sf::Texture spinWheelTexture;
	sf::Sprite spinWheelSprite;
	SpinWheel spinner;

	sf::Texture spinWheelClickerTexture;
	sf::Sprite spinwheelClickerSprite;


	//Player Names
	bool playersPopulated;
	int turnsPlayed; //Total amount of turns the game has had
	int lastTurnNo;  //The last turn that was played
	int playerAmt;
	std::vector<std::string> playerNames;
	std::vector<PlayerBoardDisplay> playerDisplay;

	void drawGradientBorder(sf::RenderWindow& window, const sf::FloatRect& rect, float borderThickness, sf::Color color1, sf::Color color2); //Add a gradient border to a shapeRect

};

#endif