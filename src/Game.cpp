
#include "Game.h"
#include <iostream>
#include <string>
#include <algorithm>
#include "VisualAddons/SpriteTransition.h"
#include "Utils/GradientBackground.h"
#include "Utils/CustomMessageBox.h"



Game::Game(sf::RenderWindow& game_window, int fps)
	: window(game_window), framesPerSecond(fps),
	optionsScreen(window, righteousFont),
	htpScreen(window, righteousFont, ryeFont),
	playerSetup(window, righteousFont),
	mainGame(window, righteousFont, ryeFont, lcdFont)
{
	optionsScreen.setGameInstance(this);
	htpScreen.setGameInstance(this);
	playerSetup.setGameInstance(this);
	mainGame.setGameInstance(this);
	srand(time(NULL));

}
Game::~Game()
{

}

//Loading Funcs

bool Game::loadFonts() {
	std::cout << "Loading Fonts..." << std::endl;
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
	return true;
}

bool Game::loadAssets() {
	std::cout << "Loading Assets..." << std::endl;
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

	//Logo
	if (!logoTexture.loadFromFile("../Data/Assets/gameLogo.png"))
	{
		std::cout << "Logo Did not load" << std::endl;;
	}
	logoSprite.setTexture(logoTexture);
	return true;
}

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
		return false;
	}

	return true;
}

bool Game::loadAudio() {
	std::cout << "Loading Audio..." << std::endl;

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

	//Wheel Click
	audioManager.loadSoundEffect("wheelClick", "../Data/Audio/SFX/wheelClick.wav");

	return true;
}

bool Game::loadCards() {
	std::cout << "Loading Cards..." << std::endl;

	//Import cards
//Initialise all vectors - reserve enough room for all vectors to hold their max info
	categoriesLoaded = 0;

	bool failedCardImport = false;

	cardImporter.initialise(DEFAULT_CATEGORIES_AMOUNT, usingCustomCards, MAX_CATEGORIES);
	std::string cardFolder = "../Cards/";
	if (cardImporter.setCardDir(cardFolder)) {
		//Directory is formatted correctly
		if (cardImporter.importCards(nsfwEnabled)) {

			//Everything imported
			if (usingCustomCards) {
				cardCategories.resize(MAX_CATEGORIES);
				cardColours.resize(MAX_CATEGORIES);
				cardQuantity.resize(MAX_CATEGORIES);
				cardQuestions.resize(MAX_CATEGORIES);
				motifLoc.resize(MAX_CATEGORIES);
				usedCards = std::vector<std::vector<int>>(DEFAULT_CATEGORIES_AMOUNT);
				//usedCustomCards; //Set to be the length of the amount of custom cards

			}
			else {
				cardCategories.resize(DEFAULT_CATEGORIES_AMOUNT);
				cardColours.resize(DEFAULT_CATEGORIES_AMOUNT);
				cardQuantity.resize(DEFAULT_CATEGORIES_AMOUNT);
				cardQuestions.resize(DEFAULT_CATEGORIES_AMOUNT);
				motifLoc.resize(DEFAULT_CATEGORIES_AMOUNT);
				usedCards = std::vector<std::vector<int>>(DEFAULT_CATEGORIES_AMOUNT);

			}

			cardCategories = cardImporter.getCardCategories();
			cardColours = cardImporter.getCardColours();
			cardQuantity = cardImporter.getCardQuantity();
			cardQuestions = cardImporter.getCardQuestions();
			motifLoc = cardImporter.getMotifLoc();
		}
		else {
			failedCardImport = true;
		}

	}
	else {
		std::cout << "Card Directory is incorrectly formatted" << std::endl;
		failedCardImport = true;
	}

	if (failedCardImport) {
		CustomMessageBox failedCard("Pour Decisions", "Cards could not be imported", 2, window);
		MessageBoxButton result = failedCard.showMessageBox(); //Show the message box

		if (result == MessageBoxButton::Ok) {
			std::cout << "OK button clicked" << std::endl;
			window.close();
		}
		else if (result == MessageBoxButton::Cancel) {
			std::cout << "Cancel button clicked" << std::endl;
			window.close();
		}
	}
	return !failedCardImport;
}

