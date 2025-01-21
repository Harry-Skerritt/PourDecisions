
#include "Game.h"
#include <iostream>
#include "VisualAddons/SpriteTransition.h"
#include "Utils/GradientBackground.h"

//Add music credit - Zapsplat

Game::Game(sf::RenderWindow& game_window)
	: window(game_window), optionsScreen(window, righteousFont),
	playerSetup(window, righteousFont)
{
	optionsScreen.setGameInstance(this);
	playerSetup.setGameInstance(this);
	srand(time(NULL));

}
Game::~Game()
{

}

//Main Game Funcs
bool Game::init()
//Move Buttons to a class which uses a background image and text easier for overlays and handling allowing for cleaner code
{
	settingsParser.loadInSettings("../Data/settings.json");
	resolution = settingsParser.getResolution();
	fullscreen = settingsParser.getFullscreen();
	musicVolume = settingsParser.getMusicVol();
	sfxVolume = settingsParser.getSfxVol();
	nsfwEnabled = settingsParser.getNSFW();
	winPoints = settingsParser.getWinPoints();

	std::cout << "Resolution:" << resolution << std::endl;
	std::cout << "Fullscreen:" << fullscreen << std::endl;
	std::cout << "Music Vol:" << musicVolume << std::endl;
	std::cout << "SFX Vol:" << sfxVolume << std::endl;
	std::cout << "NSFW:" << nsfwEnabled << std::endl;
	std::cout << "Points:" << winPoints << std::endl;

	//Fonts
	if (!righteousFont.loadFromFile("../Data/Fonts/Righteous-Regular.ttf"))
	{
		std::cout << "Righteous Font did not load" << std::endl;
	}

	//Button Backs
	if (!buttonRectTexture.loadFromFile("../Data/Assets/Buttons/rectButtonBack.png"))
	{
		std::cout << "Rect Button Did not load" << std::endl;;
	}

	if (!buttonCircleTexture.loadFromFile("../Data/Assets/Buttons/circleButtonBack.png"))
	{
		std::cout << "Circle Button Did not load" << std::endl;;
	}

	if (!buttonThinRectTexture.loadFromFile("../Data/Assets/Buttons/thinRectButtonBack.png"))
	{
		std::cout << "Thin Rect Button Did not load" << std::endl;;
	}

	//Transition Texture
	if (!transitionTexture.loadFromFile("../Data/Assets/spinwheel.png"))
	{
		std::cout << "Spinwheel Transition did no load" << std::endl;;
	}

	//Player Names
	playerNames.reserve(MAX_PLAYERS); //Reserve space for max number of players

	//Audio Loading
	//Music
	audioManager.loadMusic("menuMusic", "../Data/Audio/Music/menu_music.mp3");

	audioManager.loadMusic("mainMusic", "../Data/Audio/Music/game_music.mp3");

	//SFX
	//Play Button Sound Effect
	audioManager.loadSoundEffect("playSF", "../Data/Audio/SFX/playButtonClick.wav");

	//Other Click Sound Effect
	audioManager.loadSoundEffect("buttonClick", "../Data/Audio/SFX/menuButtonClick.wav");

	//Add Player Sound Effect
	audioManager.loadSoundEffect("addPlayerSF", "../Data/Audio/SFX/addPlayer.wav");

	//Wrong SFX
	audioManager.loadSoundEffect("wrongSF", "../Data/Audio/SFX/wrongAction.wav");

	audioManager.setMusicVolume(musicVolume);

	//Other Vars
	currentPlayers = 0;

	//Main Menu
	in_main_menu = true; //Main Menu State
	is_menu_music_playing = false;

	//Logo
	if (!logoTexture.loadFromFile("../Data/Assets/gameLogo.png"))
	{
		std::cout << "Logo Did not load" << std::endl;;
	}
	logoSprite.setTexture(logoTexture);
	logoSprite.setScale(0.3f, 0.3f);
	logoSprite.setPosition(((window.getSize().x / 2) - (logoSprite.getGlobalBounds().width / 2)), 10);

	//Play Button
	playButton.setBackgroundImage(buttonRectTexture);
	playButton.setBackgroundScale(0.6f, 0.6f);
	playButton.setText("PLAY", righteousFont, 60);
	playButton.setTextColor(buttonNormalColour);
	playButton.setHoverColor(buttonHoverColour);
	playButton.setPosition(((window.getSize().x / 2) - (playButton.getGlobalBounds().width / 2)), 450);

	//Options Button
	optionButton.setBackgroundImage(buttonThinRectTexture);
	optionButton.setBackgroundScale(0.6f, 0.6f);
	optionButton.setText("OPTIONS", righteousFont, 40);
	optionButton.setTextColor(buttonNormalColour);
	optionButton.setHoverColor(buttonHoverColour);
	optionButton.setPosition(((window.getSize().x / 2) - (optionButton.getGlobalBounds().width/2) - optionButton.getGlobalBounds().width/2) - 25, 570);

	//HTP Button
	htpButton.setBackgroundImage(buttonThinRectTexture);
	htpButton.setBackgroundScale(0.6f, 0.6f);
	htpButton.setText("HOW TO PLAY", righteousFont, 40);
	htpButton.setTextColor(buttonNormalColour);
	htpButton.setHoverColor(buttonHoverColour);
	htpButton.setPosition(((window.getSize().x / 2) - (htpButton.getGlobalBounds().width/2) + htpButton.getGlobalBounds().width/2) + 25, 570);

	
	//Transition
	spinwheelTransition.init(transitionTexture, 0.3f); //0.3s transition


	//Options Screen
	in_options = false;
	optionsScreen.initialise(musicVolume, sfxVolume, fullscreen, resolution);
	

	//Player Setup State
	in_player_setup = false;
	playerSetup.initialise();
	
	


	//Main Game
	in_game = false;

	return true;
}

