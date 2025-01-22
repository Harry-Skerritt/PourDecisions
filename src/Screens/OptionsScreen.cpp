#include "OptionsScreen.h"
#include "../Utils/GradientBackground.h"
#include "../Managers/AudioManager.h"
#include "../Utils/CustomMessageBox.h"
#include "../Game.h"
#include <iostream>

OptionsScreen::OptionsScreen(sf::RenderWindow& window, sf::Font& font) : window(window), font(font) {};
OptionsScreen::~OptionsScreen() {};


void OptionsScreen::setGameInstance(Game* game) {
	m_game = game;  // Set the Game pointer
}

void OptionsScreen::initialise(float& musicVol, float& sfxVol, bool fs, std::string res)
{
	musicVol = musicVol;
	sfxVol = sfxVol;
	fullscreen = fs;
	resolution = res;

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

	//Custom file

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
	fullscreenCheckbox.setChecked(fullscreen);
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
	resolutionMenu.setSelectedItem(resolution);

	//Audio
	//Music
	musicLabel.setFont(font);
	musicLabel.setString("Music");
	musicLabel.setCharacterSize(40);

	sf::FloatRect ml_textBounds = musicLabel.getLocalBounds();
	musicLabel.setOrigin(ml_textBounds.left + ml_textBounds.width / 2, ml_textBounds.top + ml_textBounds.height / 2);
	musicLabel.setPosition(audioHolder.getPosition().x + 110,
		audioHolder.getPosition().y + 100);

	int slider_x = audioHolder.getPosition().x + audioHolder.getLocalBounds().width; //RHS of holder
	musicSlider.setSize(200.f, 15.f);
	musicSlider.setPosition(slider_x - 230, audioHolder.getPosition().y + 90.f);
	musicSlider.setHandleColor(pd_pink);
	musicSlider.setTrackColor(sf::Color(100, 9, 136, 255));
	musicSlider.setValue(musicVol);

	// Callback from slider
	musicSlider.setOnValueChangedCallback([](float value) {
		std::cout << "Music Slider Value: " << value << std::endl;
		AudioManager::getInstance().setMusicVolume(value);

		});

	//SFX
	sfxLabel.setFont(font);
	sfxLabel.setString("Sound FX");
	sfxLabel.setCharacterSize(35);

	sf::FloatRect sl_textBounds = sfxLabel.getLocalBounds();
	sfxLabel.setOrigin(sl_textBounds.left + sl_textBounds.width / 2, sl_textBounds.top + sl_textBounds.height / 2);
	sfxLabel.setPosition(audioHolder.getPosition().x + 100,
		audioHolder.getPosition().y + 170);

	sfxSlider.setSize(200.f, 15.f);
	sfxSlider.setPosition(slider_x - 230, audioHolder.getPosition().y + 160.f);
	sfxSlider.setHandleColor(pd_pink);
	sfxSlider.setTrackColor(sf::Color(100, 9, 136, 255));
	sfxSlider.setValue(sfxVol);

	// Callback from slider
	sfxSlider.setOnValueChangedCallback([](float value) {
		std::cout << "SoundFx Slider Value: " << value << std::endl;
		//AudioManager::getInstance().setMusicVolume(value); //Set the sfx volume globally
		});
	

	//Custom File

	//Back Button
	backButton.setBackgroundImage(m_game->buttonCircleTexture);
	backButton.setBackgroundScale(0.6f, 0.6f);
	backButton.setText(">", font, 40);
	backButton.setTextColor(m_game->buttonNormalColour);
	backButton.setHoverColor(m_game->buttonHoverColour);
	backButton.setPosition((window.getSize().x - backButton.getGlobalBounds().width) - 20, 20);

	saveButton.setBackgroundImage(m_game->buttonThinRectTexture);
	saveButton.setBackgroundScale(0.3f, 0.6f);
	saveButton.setText("SAVE", font, 40);
	saveButton.setTextColor(m_game->buttonNormalColour);
	saveButton.setHoverColor(m_game->buttonHoverColour);
	saveButton.setPosition((backButton.getPosition().x - saveButton.getGlobalBounds().width) - 20, 20);
	
}

void OptionsScreen::update(float dt, sf::Vector2f& windowClick) {
	backButton.handleHover(windowClick);
	saveButton.handleHover(windowClick);
}

void OptionsScreen::splitResolution(const std::string& resolution, int& width, int& height) {
	size_t xPos = resolution.find('x');
	if (xPos == std::string::npos) {
		throw std::invalid_argument("Invalid resolution format. Expected format: 'widthxheight'");
	}

	// Extract the width and height as substrings
	std::string widthStr = resolution.substr(0, xPos);
	std::string heightStr = resolution.substr(xPos + 1);

	// Convert substrings to integers
	width = std::stoi(widthStr);
	height = std::stoi(heightStr);
}

