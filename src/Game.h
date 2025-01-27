#ifndef GAME_H
#define GAME_H

#pragma once
#include <SFML/Graphics.hpp>
#include "Managers/AudioManager.h"

#include "VisualAddons/Confetti.h"
#include "VisualAddons/SpriteTransition.h"
#include "VisualAddons/SpinWheel.h"

#include "Utils/Widgets/InputField.h"
#include "Utils/Widgets/Button.h"
#include "Utils/GradientText.h"
#include "Utils/Widgets/SolidButton.h"

#include "Screens/OptionsScreen.h"
#include "Screens/PlayerSetup.h"
#include "Screens/MainGame.h"
#include "Screens/HTPScreen.h"

#include <iostream>
#include <fstream>
#include <sstream>

#include "Utils/JSON/Settings.h"
#include "Utils/JSON/CardImporter.h"
#include "Utils/JSON/ForfeitImporter.h"

class Game
{
	public:
		Game(sf::RenderWindow& window, int fps);
		~Game();

		bool init();
		void update(float dt);
		void render(float dt);
		void mouseClicked(sf::Event event);
		void keyPressed(sf::Event event);
		void textEntered(sf::Event event);
		void mouseDragged(sf::Event event);

		void backToMainMenu(int pageID); //0 - Options, 1 - HTP, 2 - Setup, 3 - Game
		void toOptions(int pageID); //3 - Game
		void transitionToMainGame();
		void transitionToSetup(int pageID); //0 - Menu, 3 - Game

		float getMusicVolume();
		float getSFXVolume();

		int getMaxPlayers();
		int getPlayerThreshold();
		int getCurrentPlayers();
		void setCurrentPlayers(int players);
		void clearPlayerArray();

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
		int framesPerSecond;
		
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

		//Forfeits
		const int DEFAULT_FORFEITS_AMOUNT = 15; //Amount of defalut forfeits
		const std::string FORFEIT_MOTIF_LOC = "../Data/Assets/Motifs/Forfeits/";

		std::vector<std::string> forfeitMotifNames;		//Stores the names of the motif files
		std::vector<std::string> forfeitTitles;			//Stores the titles for the forfeit card
		std::vector<std::string> forfeitCards;			//Stores the card value for the forfeit card
		std::vector<int> forfeitTimers;					//Stores the duration for the timers on forefeit cards
		int forfeitQuantity;							//Amount of forfeits
		std::vector<int> usedForfeits;					//Tracks the used forfeits
		ForfeitImporter forfeitImporter;

		sf::Texture forfeitTexture;

		//Game Stuff
		bool nsfwEnabled;
		int winPoints;

	

		//Loading Funcs
		bool loadFonts();
		bool loadAssets();
		bool loadAudio();
		bool loadCards();
		bool loadForfeits();
		bool loadSettings(std::string fileLoc);;


	private:
		//Disclamer
		bool showDisclamer = true; //Should be true before release
		bool disclamerAcknowledged;
		sf::Texture disclamerTexture;
		sf::Sprite disclamerSprite;
		SolidButton disclamerButton;

		//Screen
		const sf::Vector2f BASE_RESOLUTION = sf::Vector2f(1080.0f, 720.0f);
		const std::string CREDIT_URL = "https://harry-skerritt.github.io/PourDecisions/";

		//Graphics
		std::string resolution;
		bool fullscreen;

		//Audio 
		float musicVolume;
		float sfxVolume;

		
		//Main
		sf::RenderWindow& window;
		AudioManager& audioManager = AudioManager::getInstance();
		sf::Font righteousFont;
		sf::Font ryeFont;
		sf::Font lcdFont;


		//Players & Points - Gameplay
		const int MAX_PLAYERS = 8;
		int currentPlayers;
		const int ALLOWED_THRESHOLD = 3;
		
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

		
		
		//How To Play Screen
		bool in_how_to_play;
		HowToPlayScreen htpScreen;

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