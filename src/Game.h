#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include "Confetti.h"
#include "AudioManager.h"


class Game
{
	public:
		Game(sf::RenderWindow& winbdow);
		~Game();

		bool init();
		void update(float dt);
		void render();
		void mouseClicked(sf::Event event);
		void keyPressed(sf::Event event);

		void setBackgroundGradient(sf::RenderWindow& window);


	private:
		sf::RenderWindow& window;
		AudioManager& audioManager = AudioManager::getInstance();


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

		//Main Game
		bool in_game;
		


};

#endif