void Game::update(float dt)
{
	//Button Hover Handling
	sf::Vector2i click = sf::Mouse::getPosition(window);
    sf::Vector2f windowClickPos = window.mapPixelToCoords(click);

	if (in_main_menu) {
		//In The Main Menu
		if (!is_menu_music_playing) {
			audioManager.playMusic("menuMusic", true);
			is_menu_music_playing = true;
		}

		playButton.handleHover(windowClickPos);
		optionButton.handleHover(windowClickPos);
		htpButton.handleHover(windowClickPos);
		confettiManager.update(window);
	}

	if(!in_main_menu && in_options)
	{
		//In Options Menu
		optionsScreen.update(dt, windowClickPos);

	}

	if (!in_main_menu && in_player_setup)
	{
		//In Player Setup
		spinwheelTransition.update(dt);
		playerSetup.update(dt, windowClickPos);
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
		//In THe Main Menu - Move to own class soon
		GradientBackground::setBackgroundGradient(window);
		confettiManager.draw(window);
		window.draw(logoSprite);
		playButton.draw(window);
		optionButton.draw(window);
		htpButton.draw(window);
	}

	if (!in_main_menu && in_options)
	{
		//In Options Screen
		optionsScreen.draw(window);
	}

	if (!in_main_menu && in_player_setup)
	{
		//In Player Setup -> Music should keep playing
		spinwheelTransition.render(window);
		if (spinwheelTransition.isComplete()) {
			//Transitioned to player setup
			playerSetup.draw(window, confettiManager);
		}
		
	}

	if (!in_main_menu && in_game) 
	{
		
		
	}
	
}


//Callbacks
void Game::backToMainMenu(int pageID)
{
	std::cout << "Back to main menu" << std::endl;
	if (pageID == 0)
	{
		//Coming from Options
		in_options = false;
		in_main_menu = true;
	}
	//1 - HTP
	else if (pageID == 2)
	{
		//Coming from Setup
		in_player_setup = false;
		in_main_menu = true;
		spinwheelTransition.reset();
	}
	//3 - Main Game

}

//Getters / Setters
float Game::getMusicVolume() {
	return musicVolume;
}

float Game::getSFXVolume() {
	return sfxVolume;
}

int Game::getMaxPlayers() {
	return MAX_PLAYERS;
}

int Game::getPlayerThreshold() {
	return ALLOWED_THRESHOLD;
}

int Game::getCurrentPlayers() {
	return currentPlayers;
}

void Game::setCurrentPlayers(int players) {
	currentPlayers = players;
}


//Player Array
void Game::addPlayer(std::string name) {
	playerNames.push_back(name); //Insert the player name into the last position
}

int Game::getSizeOfPlayerArray() {
	return playerNames.size();
}

//Event Handling

void Game::mouseClicked(sf::Event event)
{
	//get the click position
	sf::Vector2i click = sf::Mouse::getPosition(window);
	sf::Vector2f windowClickPos = window.mapPixelToCoords(click);


	if (event.mouseButton.button == sf::Mouse::Left)  //Left Click
	{
		if (in_main_menu) {
			//Main Menu Buttons
			if (playButton.isClicked(windowClickPos)) {
				//Play Button Clicked
				audioManager.playSoundEffect("playSF");
				std::cout << "Play Button Clicked" << std::endl;
				in_main_menu = false;
				in_player_setup = true; //Go into player setup state
			}

			if (optionButton.isClicked(windowClickPos)) {
				//Options Button Clicked
				audioManager.playSoundEffect("buttonClick");
				std::cout << "Options Button Clicked" << std::endl;
				in_main_menu = false;
				in_options = true; //Move to the options screen
			}

			if (htpButton.isClicked(windowClickPos)) {
				//HTP Button Clicked
				audioManager.playSoundEffect("buttonClick");
				std::cout << "HTP Button Clicked" << std::endl;
			}
		}
		else if (!in_main_menu && in_options)
		{
			//In Options
			optionsScreen.handleMouse(event, windowClickPos);
		}
		else if (in_player_setup) {
			//In Player Setup
			playerSetup.handleMouse(event, windowClickPos);
		}
		

	}


}

void Game::mouseDragged(sf::Event event)
{

}

void Game::textEntered(sf::Event event)
{
	if (in_player_setup)
	{
		//In Player Setup State
		playerSetup.handleTextEntry(event);
	}
}

void Game::keyPressed(sf::Event event)
{

}