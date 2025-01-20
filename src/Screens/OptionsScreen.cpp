#include "OptionsScreen.h"
#include "../Utils/GradientBackground.h"
#include "../Managers/AudioManager.h"
#include "../Game.h"
#include <iostream>

OptionsScreen::OptionsScreen(sf::RenderWindow& window, sf::Font& font) : window(window), font(font) {};
OptionsScreen::~OptionsScreen() {};


void OptionsScreen::setGameInstance(Game* game) {
	m_game = game;  // Set the Game pointer
}

void OptionsScreen::initialise(float& musicVol, float& sfxVol)
{
	musicVol = AudioManager::getInstance().getMusicVolume();
	sfxVol = 100.0f; //Needs the global set functionality

	//Title
	optionsTitle.setFont(font);
	optionsTitle.setString("OPTIONS");
	optionsTitle.setCharacterSize(80);
	optionsTitle.setGradientColors(sf::Color(251, 0, 188, 255), sf::Color(0, 238, 255, 255));
	optionsTitle.setPosition(((window.getSize().x / 2) - (optionsTitle.getGlobalBounds().width / 2)), 60);

	//Holder
	int holderOffset = 240;
	int holderX = 420;
	int holderY = 300;

	//Graphics Holder
	graphicsHolder.setFillColor(holderBack);
	graphicsHolder.setSize(sf::Vector2f(holderX, holderY));
	graphicsHolder.setPosition(((window.getSize().x / 2) - (graphicsHolder.getGlobalBounds().width/2) - holderOffset), 150);

	//Audio Holder
	audioHolder.setFillColor(holderBack);
	audioHolder.setSize(sf::Vector2f(holderX, holderY));
	audioHolder.setPosition(((window.getSize().x / 2) - (audioHolder.getGlobalBounds().width/2) + holderOffset), 150);
	
	//Custom file holder
	customFileHolder.setFillColor(holderBack);
	customFileHolder.setSize(sf::Vector2f((holderX*2) + 40, holderY/2));
	customFileHolder.setPosition(((window.getSize().x / 2) - (customFileHolder.getGlobalBounds().width / 2)), 150 + holderY + 50);

	//Holder Titles
	//Graphics
	graphicsText.setFont(font);
	graphicsText.setString("Graphics");
	graphicsText.setCharacterSize(60);
	graphicsText.setFillColor(sf::Color::White);

	sf::FloatRect g_textBounds = graphicsText.getLocalBounds();
	graphicsText.setOrigin(g_textBounds.left + g_textBounds.width / 2, g_textBounds.top + g_textBounds.height / 2);
	graphicsText.setPosition(graphicsHolder.getPosition().x + graphicsHolder.getSize().x / 2,
		graphicsHolder.getPosition().y + 40);

	//Audio
	audioText.setFont(font);
	audioText.setString("Audio");
	audioText.setCharacterSize(60);
	audioText.setFillColor(sf::Color::White);

	sf::FloatRect a_textBounds = audioText.getLocalBounds();
	audioText.setOrigin(a_textBounds.left + a_textBounds.width / 2, a_textBounds.top + a_textBounds.height / 2);
	audioText.setPosition(audioHolder.getPosition().x + audioHolder.getSize().x / 2,
		audioHolder.getPosition().y + 40);

	//Graphics
	//Fullscreen
	fullscreenLabel.setFont(font);
	fullscreenLabel.setString("Fullscreen");
	fullscreenLabel.setCharacterSize(40);

	sf::FloatRect fl_textBounds = fullscreenLabel.getLocalBounds();
	fullscreenLabel.setOrigin(fl_textBounds.left + fl_textBounds.width / 2, fl_textBounds.top + fl_textBounds.height / 2);
	fullscreenLabel.setPosition(graphicsHolder.getPosition().x + 110,
		graphicsHolder.getPosition().y + 100);

	int checkBox_x = graphicsHolder.getPosition().x + graphicsHolder.getLocalBounds().width; //RHS of holder
	fullscreenCheckbox.setSize(40.0f, 40.0f);
	fullscreenCheckbox.setPosition(checkBox_x - 60, graphicsHolder.getPosition().y + 90);
	fullscreenCheckbox.setFillColor(sf::Color(66, 126, 137, 255), sf::Color(250, 0, 188, 255));
	fullscreenCheckbox.setBorderColor(sf::Color(11, 80, 92, 255));
	fullscreenCheckbox.setOnStateChangedCallback([](bool checked) {
			std::cout << "Checkbox is now " << (checked ? "checked" : "unchecked") << std::endl;
			AudioManager::getInstance().playSoundEffect("buttonClick");
		});

	//Resolution
	resolutionLabel.setFont(font);
	resolutionLabel.setString("Resolution");
	resolutionLabel.setCharacterSize(40);

	sf::FloatRect rl_textBounds = resolutionLabel.getLocalBounds();
	resolutionLabel.setOrigin(rl_textBounds.left + rl_textBounds.width / 2, rl_textBounds.top + rl_textBounds.height / 2);
	resolutionLabel.setPosition(graphicsHolder.getPosition().x + 110,
		graphicsHolder.getPosition().y + 170);


	std::vector<std::string> resolutions = {
		"1920x1080",
		"1280x720",
		"1080x720"
	};
	resolutionMenu.initialize(checkBox_x - 162, graphicsHolder.getPosition().y + 150, 150, 40, resolutions, font);
	resolutionMenu.setColors(sf::Color(66, 126, 137, 255), sf::Color::White, sf::Color::Cyan, pd_pink, sf::Color(11, 80, 92, 255));
	resolutionMenu.setSelectedItem("1080x720");

	//Audio
	musicSlider.setSize(300.f, 20.f);
	musicSlider.setPosition(100.f, 100.f);
	musicSlider.setHandleColor(pd_pink);
	musicSlider.setTrackColor(sf::Color(100, 9, 136, 255));
	musicSlider.setValue(musicVol);

	// Set the callback to print the slider value when it changes
	musicSlider.setOnValueChangedCallback([](float value) {
		std::cout << "Music Slider Value: " << value << std::endl;
		AudioManager::getInstance().setMusicVolume(value);
		});

	sfxSlider.setSize(300.f, 20.f);
	sfxSlider.setPosition(100.f, 200.f);
	sfxSlider.setHandleColor(pd_pink);
	sfxSlider.setTrackColor(sf::Color(100, 9, 136, 255));
	sfxSlider.setValue(sfxVol);

	// Set the callback to print the slider value when it changes
	sfxSlider.setOnValueChangedCallback([](float value) {
		std::cout << "SoundFx Slider Value: " << value << std::endl;
		//AudioManager::getInstance().setMusicVolume(value); //Set the sfx volume globally
		});
	

	//Back Button
	if (!backButtonTexture.loadFromFile("../Data/Assets/Buttons/backButton.png"))
	{
		std::cout << "Back Button Did not load properly - Options" << std::endl;
	}
	backButton.setTexture(backButtonTexture);
	backButton.setScale(0.6f, 0.6f);
	backButton.setPosition((window.getSize().x - backButton.getGlobalBounds().width) - 20, 20);
	
}

