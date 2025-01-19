
#include "Game.h"
#include <iostream>
#include "SpriteTransition.h"

//Add music credit - Zapsplat

Game::Game(sf::RenderWindow& game_window)
	: window(game_window)
{
	srand(time(NULL));
}

Game::~Game()
{

}

void Game::setBackgroundGradient(sf::RenderWindow& window) 
{
	sf::VertexArray background(sf::Quads, 4);

	//Gradient Colours
	sf::Color topColour(42, 3, 60, 255);
	sf::Color btmColour(254, 0, 190, 255);

	for (int i = 0; i < 4; i++) {
		background[0].position = sf::Vector2f(0, 0);
		background[1].position = sf::Vector2f(window.getSize().x, 0);
		background[2].position = sf::Vector2f(window.getSize().x, window.getSize().y);
		background[3].position = sf::Vector2f(0, window.getSize().y);

		float factor = background[i].position.y / window.getSize().y;

		background[i].color = sf::Color(
			static_cast<sf::Uint8>((1.0f - factor) * topColour.r + factor * btmColour.r),
			static_cast<sf::Uint8>((1.0f - factor) * topColour.g + factor * btmColour.g),
			static_cast<sf::Uint8>((1.0f - factor) * topColour.b + factor * btmColour.b)
		);
	}

	window.draw(background);
}

bool Game::init()
{
	//Main Menu
	in_main_menu = true;
	is_menu_music_playing = false;

	//Music
	audioManager.loadMusic("menuMusic", "../Data/Audio/Music/menu_music.mp3");

	//Play Button Sound Effect
	audioManager.loadSoundEffect("playSF", "../Data/Audio/SFX/playButtonClick.wav");

	//Other Click Sound Effect
	audioManager.loadSoundEffect("buttonClick", "../Data/Audio/SFX/menuButtonClick.wav");

	//Logo
	if (!logoTexture.loadFromFile("../Data/gameLogo.png"))
	{
		std::cout << "Logo Did not load";
	}
	logoSprite.setTexture(logoTexture);
	logoSprite.setScale(0.3f, 0.3f);
	logoSprite.setPosition(((window.getSize().x / 2) - (logoSprite.getGlobalBounds().width / 2)), 10);

	//Play Button
	if (!playTexture.loadFromFile("../Data/playButton.png"))
	{
		std::cout << "Play Button Did not load";
	}
	playButton.setTexture(playTexture);
	playButton.setScale(0.6f, 0.6f);
	playButton.setPosition(((window.getSize().x / 2) - (playButton.getGlobalBounds().width / 2)), 450);

	//Options Button
	if (!optionsTexture.loadFromFile("../Data/optionsButton.png"))
	{
		std::cout << "Option Button Did not load";
	}
	optionsButton.setTexture(optionsTexture);
	optionsButton.setScale(0.6f, 0.6f);
	optionsButton.setPosition(((window.getSize().x / 2) - (optionsButton.getGlobalBounds().width/2) - optionsButton.getGlobalBounds().width/2) - 25, 570);

	//HTP Button
	if (!htpTexture.loadFromFile("../Data/htpButton.png"))
	{
		std::cout << "HTP Button Did not load";
	}
	htpButton.setTexture(htpTexture);
	htpButton.setScale(0.6f, 0.6f);
	htpButton.setPosition(((window.getSize().x / 2) - (htpButton.getGlobalBounds().width/2) + htpButton.getGlobalBounds().width/2) + 25, 570);

	spinwheelTransition.init(logoTexture, 0.5f); //Update the texture, 0.5s transition

	//Main Game
	in_game = false;

	return true;
}

void Game::update(float dt)
{
	if (in_main_menu) {
		//In The Main Menu
		if (!is_menu_music_playing) {
			audioManager.playMusic("menuMusic", true);
			audioManager.setMusicVolume(75.0f);
			is_menu_music_playing = true;
		}
		
		confettiManager.update(window);
	}
	
	if(!in_main_menu && in_game)
	{
		spinwheelTransition.update(dt);

		//In Main Game
		if (is_menu_music_playing) {
			audioManager.stopMusic();
			is_menu_music_playing = false;
		}
	}
	
}

void Game::render()
{

	if (in_main_menu) {
		//In THe Main Menu
		setBackgroundGradient(window);
		confettiManager.draw(window);
		window.draw(logoSprite);
		window.draw(playButton);
		window.draw(optionsButton);
		window.draw(htpButton);
	}

	if (!in_main_menu && in_game) 
	{
		spinwheelTransition.render(window);
		if (spinwheelTransition.isComplete()) {
			//Transitioned to the main game
			std::cout << "Main Game Started" << std::endl;
		}
		
	}
	
}

void Game::mouseClicked(sf::Event event)
{
	//get the click position
	sf::Vector2i click = sf::Mouse::getPosition(window);
	sf::Vector2f windowClickPos = window.mapPixelToCoords(click);
	
	if (event.mouseButton.button == sf::Mouse::Left)  //Left Click
	{
		if (playButton.getGlobalBounds().contains(windowClickPos)) {
			//Play Button Clicked
			audioManager.playSoundEffect("playSF");
			std::cout << "Play Button Clicked" << std::endl;
			in_main_menu = false;
			in_game = true;
		}

		if (optionsButton.getGlobalBounds().contains(windowClickPos)) {
			//Options Button Clicked
			audioManager.playSoundEffect("buttonClick");
			std::cout << "Options Button Clicked" << std::endl;
		}

		if (htpButton.getGlobalBounds().contains(windowClickPos)) {
			//HTP Button Clicked
			audioManager.playSoundEffect("buttonClick");
			std::cout << "HTP Button Clicked" << std::endl;
		}

	}


}

void Game::keyPressed(sf::Event event)
{

}