bool Game::loadForfeits() {
	std::cout << "Loading Forfeits..." << std::endl;
	bool failedForfeitImport = false;
	forfeitImporter.initialise(DEFAULT_FORFEITS_AMOUNT);
	std::string forfeitFileLoc = "../Cards/forfeits.json";

	if (forfeitImporter.setForfeitDir(forfeitFileLoc)) {
		if (forfeitImporter.importForfeits()) {
			forfeitQuantity = forfeitImporter.getForfeitQuantity();

			// Print data before proceeding
			std::cout << "Forfeit Quantity: " << forfeitQuantity << std::endl;
			auto motifNames = forfeitImporter.getMotifNames();
			auto titles = forfeitImporter.getForfeitTitles();
			auto cards = forfeitImporter.getForfeitCards();
			auto timers = forfeitImporter.getForfeitTimers();

			std::cout << "Motif Names Size: " << motifNames.size() << std::endl;
			std::cout << "Titles Size: " << titles.size() << std::endl;
			std::cout << "Cards Size: " << cards.size() << std::endl;
			std::cout << "Timers Size: " << timers.size() << std::endl;

			// Calculate the valid size (smallest size among vectors)
			size_t validSize = std::min(
				std::min(std::min(motifNames.size(), titles.size()),
					std::min(cards.size(), timers.size())),
				static_cast<size_t>(forfeitQuantity)
			);

			// Debugging the valid size
			std::cout << "Valid Size: " << validSize << std::endl;

			// Check if validSize is greater than 0 and resize the vectors accordingly
			if (validSize > 0) {
				forfeitMotifNames.resize(validSize);
				forfeitTitles.resize(validSize);
				forfeitCards.resize(validSize);
				forfeitTimers.resize(validSize);
				usedForfeits.resize(validSize);

				// Print resized vector sizes
				std::cout << "Resized Motif Names Size: " << forfeitMotifNames.size() << std::endl;
				std::cout << "Resized Titles Size: " << forfeitTitles.size() << std::endl;
				std::cout << "Resized Cards Size: " << forfeitCards.size() << std::endl;
				std::cout << "Resized Timers Size: " << forfeitTimers.size() << std::endl;

				// Assign values from imported data to the vectors
				std::copy(motifNames.begin(), motifNames.begin() + validSize, forfeitMotifNames.begin());
				std::copy(titles.begin(), titles.begin() + validSize, forfeitTitles.begin());
				std::copy(cards.begin(), cards.begin() + validSize, forfeitCards.begin());
				std::copy(timers.begin(), timers.begin() + validSize, forfeitTimers.begin());

				// Debugging the data copied into vectors
				std::cout << "Motif Names after copy: ";
				for (const auto& motif : forfeitMotifNames) std::cout << motif << " ";
				std::cout << std::endl;

				std::cout << "Titles after copy: ";
				for (const auto& title : forfeitTitles) std::cout << title << " ";
				std::cout << std::endl;

				std::cout << "Cards after copy: ";
				for (const auto& card : forfeitCards) std::cout << card << " ";
				std::cout << std::endl;

				std::cout << "Timers after copy: ";
				for (const auto& timer : forfeitTimers) std::cout << timer << " ";
				std::cout << std::endl;

				std::cout << "All copied" << std::endl;
			}
			else {
				std::cerr << "Error: No valid forfeit data to load" << std::endl;
				failedForfeitImport = true;
			}
		}
		else {
			failedForfeitImport = true;
			std::cout << ".import else" << std::endl;
		}
	}
	else {
		std::cout << "Failed to open forfeit file" << std::endl;
		failedForfeitImport = true;
	}

	if (failedForfeitImport) {
		CustomMessageBox failedForfeit("Pour Decisions", "Forfeits could not be imported", 2, window);
		MessageBoxButton result = failedForfeit.showMessageBox(); // Show the message box

		if (result == MessageBoxButton::Ok) {
			std::cout << "OK button clicked" << std::endl;
			window.close();
		}
		else if (result == MessageBoxButton::Cancel) {
			std::cout << "Cancel button clicked" << std::endl;
			window.close();
		}
	}

	return !failedForfeitImport;
}


//Game

