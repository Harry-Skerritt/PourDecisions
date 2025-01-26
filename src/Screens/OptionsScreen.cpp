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

void OptionsScreen::initialise(float& musicVolIn, float& sfxVolIn, bool fs, std::string res, bool nsfw, int winPoints)
{
	musicVol = musicVolIn;
	sfxVol = sfxVolIn;
	fullscreen = fs;
	resolution = res;
	nsfwEnabled = nsfw;
	pointsToWin = winPoints;

	//Title
	optionsTitle.setFont(font);
	optionsTitle.setString("OPTIONS");
	optionsTitle.setCharacterSize(window.getSize().y * 0.11f);
	optionsTitle.setGradientColors(sf::Color(251, 0, 188, 255), sf::Color(0, 238, 255, 255));
	optionsTitle.setPosition(((window.getSize().x / 2) - (optionsTitle.getGlobalBounds().width / 2)), 60);

	//Holder
	int holderOffset = window.getSize().x * 0.22f;
	int holderX = window.getSize().x * 0.38f;
	int holderY = window.getSize().y * 0.41f;

	//Graphics Holder
	graphicsHolder.setFillColor(holderBack);
	graphicsHolder.setSize(sf::Vector2f(holderX, holderY * 0.85));
	graphicsHolder.setPosition(((window.getSize().x / 2) - (graphicsHolder.getGlobalBounds().width/2) - holderOffset), window.getSize().y * 0.2f);

	//Audio Holder
	audioHolder.setFillColor(holderBack);
	audioHolder.setSize(sf::Vector2f(holderX, holderY * 0.85));
	audioHolder.setPosition(((window.getSize().x / 2) - (audioHolder.getGlobalBounds().width/2) + holderOffset), graphicsHolder.getPosition().y);
	
	//Custom file holder
	customFileHolder.setFillColor(holderBack);
	customFileHolder.setSize(sf::Vector2f((holderX*1.4f), holderY * 0.83));
	customFileHolder.setPosition(graphicsHolder.getPosition().x, (graphicsHolder.getPosition().y + graphicsHolder.getGlobalBounds().height) + window.getSize().y * 0.062f);

	//Game Holder
	gameSettingHolder.setFillColor(holderBack);
	gameSettingHolder.setSize(sf::Vector2f(holderX * 0.69f, holderY * 0.83));
	gameSettingHolder.setPosition((audioHolder.getPosition().x + audioHolder.getGlobalBounds().width) - gameSettingHolder.getGlobalBounds().width, customFileHolder.getPosition().y);

	//Holder Titles
	//Graphics
	graphicsText.setFont(font);
	graphicsText.setString("Graphics");
	graphicsText.setCharacterSize(window.getSize().x * 0.05f);
	graphicsText.setFillColor(sf::Color::White);

	sf::FloatRect g_textBounds = graphicsText.getLocalBounds();
	graphicsText.setOrigin(g_textBounds.left + g_textBounds.width / 2, g_textBounds.top + g_textBounds.height / 2);
	graphicsText.setPosition(graphicsHolder.getPosition().x + graphicsHolder.getSize().x / 2,
		audioHolder.getPosition().y + holderY * 0.1f);

	//Audio
	audioText.setFont(font);
	audioText.setString("Audio");
	audioText.setCharacterSize(window.getSize().x * 0.055f);
	audioText.setFillColor(sf::Color::White);

	sf::FloatRect a_textBounds = audioText.getLocalBounds();
	audioText.setOrigin(a_textBounds.left + a_textBounds.width / 2, a_textBounds.top + a_textBounds.height / 2);
	audioText.setPosition(audioHolder.getPosition().x + audioHolder.getSize().x / 2,
		audioHolder.getPosition().y + holderY * 0.1f);

	//Custom File Text
	customText.setFont(font);
	customText.setString("Custom Cards");
	customText.setCharacterSize(window.getSize().y * 0.044f);
	customText.setFillColor(sf::Color::White);

	sf::FloatRect c_textBounds = customText.getLocalBounds();
	customText.setOrigin(c_textBounds.left + c_textBounds.width / 2, c_textBounds.top + c_textBounds.height / 2);
	customText.setPosition(customFileHolder.getPosition().x + customFileHolder.getSize().x / 2,
		customFileHolder.getPosition().y + holderY * 0.1f);

	//Game Settings Text
	gameText.setFont(font);
	gameText.setString("Game Settings");
	gameText.setCharacterSize(window.getSize().y * 0.044f);
	gameText.setFillColor(sf::Color::White);

	sf::FloatRect gm_textBounds = gameText.getLocalBounds();
	gameText.setOrigin(gm_textBounds.left + gm_textBounds.width / 2, gm_textBounds.top + gm_textBounds.height / 2);
	gameText.setPosition(gameSettingHolder.getPosition().x + gameSettingHolder.getSize().x / 2,
		gameSettingHolder.getPosition().y + holderY * 0.1f);


	//Graphics
	//Fullscreen
	fullscreenLabel.setFont(font);
	fullscreenLabel.setString("Fullscreen");
	fullscreenLabel.setCharacterSize(window.getSize().x * 0.037f);

	sf::FloatRect fl_textBounds = fullscreenLabel.getLocalBounds();
	fullscreenLabel.setOrigin(fl_textBounds.left + fl_textBounds.width / 2, fl_textBounds.top + fl_textBounds.height / 2);
	fullscreenLabel.setPosition(graphicsHolder.getPosition().x + window.getSize().x * 0.1f,
		graphicsHolder.getPosition().y + holderX * 0.26f);

	int checkBox_x = graphicsHolder.getPosition().x + graphicsHolder.getLocalBounds().width; //RHS of holder
	fullscreenCheckbox.setSize(window.getSize().x * 0.037f, window.getSize().x * 0.037f);
	fullscreenCheckbox.setPosition(checkBox_x - window.getSize().x * 0.055f, (graphicsHolder.getPosition().y + holderX * 0.26f) - (window.getSize().x * 0.037f)/2);
	fullscreenCheckbox.setFillColor(sf::Color(66, 126, 137, 255), sf::Color(250, 0, 188, 255));
	fullscreenCheckbox.setBorderColor(sf::Color(11, 80, 92, 255));
	fullscreenCheckbox.setChecked(fullscreen);
	fullscreenCheckbox.setOnStateChangedCallback([](bool checked) {
			std::cout << "Fullscreen Checkbox is now " << (checked ? "checked" : "unchecked") << std::endl;
			AudioManager::getInstance().playSoundEffect("buttonClick");
		});

	//Resolution
	resolutionLabel.setFont(font);
	resolutionLabel.setString("Resolution");
	resolutionLabel.setCharacterSize(window.getSize().x * 0.037f);

	sf::FloatRect rl_textBounds = resolutionLabel.getLocalBounds();
	resolutionLabel.setOrigin(rl_textBounds.left + rl_textBounds.width / 2, rl_textBounds.top + rl_textBounds.height / 2);
	resolutionLabel.setPosition(graphicsHolder.getPosition().x + window.getSize().x * 0.1f,
		graphicsHolder.getPosition().y + holderX * 0.41f);


	std::vector<std::string> resolutions = {
		"1920x1080",
		"1280x720",
		"1080x720"
	};
	resolutionMenu.initialize(checkBox_x - window.getSize().x * 0.15f, (graphicsHolder.getPosition().y + holderX * 0.41f) - (window.getSize().y * 0.055f / 2), window.getSize().x * 0.138f, window.getSize().y * 0.055f, resolutions, font, window.getSize().y * 0.027f);
	resolutionMenu.setColors(sf::Color(66, 126, 137, 255), sf::Color::White, sf::Color::Cyan, pd_pink, sf::Color(11, 80, 92, 255));
	resolutionMenu.setSelectedItem(resolution);

	//Audio
	//Music
	musicLabel.setFont(font);
	musicLabel.setString("Music");
	musicLabel.setCharacterSize(window.getSize().x * 0.037f);

	sf::FloatRect ml_textBounds = musicLabel.getLocalBounds();
	musicLabel.setOrigin(ml_textBounds.left + ml_textBounds.width / 2, ml_textBounds.top + ml_textBounds.height / 2);
	musicLabel.setPosition(audioHolder.getPosition().x + window.getSize().x * 0.09f,
		audioHolder.getPosition().y + holderX * 0.24f);

	int slider_x = audioHolder.getPosition().x + audioHolder.getLocalBounds().width; //RHS of holder
	musicSlider.setSize(window.getSize().x * 0.185f ,window.getSize().y * 0.02f);
	musicSlider.setPosition(slider_x - window.getSize().x * 0.21f, musicLabel.getPosition().y);
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
	sfxLabel.setCharacterSize(window.getSize().x * 0.032f);

	sf::FloatRect sl_textBounds = sfxLabel.getLocalBounds();
	sfxLabel.setOrigin(sl_textBounds.left + sl_textBounds.width / 2, sl_textBounds.top + sl_textBounds.height / 2);
	sfxLabel.setPosition(audioHolder.getPosition().x + window.getSize().x * 0.09f,
		audioHolder.getPosition().y + holderX * 0.41f);

	sfxSlider.setSize(window.getSize().x * 0.185f, window.getSize().y * 0.02f);
	sfxSlider.setPosition(slider_x - window.getSize().x * 0.21f, sfxLabel.getPosition().y - (sfxLabel.getGlobalBounds().height * 0.01f));
	sfxSlider.setHandleColor(pd_pink);
	sfxSlider.setTrackColor(sf::Color(100, 9, 136, 255));
	sfxSlider.setValue(sfxVol);

	// Callback from slider
	sfxSlider.setOnValueChangedCallback([](float value) {
		std::cout << "SoundFx Slider Value: " << value << std::endl;
		AudioManager::getInstance().setGlobalSoundEffectVolume(value); //Set the sfx volume globally
		});
	

	//Game Settings
	nsfwLabel.setFont(font);
	nsfwLabel.setString("NSFW");
	nsfwLabel.setCharacterSize(window.getSize().x * 0.037f);

	sf::FloatRect ne_textBounds = nsfwLabel.getLocalBounds();
	nsfwLabel.setOrigin(ne_textBounds.left + ne_textBounds.width / 2, ne_textBounds.top + ne_textBounds.height / 2);
	nsfwLabel.setPosition(gameSettingHolder.getPosition().x + nsfwLabel.getGlobalBounds().width /2 + window.getSize().x * 0.01f,
		gameSettingHolder.getPosition().y + window.getSize().y * 0.125f);

	int n_checkBox_x = gameSettingHolder.getPosition().x + gameSettingHolder.getLocalBounds().width; //RHS of holder
	nsfwEnabledCheckbox.setSize(window.getSize().x * 0.037f, window.getSize().x * 0.037f);
	nsfwEnabledCheckbox.setPosition(n_checkBox_x - window.getSize().x * 0.055f, (gameSettingHolder.getPosition().y + window.getSize().y * 0.125f) - (window.getSize().x * 0.037f / 2));
	nsfwEnabledCheckbox.setFillColor(sf::Color(66, 126, 137, 255), sf::Color(250, 0, 188, 255));
	nsfwEnabledCheckbox.setBorderColor(sf::Color(11, 80, 92, 255));
	nsfwEnabledCheckbox.setChecked(nsfwEnabled);
	nsfwEnabledCheckbox.setOnStateChangedCallback([](bool checked) {
		std::cout << "NSFW Checkbox is now " << (checked ? "checked" : "unchecked") << std::endl;
		AudioManager::getInstance().playSoundEffect("buttonClick");
		});

	pointsLabel.setFont(font);
	pointsLabel.setString("Points To Win");
	pointsLabel.setCharacterSize(window.getSize().x * 0.02f);

	sf::FloatRect pl_textBounds = pointsLabel.getLocalBounds();
	pointsLabel.setOrigin(pl_textBounds.left + pl_textBounds.width / 2, pl_textBounds.top + pl_textBounds.height / 2);
	pointsLabel.setPosition(gameSettingHolder.getPosition().x + pointsLabel.getGlobalBounds().width / 2 + window.getSize().x * 0.01f,
		nsfwLabel.getPosition().y + window.getSize().y * 0.098f);

	pointsToWinInput.setFont(font);
	pointsToWinInput.setSize(gameSettingHolder.getSize().x * 0.35f, gameSettingHolder.getSize().y * 0.18f);
	pointsToWinInput.setCharacterSize(window.getSize().y * 0.041f);
	pointsToWinInput.setBackgroundColour(sf::Color(66, 126, 137, 255));
	pointsToWinInput.setPlaceholder(std::to_string(pointsToWin));
	pointsToWinInput.setPosition((n_checkBox_x - window.getSize().x * 0.055f) - pointsToWinInput.getGlobalBounds().width / 2, pointsLabel.getPosition().y - pointsToWinInput.getGlobalBounds().height / 2);

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

	nsfwEnabledCheckbox.handleMouseInput(sf::Mouse::getPosition(window), true);

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		if (saveButton.isClicked(windowClick)) {
			//Save Button Clicked
			AudioManager::getInstance().playSoundEffect("buttonClick");

			//Check is important settings have changed
			bool fs_changed = false;
			bool res_changed = false;
			bool nsfw_changed = false;

			//Check if full screen has changed
			if (fullscreenCheckbox.isChecked() != fullscreen) {
				//If its not the same as when it was called then its changed
				fs_changed = true;
			}

			//Check if resolution has changed
			if (resolutionMenu.getSelectedItem() != resolution) {
				//If its not the same as when it was called then its changed
				res_changed = true;
			}

			//Check if nsfw has change
			if (nsfwEnabledCheckbox.isChecked() != nsfwEnabled) {
				//If its not the same as when it was called then its changed
				nsfw_changed = true;
			}


			if (fs_changed || res_changed || nsfw_changed) {
				//Graphic settings have changed.

				//Create a popup about restart
				CustomMessageBox restartWarning("Pour Decisions", "To change graphics or nsfw settings, the game will restart", 2, window);
				MessageBoxButton result = restartWarning.showMessageBox(); //Show the message box

				if (result == MessageBoxButton::Ok) {
					std::cout << "OK button clicked" << std::endl;
					//Okay with restart -> So save all settings and restart
					try {
						Settings settings = Settings::fromFile(settingLoc);

						//Split res
						int resX, resY;
						resolution = resolutionMenu.getSelectedItem();
						splitResolution(resolution, resX, resY);

					
						// Modify graphisc settings
						settings.setResolution(resX, resY);

						fullscreen = fullscreenCheckbox.isChecked();
						settings.setFullscreen(fullscreen);

						// Modify audio settings
						musicVol = AudioManager::getInstance().getMusicVolume();
						if (musicVol < 0) {
							musicVol = 0;
						}
						settings.setMusicVolume(musicVol);

						sfxVol = AudioManager::getInstance().getSoundEffectVolume();
						if (sfxVol < 0) {
							sfxVol = 0;
						}
						settings.setSFXVolume(sfxVol);

						// Modify game settings
						std::cout << "NSFW BEFORE CHANGING TO THE CHECKBOX: " << nsfwEnabled << std::endl;
						nsfwEnabled = nsfwEnabledCheckbox.isChecked();
						std::cout << "NSFW BEFORE WRITING TO SETTINGS: " << nsfwEnabled << std::endl;
						settings.setNSFWEnabled(nsfwEnabled);

						if (pointsToWinInput.hasValue()) {
							std::cout << "PTW HAS VALUE" << std::endl;
							if (std::stoi(pointsToWinInput.getCurrentValue()) != pointsToWin) {
								//The points have changed
								std::cout << "PTW BEFORE CHANGING: " << std::to_string(pointsToWin) << std::endl;
								std::cout << "PTW BEFORE WRITING TO SETTINGS: " << std::stoi(pointsToWinInput.getCurrentValue()) << std::endl;
								settings.setWinPoints(std::stoi(pointsToWinInput.getCurrentValue()));
							}
						}

						// Save the updated settings back to the file
						settings.saveToFile(settingLoc);


						std::cout << "Settings updated and saved successfully.\n";

						//Settings saved so restart
						restartRequested = true;
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
				CustomMessageBox restartWarning("Pour Decisions", "Changes will not be saved!", 2, window);
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

void OptionsScreen::handleTextEntry(sf::Event event) {
	pointsToWinInput.handleInput(event, true); //Might need to make it so only allowed when the mouse is near
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
	window.draw(gameSettingHolder);

	//Holder Labels
	window.draw(graphicsText);
	window.draw(audioText);
	window.draw(customText);
	window.draw(gameText);
	
	//Graphics
	window.draw(fullscreenLabel);
	window.draw(fullscreenCheckbox); //<- Add functionality - need to fix checked state
	window.draw(resolutionLabel);
	window.draw(resolutionMenu);
	
	//Audio
	window.draw(musicLabel);
	window.draw(musicSlider);
	window.draw(sfxLabel);
	window.draw(sfxSlider); 

	//Game
	window.draw(nsfwLabel);
	window.draw(nsfwEnabledCheckbox);
	window.draw(pointsLabel);
	pointsToWinInput.draw(window);
	
}