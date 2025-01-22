#ifndef GAME_H
#define GAME_H

#pragma once
#include <SFML/Graphics.hpp>
#include "Managers/AudioManager.h"

#include "VisualAddons/Confetti.h"
#include "VisualAddons/SpriteTransition.h"

#include "Utils/Widgets/InputField.h"
#include "Utils/Widgets/Button.h"
#include "Utils/GradientText.h"

#include "Screens/OptionsScreen.h"
#include "Screens/PlayerSetup.h"

//Settings
#include <iostream>
#include <fstream>
#include <sstream>
#include "Utils/JSON/Settings.h"

#include "GameObjects/Card.h" //Test

class Game
{
	public:
		Game(sf::RenderWindow& window);
		~Game();

		bool init();
		void update(float dt);
		void render();
		void mouseClicked(sf::Event event);
		void keyPressed(sf::Event event);
		void textEntered(sf::Event event);
		void mouseDragged(sf::Event event);

		void backToMainMenu(int pageID); //0 - Options, 1 - HTP, 2 - Game

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

	private:
		//Settings from file
		bool loadSettings(std::string fileLoc);;

		//Screen
		const sf::Vector2f BASE_RESOLUTION = sf::Vector2f(1080.0f, 720.0f);

		Card cardTest; //Test

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


		//Players & Points
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
		sf::Texture transitionTexture;
		SpriteTransition spinwheelTransition;

		//Options Screen
		bool in_options;
		OptionsScreen optionsScreen;

		//Player Setup
		bool in_player_setup;
		PlayerSetup playerSetup;
		

		//Main Game
		bool in_game;
		


};

#endif