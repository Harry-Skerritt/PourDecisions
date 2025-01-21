#ifndef PLAYERSETUP_H
#define PLAYERSETUP_H
#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "../VisualAddons/GradientText.h"
#include "../VisualAddons/Confetti.h"
#include "../Utils/Widgets/Button.h"
#include "../Utils/Widgets/InputField.h"

//Continue moving player setup into this

class Game;

class PlayerSetup {
public:
	PlayerSetup(sf::RenderWindow&, sf::Font& font);
	~PlayerSetup();

	void setGameInstance(Game* game);

	void initialise();

	void update(float dt, sf::Vector2f& windowClick);

	void handleMouse(sf::Event event, sf::Vector2f windowClick);

	void handleTextEntry(sf::Event event);

	void draw(sf::RenderWindow& window, ConfettiManager& confetti);

private:
	sf::RenderWindow& window;
	sf::Font& font;

	Game* m_game;

	GradientText playerSetupTitle;
	InputField playerNameEntry;
	Button addPlayerButton;

};

#endif