bool Game::init()
{
	std::cout << "Initialising Game.." << std::endl;
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

		disclamerButton.setBackgroundColor(disclamerRed, window.getSize().x * 0.27f, window.getSize().y * 0.07f);
		disclamerButton.setBorder(disclamerRed, 2.0f);
		disclamerButton.setPosition(window.getSize().x / 2 - disclamerButton.getGlobalBounds().width / 2, window.getSize().y * 0.91f);
		disclamerButton.setText("ACKNOWLEDGE", ryeFont, window.getSize().y * 0.055f);
		disclamerButton.setTextColor(disclamerWhite);
		
	}

	if (!showDisclamer) {
		disclamerAcknowledged = true;
	}

	std::cout << "Passed Disclamer" << std::endl; //DEBUG

	//Main Game

	scaleX = static_cast<float>(window.getSize().x) / BASE_RESOLUTION.x;
	scaleY = static_cast<float>(window.getSize().y) / BASE_RESOLUTION.y;

	std::cout << "Passed Scalers" << std::endl; //DEBUG

	//Player Names
	playerNames.reserve(MAX_PLAYERS); //Reserve space for max number of players

	//Other Vars
	currentPlayers = 0;

	std::cout << "Passed Player Names stuff" << std::endl; //DEBUG

	//Main Menu
	in_main_menu = !showDisclamer; //Main Menu State
	is_menu_music_playing = false;

	std::cout << "Passed Main menu init vars" << std::endl; //DEBUG
	

	logoSprite.setScale(scaleX * 0.3f, scaleX * 0.3f);
	logoSprite.setPosition(((window.getSize().x / 2) - (logoSprite.getGlobalBounds().width / 2)), 10);

	std::cout << "Passed logo" << std::endl; //DEBUG

	//Play Button
	playButton.setBackgroundImage(buttonRectTexture);
	playButton.setBackgroundScale(0.6f, 0.6f);
	playButton.setText("PLAY", righteousFont, 60);
	playButton.setTextColor(buttonNormalColour);
	playButton.setHoverColor(buttonHoverColour);
	playButton.setPosition(((window.getSize().x / 2) - (playButton.getGlobalBounds().width / 2)), window.getSize().y - 270);

	std::cout << "Passed play" << std::endl; //DEBUG

	//Options Button
	optionButton.setBackgroundImage(buttonThinRectTexture);
	optionButton.setBackgroundScale(0.6f, 0.6f);
	optionButton.setText("OPTIONS", righteousFont, 40);
	optionButton.setTextColor(buttonNormalColour);
	optionButton.setHoverColor(buttonHoverColour);
	optionButton.setPosition(((window.getSize().x / 2) - (optionButton.getGlobalBounds().width/2) - optionButton.getGlobalBounds().width/2) - 25, window.getSize().y - 150);

	std::cout << "Passed options" << std::endl; //DEBUG

	//HTP Button
	htpButton.setBackgroundImage(buttonThinRectTexture);
	htpButton.setBackgroundScale(0.6f, 0.6f);
	htpButton.setText("HOW TO PLAY", righteousFont, 40);
	htpButton.setTextColor(buttonNormalColour);
	htpButton.setHoverColor(buttonHoverColour);
	htpButton.setPosition(((window.getSize().x / 2) - (htpButton.getGlobalBounds().width/2) + htpButton.getGlobalBounds().width/2) + 25, window.getSize().y - 150);

	std::cout << "Passed htp" << std::endl; //DEBUG

	//Quit Button
	quitButton.setBackgroundImage(buttonCircleTexture);
	quitButton.setBackgroundScale(scaleX * 0.4f, scaleX * 0.4f);
	quitButton.setText("X", righteousFont, window.getSize().y * 0.0416f);
	quitButton.setTextColor(buttonNormalColour);
	quitButton.setHoverColor(buttonHoverColour);
	quitButton.setPosition(window.getSize().x - quitButton.getGlobalBounds().width - 25, 25);

	std::cout << "Passed quit" << std::endl; //DEBUG

	//Transition
	spinwheelTransition.init(transitionTexture, 0.3f, window); //0.3s transition
	
	std::cout << "Passed spinwheel transition" << std::endl; //DEBUG

	//Options Screen
	in_options = false;
	optionsScreen.initialise(musicVolume, sfxVolume, fullscreen, resolution, nsfwEnabled, winPoints);
	
	std::cout << "Passed options screen init" << std::endl; //DEBUG

	//How To play
	in_how_to_play = false;
	htpScreen.init();
	

	//Player Setup State
	in_player_setup = false;
	playerSetup.initialise();
	
	std::cout << "Passed player setup init" << std::endl; //DEBUG

	//Main Game
	in_game = false;
	is_game_music_playing = false;
	mainGame.init();

	std::cout << "Passed main game init" << std::endl; //DEBUG
	
	audioManager.setMusicVolume(musicVolume);
	audioManager.setGlobalSoundEffectVolume(sfxVolume);

	std::cout << "Passed audio volume" << std::endl; //DEBUG

	std::cout << "Game Initialised!" << std::endl; //DEBUG

	return true;
}