void OptionsScreen::handleMouse(sf::Event event, sf::Vector2f& windowClick)
{
	fullscreenCheckbox.handleMouseInput(sf::Mouse::getPosition(window), true);	  
	resolutionMenu.handleEvent(event, sf::Mouse::getPosition(window));		       

	musicSlider.handleMouseInput(sf::Mouse::getPosition(window), true);
	sfxSlider.handleMouseInput(sf::Mouse::getPosition(window), true);

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		if (saveButton.isClicked(windowClick)) {
			//Save Button Clicked
			AudioManager::getInstance().playSoundEffect("buttonClick");

			//Check is graphics have changed
			bool fs_changed = false;
			bool res_changed = false;

			//Check if full screen has changed
			if (fullscreenCheckbox.isChecked() != fullscreen) {
				//If its not the same as when it was called then its changed
				fs_changed = true;
			}

			if (resolutionMenu.getSelectedItem() != resolution) {
				//If its not the same as when it was called then its changed
				res_changed = true;
			}

			if (fs_changed || res_changed) {
				//Graphic settings have changed.

				//Create a popup about restart
				CustomMessageBox restartWarning("Pour Decisions", "To change graphics settings, the game will restart", 1);
				MessageBoxButton result = restartWarning.showMessageBox(); //Show the message box

				if (result == MessageBoxButton::Ok) {
					std::cout << "OK button clicked" << std::endl;
					//Okay with restart -> So save all settings and restart
					try {
						Settings settings = Settings::fromFile(settingLoc);

						//Split res
						int resX, resY;
						splitResolution(resolutionMenu.getSelectedItem(), resX, resY);


						// Modify graphisc settings
						settings.setResolution(resX, resY);
						settings.setFullscreen(fullscreenCheckbox.isChecked());

						// Modify audio settings
						musicVol = AudioManager::getInstance().getMusicVolume();
						if (musicVol < 0) {
							musicVol = 0;
						}
						settings.setMusicVolume(musicVol);

						//sfxVol = AudioManager::getInstance().getSFXVolume(); //Update the stored sfx value which needs a global func
						if (sfxVol < 0) {
							sfxVol = 0;
						}
						settings.setSFXVolume(sfxVol);

						// Modify game settings
						settings.setNSFWEnabled(false); //Needs to be added
						settings.setWinPoints(20);		//Needs to be added

						// Save the updated settings back to the file
						settings.saveToFile(settingLoc);

						std::cout << "Settings updated and saved successfully.\n";
					}
					catch (const std::exception& e) {
						std::cerr << "Error: " << e.what() << "\n";
					}

				}
				else if (result == MessageBoxButton::Cancel) {
					std::cout << "Cancel button clicked" << std::endl;
					//Do not want to restart -> Do nothing
				}

			}
			else {
				//Graphics settings havent changed
				//Update Audio and game settings
				try {
					Settings settings = Settings::fromFile(settingLoc);

					// Modify audio settings
					musicVol = AudioManager::getInstance().getMusicVolume();
					settings.setMusicVolume(musicVol);

					//sfxVol = AudioManager::getInstance().getSFXVolume(); //Update the stored sfx value which needs a global func
					settings.setSFXVolume(sfxVol);

					// Modify game settings
					settings.setNSFWEnabled(false); //Needs to be added
					settings.setWinPoints(20);		//Needs to be added

					// Save the updated settings back to the file
					settings.saveToFile(settingLoc);

					std::cout << "Settings updated and saved successfully.\n";
				}
				catch (const std::exception& e) {
					std::cerr << "Error: " << e.what() << "\n";
				}
			}

		}
		if (backButton.isClicked(windowClick)) {
			//Back button clicked
			std::cout << "Back button clicked" << std::endl;
			AudioManager::getInstance().playSoundEffect("buttonClick");

			if (resolutionMenu.getSelectedItem() != resolution || fullscreenCheckbox.isChecked() != fullscreen
				|| AudioManager::getInstance().getMusicVolume() != musicVol) //Add sfx, nsfw and points 
			{
				//Some settings have changed
				CustomMessageBox restartWarning("Pour Decisions", "Changes will not be saved!", 1);
				MessageBoxButton result = restartWarning.showMessageBox(); //Show the message box

				if (result == MessageBoxButton::Ok) {
					std::cout << "OK button clicked" << std::endl;

					//Do not care about saving changes to go back
					if (m_game) {
						m_game->backToMainMenu(0); //Back to main menu
					}
				}
				else if (result == MessageBoxButton::Cancel) {
					//Want to save so do nothing
				}
			}
			else {
				//No settings have changed so go back
				if (m_game) {
					m_game->backToMainMenu(0); //Back to main menu
				}
			}
		}
	}
}

void OptionsScreen::draw(sf::RenderWindow& window)
{
	GradientBackground::setBackgroundGradient(window);
	//Background
	window.draw(optionsTitle);
	backButton.draw(window);
	saveButton.draw(window);

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
	window.draw(musicLabel);
	window.draw(musicSlider);
	window.draw(sfxLabel);
	window.draw(sfxSlider); // <- Add functionality
	
	
}