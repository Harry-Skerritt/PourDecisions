
#include "Game.h"
#include <iostream>
#include "VisualAddons/SpriteTransition.h"
#include "Utils/GradientBackground.h"

//Add music credit - Zapsplat

Game::Game(sf::RenderWindow& game_window)
	: window(game_window), optionsScreen(window, righteousFont)
{
	optionsScreen.setGameInstance(this);
	srand(time(NULL));

}

Game::~Game()
{

}
bool Game::init()
//Move Buttons to a class which uses a background image and text easier for overlays and handling allowing for cleaner code
{
	//Fonts
	if (!righteousFont.loadFromFile("../Data/Fonts/Righteous-Regular.ttf"))
	{
		std::cout << "Righteous Font did not load" << std::endl;
	}

	//Main Menu
	in_main_menu = true; //Main Menu State
	is_menu_music_playing = false;

	//Music
	audioManager.loadMusic("menuMusic", "../Data/Audio/Music/menu_music.mp3");

	//Play Button Sound Effect
	audioManager.loadSoundEffect("playSF", "../Data/Audio/SFX/playButtonClick.wav");

	//Other Click Sound Effect
	audioManager.loadSoundEffect("buttonClick", "../Data/Audio/SFX/menuButtonClick.wav");

	//Add Player Sound Effect
	audioManager.loadSoundEffect("addPlayerSF", "../Data/Audio/SFX/addPlayer.wav");

	//Wrong SFX
	audioManager.loadSoundEffect("wrongSF", "../Data/Audio/SFX/wrongAction.wav");

	//Logo
	if (!logoTexture.loadFromFile("../Data/Assets/gameLogo.png"))
	{
		std::cout << "Logo Did not load" << std::endl;;
	}
	logoSprite.setTexture(logoTexture);
	logoSprite.setScale(0.3f, 0.3f);
	logoSprite.setPosition(((window.getSize().x / 2) - (logoSprite.getGlobalBounds().width / 2)), 10);

	//Play Button
	if (!playTexture.loadFromFile("../Data/Assets/Buttons/playButton.png"))
	{
		std::cout << "Play Button Did not load" << std::endl;;
	}
	playButton.setTexture(playTexture);
	playButton.setScale(0.6f, 0.6f);
	playButton.setPosition(((window.getSize().x / 2) - (playButton.getGlobalBounds().width / 2)), 450);

	//Options Button
	if (!optionsTexture.loadFromFile("../Data/Assets/Buttons/optionsButton.png"))
	{
		std::cout << "Option Button Did not load" << std::endl;;
	}
	optionsButton.setTexture(optionsTexture);
	optionsButton.setScale(0.6f, 0.6f);
	optionsButton.setPosition(((window.getSize().x / 2) - (optionsButton.getGlobalBounds().width/2) - optionsButton.getGlobalBounds().width/2) - 25, 570);

	//HTP Button
	if (!htpTexture.loadFromFile("../Data/Assets/Buttons/htpButton.png"))
	{
		std::cout << "HTP Button Did not load" << std::endl;;
	}
	htpButton.setTexture(htpTexture);
	htpButton.setScale(0.6f, 0.6f);
	htpButton.setPosition(((window.getSize().x / 2) - (htpButton.getGlobalBounds().width/2) + htpButton.getGlobalBounds().width/2) + 25, 570);


	if (!transitionTexture.loadFromFile("../Data/Assets/spinwheel.png"))
	{
		std::cout << "Spinwheel Transition did no load" << std::endl;;
	}
	spinwheelTransition.init(transitionTexture, 0.3f); //Update the texture, 0.3s transition

	//Options Screen
	in_options = false;
	optionsScreen.initialise(musicVolume, sfxVolume);
	

	//Player Setup State
	player_setup = false; 

	//Title
	playerSetupTitle.setFont(righteousFont);
	playerSetupTitle.setString("PLAYER SETUP");
	playerSetupTitle.setCharacterSize(80);
	playerSetupTitle.setGradientColors(sf::Color(251, 0, 188, 255), sf::Color(0, 238, 255, 255));
	playerSetupTitle.setPosition(((window.getSize().x / 2) - (playerSetupTitle.getGlobalBounds().width / 2)), 60);


	//Text Entry
	playerNameEntry.setFont(righteousFont);
	playerNameEntry.setSize(400, 60);
	playerNameEntry.setBackgroundColour(sf::Color(66, 66, 66, 255));
	playerNameEntry.setPlaceholder("Enter Player Name");
	playerNameEntry.setPosition(((window.getSize().x / 2) - (playerNameEntry.getGlobalBounds().width / 2)), 150);
	playerNameEntry.setBorder(4.0f, sf::Color::Black);

	//Add Player Button
	if (!addPlayerTexture.loadFromFile("../Data/Assets/Buttons/addPlayerButton.png")) {
		std::cout << "Add Player Texture did not load" << std::endl;
	}
	addPlayerButton.setTexture(addPlayerTexture);
	addPlayerButton.setScale(0.6f, 0.6f);
	addPlayerButton.setPosition(playerNameEntry.getPosition().x + playerNameEntry.getGlobalBounds().width + 20, 150);
	
	audioManager.setMusicVolume(musicVolume);


	//Main Game
	in_game = false;

	return true;
}

