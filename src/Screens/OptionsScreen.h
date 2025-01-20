#ifndef OPTIONSSCREEN_H
#define OPTIONSSCREEN_H

#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "../VisualAddons/GradientText.h"
//#include "../Utils/RoundedRectangle.h" // <- Fix
#include "../Utils/Widgets/VolumeSlider.h"
#include "../Utils/Widgets/CheckBox.h"
#include "../Utils/Widgets/DropdownMenu.h"

class Game;

class OptionsScreen {
public:
	OptionsScreen(sf::RenderWindow& window, sf::Font& font);
	~OptionsScreen();

	void setGameInstance(Game* game);

	void initialise(float& musicVol, float& sfxVol);

	void handleMouse(sf::Event event);

	void draw(sf::RenderWindow& window);

private:
	sf::RenderWindow& window;
	sf::Font& font;

	Game* m_game;

	float musicVol;
	float sfxVol;

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
	VolumeSlider musicSlider;
	VolumeSlider sfxSlider;

	//Backgrounds <- Set to rounded rects once working
	sf::RectangleShape graphicsHolder;
	sf::RectangleShape audioHolder;
	sf::RectangleShape customFileHolder;

	//Buttons
	sf::Sprite backButton;
	sf::Texture backButtonTexture;
};

#endif // OPTIONSSCREEN_H