bool Game::checkAllCardsUsed() {
	bool allCardsUsed = true;

	// Check non-custom cards
	for (int i = 0; i < DEFAULT_CATEGORIES_AMOUNT; i++) {
		if (usedCards[i].size() != cardQuantity[i]) {
			allCardsUsed = false;
			break;
		}
	}

	// Check custom cards if in use
	if (usingCustomCards) {
		if (usedCustomCards.size() != amountOfCustomCards) {
			allCardsUsed = false;
		}
	}

	return allCardsUsed;
}

void Game::resetUsedCards() {
	if (usingCustomCards) {
		usedCustomCards.clear(); // Clear custom cards
	}

	// Clear used cards for each category
	for (int i = 0; i < DEFAULT_CATEGORIES_AMOUNT; i++) {
		usedCards[i].clear();
	}
}

void Game::update(float dt)
{
	//Button Hover Handling
	sf::Vector2i click = sf::Mouse::getPosition(window);
    sf::Vector2f windowClickPos = window.mapPixelToCoords(click);

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

		
	}

	if(!in_main_menu && in_options)
	{
		//In Options Menu
		optionsScreen.update(dt, windowClickPos);

	}

	if (!in_main_menu && in_how_to_play)
	{
		htpScreen.update(dt, windowClickPos);
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

		
	}

	if (!in_main_menu && in_options)
	{
		//In Options Screen
		optionsScreen.draw(window);
	}

	if (!in_main_menu && in_how_to_play)
	{
		htpScreen.draw(window);
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
		mainGame.draw(window, dt);
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
	else if (pageID == 1) {
		//Coming from htp
		in_how_to_play = false;
		in_main_menu = true;
	}
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
		if (playerNames.size() != 0) {
			playerNames.clear();
		}
	}	
}

void Game::toOptions(int pageID) {
	if (pageID == 0) {
		//From menu
		in_main_menu = false;
		in_options = true;
	} else if (pageID == 3) {
		//from Main Game
		in_game = false;
		in_options = true;
	}
}

void Game::transitionToMainGame() {
	if (in_player_setup) {
		in_player_setup = false;
		in_game = true;
		mainGame.populatePlayers(playerNames);
	}
}

void Game::transitionToSetup(int pageID) {
	if (pageID == 0) {
		//From main menu
		in_main_menu = false;
		in_player_setup = true;
	}
	else if (pageID == 3) {
		//From main game - play agiain
		in_game = false;
		in_player_setup = true;
		playerSetup.repopulatePlayers(playerNames);
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

void Game::clearPlayerArray() {
	playerNames.clear();
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
				transitionToSetup(0);
			}

			if (optionButton.isClicked(windowClickPos)) {
				//Options Button Clicked
				audioManager.playSoundEffect("buttonClick");
				std::cout << "Options Button Clicked" << std::endl;
				toOptions(0);
			}

			if (htpButton.isClicked(windowClickPos)) {
				//HTP Button Clicked
				audioManager.playSoundEffect("buttonClick");
				std::cout << "HTP Button Clicked" << std::endl;
				in_main_menu = false;
				in_how_to_play = true;
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
		else if (!in_main_menu && in_how_to_play)
		{
			htpScreen.handleMouse(windowClickPos);
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

	if (!in_main_menu && in_options)
	{
		//In Options Menu
		optionsScreen.handleTextEntry(event);

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
}

bool Game::isRestartRequired() const {
	return optionsScreen.isRestartRequested();
}


