#ifndef GAME_H
#define GAME_H

#pragma once
#include <SFML/Graphics.hpp>
#include "Managers/AudioManager.h"

#include "VisualAddons/Confetti.h"
#include "VisualAddons/SpriteTransition.h"
#include "VisualAddons/GradientText.h"

#include "Utils/Widgets/InputField.h"
#include "Utils/Widgets/Button.h"

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

		//Button
		sf::Color buttonHoverColour = sf::Color(13, 58, 109, 255); //sf::Color(170, 170, 170, 255);
		sf::Color buttonNormalColour = sf::Color::White;

		sf::Texture buttonRectTexture;
		sf::Texture buttonCircleTexture;
		sf::Texture buttonThinRectTexture;

	private:
		sf::RenderWindow& window;
		AudioManager& audioManager = AudioManager::getInstance();
		sf::Font righteousFont;
		sf::Vector2f windowClickPos;

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