void Game::update(float dt)
{
	//Set Volume
	//audioManager.setMusicVolume(musicVolume); //75.0 Default
	//audioManager.setSoundEffectVolume(sfxVolume); -> Make this a global function

	if (in_main_menu) {
		//In The Main Menu
		if (!is_menu_music_playing) {
			audioManager.playMusic("menuMusic", true);
			is_menu_music_playing = true;
		}
		
		confettiManager.update(window);
	}

	if(!in_main_menu && in_options)
	{
		//In Options Menu

	}

	if (!in_main_menu && player_setup)
	{
		//In Player Setup
		spinwheelTransition.update(dt);
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
		GradientBackground::setBackgroundGradient(window);
		confettiManager.draw(window);
		window.draw(logoSprite);
		window.draw(playButton);
		window.draw(optionsButton);
		window.draw(htpButton);
	}

	if (!in_main_menu && in_options)
	{
		//In Options Screen
		optionsScreen.draw(window);
	}

	if (!in_main_menu && player_setup)
	{
		//In Player Setup -> Music should keep playing
		spinwheelTransition.render(window);
		if (spinwheelTransition.isComplete()) {
			//Transitioned to player setup
			GradientBackground::setBackgroundGradient(window);
			confettiManager.draw(window);
			window.draw(playerSetupTitle);
			playerNameEntry.draw(window);
			window.draw(addPlayerButton);
		}
		
	}

	if (!in_main_menu && in_game) 
	{
		
		
	}
	
}

void Game::backToMainMenu(int pageID)
{
	std::cout << "Back to main menu" << std::endl;
	if (pageID == 0)
	{
		//Coming from Options
		in_options = false;
		in_main_menu = true;
	}//1 - HTP
	//2 - Main Game

}

float Game::getMusicVolume() {
	return musicVolume;
}

float Game::getSFXVolume() {
	return sfxVolume;
}

void Game::mouseClicked(sf::Event event)
{
	//get the click position
	sf::Vector2i click = sf::Mouse::getPosition(window);
	sf::Vector2f windowClickPos = window.mapPixelToCoords(click);


	if (event.mouseButton.button == sf::Mouse::Left)  //Left Click
	{
		if (in_main_menu) {
			//Main Menu Buttons
			if (playButton.getGlobalBounds().contains(windowClickPos)) {
				//Play Button Clicked
				audioManager.playSoundEffect("playSF");
				std::cout << "Play Button Clicked" << std::endl;
				in_main_menu = false;
				player_setup = true; //Go into player setup state
			}

			if (optionsButton.getGlobalBounds().contains(windowClickPos)) {
				//Options Button Clicked
				audioManager.playSoundEffect("buttonClick");
				std::cout << "Options Button Clicked" << std::endl;
				in_main_menu = false;
				in_options = true; //Move to the options screen
			}

			if (htpButton.getGlobalBounds().contains(windowClickPos)) {
				//HTP Button Clicked
				audioManager.playSoundEffect("buttonClick");
				std::cout << "HTP Button Clicked" << std::endl;
			}
		}
		else if (!in_main_menu && in_options)
		{
			//In Options
			optionsScreen.handleMouse(event);
		}
		else if (player_setup) {
			//In Player Setup
			if (addPlayerButton.getGlobalBounds().contains(windowClickPos)) {
				if (playerNameEntry.isEmpty()) {
					audioManager.playSoundEffect("wrongSF");
				}
				else {
					audioManager.playSoundEffect("addPlayerSF");
				}
				
				std::cout << "Add Player Clicked" << std::endl;
				//Handle adding the player
				playerNameEntry.resetField(); //Reset for next name
			}
		}
		

	}


}

void Game::mouseDragged(sf::Event event)
{

}

void Game::textEntered(sf::Event event)
{
	if (player_setup)
	{
		//In Player Setup State
		playerNameEntry.handleInput(event);
	}
}

void Game::keyPressed(sf::Event event)
{

}