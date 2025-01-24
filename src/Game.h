#ifndef GAME_H
#define GAME_H

#pragma once
#include <SFML/Graphics.hpp>
#include "Managers/AudioManager.h"

#include "VisualAddons/Confetti.h"
#include "VisualAddons/SpriteTransition.h"
#include "VisualAddons/RockingSprite.h"
#include "VisualAddons/SpinWheel.h"

#include "Utils/Widgets/InputField.h"
#include "Utils/Widgets/Button.h"
#include "Utils/GradientText.h"
#include "Utils/Widgets/SolidButton.h"

#include "Screens/OptionsScreen.h"
#include "Screens/PlayerSetup.h"
#include "Screens/MainGame.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include "Utils/JSON/Settings.h"
#include "Utils/JSON/CardImporter.h"

class Game
{
	public:
		Game(sf::RenderWindow& window);
		~Game();

		bool init();
		void update(float dt);
		void render(float dt);
		void mouseClicked(sf::Event event);
		void keyPressed(sf::Event event);
		void textEntered(sf::Event event);
		void mouseDragged(sf::Event event);

		void backToMainMenu(int pageID); //0 - Options, 1 - HTP, 2 - Setup, 3 - Game
		void transitionToMainGame();

		float getMusicVolume();
		float getSFXVolume();

		int getMaxPlayers();
		int getPlayerThreshold();
		int getCurrentPlayers();
		void setCurrentPlayers(int players);

		void addPlayer(std::string name);
		int getSizeOfPlayerArray();

		//Button
		sf::Color buttonHoverColour = sf::Color(13, 58, 109, 255); //sf::Color(170, 170, 170, 255);
		sf::Color buttonNormalColour = sf::Color::White;

		sf::Texture buttonRectTexture;
		sf::Texture buttonCircleTexture;
		sf::Texture buttonThinRectTexture;

		float scaleX;
		float scaleY;

		//Screen
		bool isRestartRequired() const;
		void getUpdatedSettings(bool& fullscreen, sf::VideoMode& resolution);

		//Cards
		const int MAX_CATEGORIES = 8; //Maximum amount of allowed categories
		const int DEFAULT_CATEGORIES_AMOUNT = 7; //Amount of default categories present
		int amountOfCustomCards;
		bool usingCustomCards = false; //Set to true in Options Screen - need to create dir
		int categoriesLoaded;

		std::vector<std::string> cardCategories;			 //Stores the names of the categories
		std::vector<sf::Color> cardColours;					 //Stores the colours of each category
		std::vector<int> cardQuantity;						 //Stores the amount of cards in each category
		std::vector<std::vector<std::string>> cardQuestions; //Stores the questions for each category
		std::vector<std::vector<int>> usedCards;			 //Stores the cards which have been played
		std::vector<std::string> motifLoc;					 //Stores the file location of the motif for each card 

		std::vector<int> usedCustomCards;

		bool checkAllCardsUsed();
		int maxNumberOfCards;
		void resetUsedCards();

		CardImporter cardImporter;

	private:
		//Disclamer
		bool showDisclamer = false;
		bool disclamerAcknowledged;
		sf::Texture disclamerTexture;
		sf::Sprite disclamerSprite;
		SolidButton disclamerButton;

		//Settings from file
		bool loadSettings(std::string fileLoc);;

		//Screen
		const sf::Vector2f BASE_RESOLUTION = sf::Vector2f(1080.0f, 720.0f);


		//Graphics
		std::string resolution;
		bool fullscreen;

		//Audio 
		float musicVolume;
		float sfxVolume;

		//Game Stuff
		bool nsfwEnabled;
		int winPoints;

		
		//Main
		sf::RenderWindow& window;
		AudioManager& audioManager = AudioManager::getInstance();
		sf::Font righteousFont;
		sf::Font ryeFont;
		sf::Font lcdFont;


		//Players & Points - Gameplay
		const int MAX_PLAYERS = 8;
		int currentPlayers;
		const int ALLOWED_THRESHOLD = 1; //3
		
		std::vector<std::string> playerNames;
		std::vector<int> playerPoints;

	
		//Main Menu
		bool in_main_menu;
		bool is_menu_music_playing;
		sf::Sprite logoSprite;
		sf::Texture logoTexture;

		Button playButton;
		Button optionButton;
		Button htpButton;

		Button quitButton;

		ConfettiManager confettiManager;

		//Transitions
		sf::Texture transitionTexture;
		SpriteTransition spinwheelTransition;

		sf::Texture forfeitTexture;
		RockingSprite forfeitRock;

		sf::Texture spinwheel;
		SpinWheel spinwheel_wheel;


		//Options Screen
		bool in_options;
		OptionsScreen optionsScreen;

		//Player Setup
		bool in_player_setup;
		PlayerSetup playerSetup;
		

		//Main Game
		bool in_game;
		bool is_game_music_playing;
		MainGame mainGame;
		


};

#endif