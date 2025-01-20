
#include "Game.h"
#include <iostream>
#include "VisualAddons/SpriteTransition.h"

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

	//Player Setup State
	player_setup = false; 

	//Title
	playerSetupTitle.setFont(righteousFont);
	playerSetupTitle.setString("PLAYER SETUP");
	playerSetupTitle.setCharacterSize(80);
	playerSetupTitle.setGradientColors(sf::Color(251, 0, 188, 255), sf::Color(0, 238, 255, 255));

	sf::FloatRect localBounds = playerSetupTitle.getLocalBounds();
	playerSetupTitle.setOrigin(localBounds.width / 2, localBounds.height / 2);
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
			audioManager.setMusicVolume(0.0f); //75.0 Default
			is_menu_music_playing = true;
		}
		
		confettiManager.update(window);
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
		setBackgroundGradient(window);
		confettiManager.draw(window);
		window.draw(logoSprite);
		window.draw(playButton);
		window.draw(optionsButton);
		window.draw(htpButton);
	}

	if (!in_main_menu && player_setup)
	{
		//In Player Setup -> Music should keep playing
		spinwheelTransition.render(window);
		if (spinwheelTransition.isComplete()) {
			//Transitioned to player setup
			//Fix the delay with black screen - Done?
			
			setBackgroundGradient(window);
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
			}

			if (htpButton.getGlobalBounds().contains(windowClickPos)) {
				//HTP Button Clicked
				audioManager.playSoundEffect("buttonClick");
				std::cout << "HTP Button Clicked" << std::endl;
			}
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