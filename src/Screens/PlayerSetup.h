#ifndef PLAYERSETUP_H
#define PLAYERSETUP_H
#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

//Continue moving player setup into this

class Game;

class PlayerSetup
{
public:
	PlayerSetup(sf::RenderWindow&, sf::Font& font);
	~PlayerSetup();

	void setGameInstnace(Game* game);

	bool init();

	void update(float dt);

	void draw(sf::RenderWindow& window);
};

#endif