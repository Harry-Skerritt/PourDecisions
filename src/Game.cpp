
#include "Game.h"
#include <iostream>
#include <string>
#include "VisualAddons/SpriteTransition.h"
#include "Utils/GradientBackground.h"

//Add music credit - Zapsplat

Game::Game(sf::RenderWindow& game_window)
	: window(game_window), optionsScreen(window, righteousFont),
	playerSetup(window, righteousFont), mainGame(window, righteousFont, ryeFont, lcdFont)
{
	optionsScreen.setGameInstance(this);
	playerSetup.setGameInstance(this);
	mainGame.setGameInstance(this);
	srand(time(NULL));

}
Game::~Game()
{

}

//Main Game Funcs
bool Game::init()
{
	//Disclamer
	if (showDisclamer) {
		
		if (!disclamerTexture.loadFromFile("../Data/Assets/disclamer.png")) {
			std::cout << "Disclamer did not load" << std::endl;
		}

		float disclamerScaleX = static_cast<float>(window.getSize().x) / disclamerTexture.getSize().x;
		float disclamerScaleY = static_cast<float>(window.getSize().y) / disclamerTexture.getSize().y;

		disclamerSprite.setTexture(disclamerTexture);
		disclamerSprite.setScale(disclamerScaleX, disclamerScaleY);
		disclamerSprite.setPosition(0.f, 0.f);

		disclamerAcknowledged = false;

		sf::Color disclamerRed = sf::Color(255, 1, 67);
		sf::Color disclamerWhite = sf::Color::White;

		disclamerButton.setBackgroundColor(disclamerRed, window.getSize().x * 0.25f, window.getSize().y * 0.07f);
		disclamerButton.setBorder(disclamerRed, 2.0f);
		disclamerButton.setText("TEST", ryeFont, window.getSize().y * 0.055f);
		disclamerButton.setTextColor(disclamerWhite);
		disclamerButton.setPosition(window.getSize().x / 2 - disclamerButton.getGlobalBounds().width / 2, window.getSize().y * 0.91f);
	}

	if (!showDisclamer) {
		disclamerAcknowledged = true;
	}

	//Main Game

	scaleX = static_cast<float>(window.getSize().x) / BASE_RESOLUTION.x;
	scaleY = static_cast<float>(window.getSize().y) / BASE_RESOLUTION.y;

	//Load Settings
	loadSettings("../Data/Settings.json");

	//Fonts
	if (!righteousFont.loadFromFile("../Data/Fonts/Righteous-Regular.ttf"))
	{
		std::cout << "Righteous Font did not load" << std::endl;
	}

	if (!ryeFont.loadFromFile("../Data/Fonts/Rye-Regular.ttf"))
	{
		std::cout << "Rye Font did not load" << std::endl;
	}

	if (!lcdFont.loadFromFile("../Data/Fonts/LCD14.otf"))
	{
		std::cout << "LCD Font did not load" << std::endl;
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

	//Transition Textures
	if (!transitionTexture.loadFromFile("../Data/Assets/spinwheel.png"))
	{
		std::cout << "Spinwheel Transition did not load" << std::endl;;
	}

	if (!forfeitTexture.loadFromFile("../Data/Assets/forfeitBadge.png")) 
	{
		std::cout << "Forfeit Transition did not load";
	}

	if (!spinwheel.loadFromFile("../Data/Assets/categorySpinwheel.png"))
	{
		std::cout << "Spinwheel did not load";
	}

	//Player Names
	playerNames.reserve(MAX_PLAYERS); //Reserve space for max number of players

	//Audio Loading
	//Music
	audioManager.loadMusic("menuMusic", "../Data/Audio/Music/menu_music.mp3");

	audioManager.loadMusic("gameMusic", "../Data/Audio/Music/game_music.mp3");

	//SFX
	//Play Button Sound Effect
	audioManager.loadSoundEffect("playSF", "../Data/Audio/SFX/playButtonClick.wav");

	//Other Click Sound Effect
	audioManager.loadSoundEffect("buttonClick", "../Data/Audio/SFX/menuButtonClick.wav");

	//Add Player Sound Effect
	audioManager.loadSoundEffect("addPlayerSF", "../Data/Audio/SFX/addPlayer.wav");

	//Wrong SFX
	audioManager.loadSoundEffect("wrongSF", "../Data/Audio/SFX/wrongAction.wav");

	//Card Select SFX
	audioManager.loadSoundEffect("cardPick", "../Data/Audio/SFX/cardSelect.wav");

	//Forfeit SFX
	audioManager.loadSoundEffect("forfeitRock", "../Data/Audio/SFX/forfeitSound.wav");

	//Point SFX
	audioManager.loadSoundEffect("pointGot", "../Data/Audio/SFX/pointSFX.wav");


	audioManager.setMusicVolume(musicVolume);

	//Other Vars
	currentPlayers = 0;

	//Main Menu
	in_main_menu = !showDisclamer; //Main Menu State
	is_menu_music_playing = false;

	//Logo
	if (!logoTexture.loadFromFile("../Data/Assets/gameLogo.png"))
	{
		std::cout << "Logo Did not load" << std::endl;;
	}
	logoSprite.setTexture(logoTexture);

	

	logoSprite.setScale(scaleX * 0.3f, scaleX * 0.3f);
	logoSprite.setPosition(((window.getSize().x / 2) - (logoSprite.getGlobalBounds().width / 2)), 10);

	//Play Button
	playButton.setBackgroundImage(buttonRectTexture);
	playButton.setBackgroundScale(0.6f, 0.6f);
	playButton.setText("PLAY", righteousFont, 60);
	playButton.setTextColor(buttonNormalColour);
	playButton.setHoverColor(buttonHoverColour);
	playButton.setPosition(((window.getSize().x / 2) - (playButton.getGlobalBounds().width / 2)), window.getSize().y - 270);

	//Options Button
	optionButton.setBackgroundImage(buttonThinRectTexture);
	optionButton.setBackgroundScale(0.6f, 0.6f);
	optionButton.setText("OPTIONS", righteousFont, 40);
	optionButton.setTextColor(buttonNormalColour);
	optionButton.setHoverColor(buttonHoverColour);
	optionButton.setPosition(((window.getSize().x / 2) - (optionButton.getGlobalBounds().width/2) - optionButton.getGlobalBounds().width/2) - 25, window.getSize().y - 150);

	//HTP Button
	htpButton.setBackgroundImage(buttonThinRectTexture);
	htpButton.setBackgroundScale(0.6f, 0.6f);
	htpButton.setText("HOW TO PLAY", righteousFont, 40);
	htpButton.setTextColor(buttonNormalColour);
	htpButton.setHoverColor(buttonHoverColour);
	htpButton.setPosition(((window.getSize().x / 2) - (htpButton.getGlobalBounds().width/2) + htpButton.getGlobalBounds().width/2) + 25, window.getSize().y - 150);

	//Quit Button
	quitButton.setBackgroundImage(buttonCircleTexture);
	quitButton.setBackgroundScale(scaleX * 0.4f, scaleX * 0.4f);
	quitButton.setText("X", righteousFont, window.getSize().y * 0.0416f);
	quitButton.setTextColor(buttonNormalColour);
	quitButton.setHoverColor(buttonHoverColour);
	quitButton.setPosition(window.getSize().x - quitButton.getGlobalBounds().width - 25, 25);

	
	//Transition
	spinwheelTransition.init(transitionTexture, 0.3f, window); //0.3s transition
	forfeitRock.init(forfeitTexture, window);

	spinwheel_wheel.init(spinwheel, sf::Vector2f((window.getSize().x / 2), (window.getSize().y / 2)), 200.0f);
	

	//Options Screen
	in_options = false;
	optionsScreen.initialise(musicVolume, sfxVolume, fullscreen, resolution);
	

	//Player Setup State
	in_player_setup = false;
	playerSetup.initialise();
	
	


	//Main Game
	in_game = false;
	is_game_music_playing = false;
	mainGame.init();

	//Test Card
	sf::Color colourTest = sf::Color(0, 168, 64);
	std::string textTest = "What's the most embarrassing thing you've ever done?";
	std::cout << "PC SX: " << scaleX << std::endl;
	cardTest.initialise(colourTest, righteousFont, ryeFont, "TRUTH", textTest, "../Data/Assets/Motifs/truthMotif.png", scaleX, window);
	

	return true;
}

void Game::update(float dt)
{
	//Button Hover Handling
	sf::Vector2i click = sf::Mouse::getPosition(window);
    sf::Vector2f windowClickPos = window.mapPixelToCoords(click);

	cardTest.update(dt, windowClickPos);

	if (!disclamerAcknowledged) {
		disclamerButton.handleHover(windowClickPos);
	}

	if (in_main_menu && disclamerAcknowledged) {
		//In The Main Menu
		if (!is_menu_music_playing) {
			audioManager.playMusic("menuMusic", true);
			is_menu_music_playing = true;
		}

		playButton.handleHover(windowClickPos);
		optionButton.handleHover(windowClickPos);
		htpButton.handleHover(windowClickPos);
		quitButton.handleHover(windowClickPos);
		confettiManager.update(window);

		forfeitRock.update(dt);
		spinwheel_wheel.update(dt);
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

		//Change music
		if (is_menu_music_playing) {
			audioManager.stopMusic();
			is_menu_music_playing = false;
			if (!is_game_music_playing) {
				audioManager.playMusic("gameMusic", true);
				is_game_music_playing = true;
			}
		}

		mainGame.update(dt, windowClickPos);
	}
	
}

void Game::render(float dt)
{
	if (!disclamerAcknowledged) {
		window.draw(disclamerSprite);
		disclamerButton.draw(window);
	}

	if (in_main_menu && disclamerAcknowledged) {
		//In THe Main Menu - Move to own class soon
		GradientBackground::setBackgroundGradient(window);
		confettiManager.draw(window);
		window.draw(logoSprite);
		playButton.draw(window);
		optionButton.draw(window);
		htpButton.draw(window);
		quitButton.draw(window);

		forfeitRock.draw(window);
		//spinwheel_wheel.draw(window);

		if (showCard) {
			cardTest.showCard(window, dt);
			
		}
		else {
			cardTest.hideCard(window, dt);
			audioManager.playSoundEffect("cardPick");
		}
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
		mainGame.draw(window);
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
	else if (pageID == 3)
	{
		//Coming from game
		in_game = false;
		in_main_menu = true;
		playerSetup.reset();
	}
	

}

void Game::transitionToMainGame() {
	if (in_player_setup) {
		in_player_setup = false;
		in_game = true;
		mainGame.populatePlayers(playerNames);
	}
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

// Settings
bool Game::loadSettings(std::string fileLoc) {
	try {
		//Parse JSON
		Settings settings = Settings::fromFile(fileLoc);

		//Print the values
		std::cout << "Resolution: " << settings.getResolution() << "\n";
		std::cout << "Fullscreen: " << settings.getFullscreen() << "\n";
		std::cout << "Music Volume: " << settings.getMusicVolume() << "\n";
		std::cout << "SFX Volume: " << settings.getSFXVolume() << "\n";
		std::cout << "NSFW Enabled: " << settings.getNSFWEnabled() << "\n";
		std::cout << "Win Points: " << settings.getWinPoints() << "\n";

		//Get the values
		resolution = settings.getResolution();
		fullscreen = settings.getFullscreen();
		musicVolume = settings.getMusicVolume();
		sfxVolume = settings.getSFXVolume();
		nsfwEnabled = settings.getNSFWEnabled();
		winPoints = settings.getWinPoints();

	}
	catch (const std::exception& ex) {
		std::cerr << "Error parsing Settings JSON: " << ex.what() << "\n";
		return 1;
	}

	return 0;
}

//Event Handling

void Game::mouseClicked(sf::Event event)
{
	//get the click position
	sf::Vector2i click = sf::Mouse::getPosition(window);
	sf::Vector2f windowClickPos = window.mapPixelToCoords(click);

	if (event.mouseButton.button == sf::Mouse::Left)  //Left Click
	{
		if (!disclamerAcknowledged) {
			if (disclamerButton.isClicked(windowClickPos)) {
				audioManager.playSoundEffect("buttonClick");
				disclamerAcknowledged = true;
				in_main_menu = true;
			}
		}
		if (in_main_menu && disclamerAcknowledged) {
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

			if (quitButton.isClicked(windowClickPos)) {
				window.close();
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
		else if (!in_player_setup && in_game) {
			mainGame.handleMouse(event, windowClickPos);
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
	if (in_player_setup) {
		if (event.key.code == sf::Keyboard::Enter) {
			playerSetup.handleEnter(event);
		}
	}

	if (in_game) {
		mainGame.handleKeypress(event);
	}

	/*
	if (event.key.code == sf::Keyboard::C) {
		showCard = !showCard;
	}
	
	if (event.key.code == sf::Keyboard::R) {
		audioManager.playSoundEffect("forfeitRock");
		forfeitRock.startRocking();
	}

	if (event.key.code == sf::Keyboard::Space) {
		spinwheel_wheel.spin();
	}
	*/
}

bool Game::isRestartRequired() const {
	return optionsScreen.isRestartRequested();
}

void Game::getUpdatedSettings(bool& fullscreen, sf::VideoMode& resolution) {
	fullscreen = optionsScreen.fullscreenCheckbox.isChecked();
	std::string res = optionsScreen.resolutionMenu.getSelectedItem();
	int width, height;
	optionsScreen.splitResolution(res, width, height);
	resolution = sf::VideoMode(width, height);
}

