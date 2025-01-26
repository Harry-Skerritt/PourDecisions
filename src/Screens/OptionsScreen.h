#ifndef OPTIONSSCREEN_H
#define OPTIONSSCREEN_H

#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "../Utils/GradientText.h"
#include "../Utils/Widgets/VolumeSlider.h"
#include "../Utils/Widgets/CheckBox.h"
#include "../Utils/Widgets/DropdownMenu.h"
#include "../Utils/Widgets/Button.h"
#include "../Utils/Widgets/InputField.h"
#include "../Utils/JSON/Settings.h"

#include <string>

class Game;

class OptionsScreen {
public:
	OptionsScreen(sf::RenderWindow& window, sf::Font& font);
	~OptionsScreen();

	void setGameInstance(Game* game);

	void initialise(float& musicVol, float& sfxVol, bool fs, std::string res, bool nsfw, int winPoints);

	void update(float dt, sf::Vector2f& windowClick);

	void handleMouse(sf::Event event, sf::Vector2f& windowClick);

	void handleTextEntry(sf::Event event);

	void draw(sf::RenderWindow& window);

	bool isRestartRequested() const { return restartRequested; }

	//Graphics
	Checkbox fullscreenCheckbox;
	DropdownMenu resolutionMenu;

	//Game Settings
	Checkbox nsfwEnabledCheckbox;
	InputField pointsToWinInput;

	//Helper function
	void splitResolution(const std::string& resolution, int& width, int& height);

private:
	sf::RenderWindow& window;
	sf::Font& font;

	bool restartRequested = false;

	Game* m_game;
	std::string settingLoc = "../Data/Settings.json";

	float musicVol;
	float sfxVol;
	bool fullscreen;
	std::string resolution;
	bool nsfwEnabled;
	int pointsToWin;

	sf::Color gradientColour_1 = sf::Color(3, 58, 60, 255);
	sf::Color gradientColour_2 = sf::Color(0, 215, 253, 255);
	sf::Color pd_pink = sf::Color(250, 0, 188, 255);
	sf::Color holderBack = sf::Color(44, 3, 60, 255);

	//Text
	GradientText optionsTitle;
	sf::Text graphicsText;
	sf::Text audioText;
	sf::Text customText;
	sf::Text gameText;

	//Graphics
	sf::Text fullscreenLabel;
	sf::Text resolutionLabel;
	

	//Audio
	sf::Text musicLabel;
	sf::Text sfxLabel;
	VolumeSlider musicSlider;
	VolumeSlider sfxSlider;

	//Custom Cards
	sf::Text fileLabel;

	//Game Settings
	sf::Text nsfwLabel;
	sf::Text pointsLabel;


	//Backgrounds <- Set to rounded rects once working
	sf::RectangleShape graphicsHolder;
	sf::RectangleShape audioHolder;
	sf::RectangleShape customFileHolder;
	sf::RectangleShape gameSettingHolder;

	//Buttons
	Button backButton;
	Button saveButton;

	
};

#endif // OPTIONSSCREEN_H
