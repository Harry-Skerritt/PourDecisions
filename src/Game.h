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

	private:
		//Window Options
		//Need to be set properly somewhere
		bool fullscreen = false;
		std::string resolution = "1080x720"; 

		
		sf::RenderWindow& window;
		AudioManager& audioManager = AudioManager::getInstance();
		sf::Font righteousFont;

		const int MAX_PLAYERS = 8;
		int currentPlayers;
		const int ALLOWED_THRESHOLD = 3;
		std::vector<std::string> playerNames;


		float musicVolume = 0.0f;//75.0f;
		float sfxVolume = 100.0f;

	
		//Main Menu
		bool in_main_menu;
		bool is_menu_music_playing;
		sf::Sprite logoSprite;
		sf::Texture logoTexture;

		Button playButton;
		Button optionButton;
		Button htpButton;

		
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