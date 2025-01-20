#ifndef GAME_H
#define GAME_H

#pragma once
#include <SFML/Graphics.hpp>
#include "VisualAddons/Confetti.h"
#include "Managers/AudioManager.h"
#include "VisualAddons/SpriteTransition.h"
#include "VisualAddons/GradientText.h"
#include "Utils/Widgets/InputField.h"
#include "Screens/OptionsScreen.h"


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


	private:
		sf::RenderWindow& window;
		AudioManager& audioManager = AudioManager::getInstance();
		sf::Font righteousFont;

		float musicVolume = 0.0f;//75.0f;
		float sfxVolume = 100.0f;


		//Main Menu
		bool in_main_menu;
		bool is_menu_music_playing;
		sf::Sprite logoSprite;
		sf::Texture logoTexture;

		sf::Sprite playButton;
		sf::Texture playTexture;

		sf::Sprite htpButton;
		sf::Texture htpTexture;

		sf::Sprite optionsButton;
		sf::Texture optionsTexture;
		ConfettiManager confettiManager;
		sf::Texture transitionTexture;
		SpriteTransition spinwheelTransition;
		InputField playerNameEntry;

		//Options Screen
		bool in_options;
		OptionsScreen optionsScreen;

		//Player Setup
		bool player_setup;
		GradientText playerSetupTitle;
		sf::Sprite addPlayerButton;
		sf::Texture addPlayerTexture;
		

		//Main Game
		bool in_game;
		


};

#endif