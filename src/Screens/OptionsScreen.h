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

#include <string>

class Game;

class OptionsScreen {
public:
	OptionsScreen(sf::RenderWindow& window, sf::Font& font);
	~OptionsScreen();

	void setGameInstance(Game* game);

	void initialise(float& musicVol, float& sfxVol, bool fs, std::string res);

	void update(float dt, sf::Vector2f& windowClick);

	void handleMouse(sf::Event event, sf::Vector2f& windowClick);

	void draw(sf::RenderWindow& window);

private:
	sf::RenderWindow& window;
	sf::Font& font;

	Game* m_game;

	float musicVol;
	float sfxVol;
	bool fullscreen;
	std::string resolution;

	sf::Color gradientColour_1 = sf::Color(3, 58, 60, 255);
	sf::Color gradientColour_2 = sf::Color(0, 215, 253, 255);
	sf::Color pd_pink = sf::Color(250, 0, 188, 255);
	sf::Color holderBack = sf::Color(44, 3, 60, 255);

	//Text
	GradientText optionsTitle;
	sf::Text graphicsText;
	sf::Text audioText;

	//Graphics
	sf::Text fullscreenLabel;
	sf::Text resolutionLabel;
	Checkbox fullscreenCheckbox;
	DropdownMenu resolutionMenu;

	//Audio
	sf::Text musicLabel;
	sf::Text sfxLabel;
	VolumeSlider musicSlider;
	VolumeSlider sfxSlider;

	//Backgrounds <- Set to rounded rects once working
	sf::RectangleShape graphicsHolder;
	sf::RectangleShape audioHolder;
	sf::RectangleShape customFileHolder;

	//Buttons
	Button backButton;
};

#endif // OPTIONSSCREEN_H