void OptionsScreen::handleMouse(sf::Event event)
{
	fullscreenCheckbox.handleMouseInput(sf::Mouse::getPosition(window), true);	   //Add a popup saying the app will restart and then do the full screen
	resolutionMenu.handleEvent(event, sf::Mouse::getPosition(window));		   //Add a popup saying the app will restart and then do the resolution change

	//Click
	sf::Vector2i click = sf::Mouse::getPosition(window);
	sf::Vector2f windowClickPos = window.mapPixelToCoords(click);

	musicSlider.handleMouseInput(sf::Mouse::getPosition(window), true);
	sfxSlider.handleMouseInput(sf::Mouse::getPosition(window), true);

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		if (backButton.getGlobalBounds().contains(windowClickPos)) {
			//Back button clicked
			AudioManager::getInstance().playSoundEffect("buttonClick");
			std::cout << "Back button clicked" << std::endl;
			if (m_game) {
				m_game->backToMainMenu(0); //Back to main menu
			}
		}
		
		
	}
	else {
		//musicSlider.handleMouseInput(sf::Mouse::getPosition(window), false);
	}
}

void OptionsScreen::draw(sf::RenderWindow& window)
{
	GradientBackground::setBackgroundGradient(window);
	//Background
	window.draw(optionsTitle);
	window.draw(backButton); //Add handler

	//Holders
	window.draw(graphicsHolder);
	window.draw(audioHolder);
	window.draw(customFileHolder);

	//Holder Labels
	window.draw(graphicsText);
	window.draw(audioText);

	//Graphics
	window.draw(fullscreenLabel);
	window.draw(fullscreenCheckbox); //<- Add functionality
	window.draw(resolutionLabel);
	window.draw(resolutionMenu); //<- Add functionality
	
	//Audio
	window.draw(musicSlider);
	window.draw(sfxSlider);
	
	
}