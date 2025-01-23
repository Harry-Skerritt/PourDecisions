#ifndef PLAYERBOARDDISPLAY_H
#define PLAYERBOARDDISPLAY_H

#include <SFML/Graphics.hpp>
#include <string>

class PlayerBoardDisplay {
public:
	PlayerBoardDisplay();
	~PlayerBoardDisplay();
	
	void initialise(std::string& playerName, sf::Font& playerNameFont, sf::Font& pointsFont, float posX, float posY, float sizeX, float sizeY, int startPoints = 0, int charSize = 0);

	void setPosition(float x, float y);
	void setSize(float x, float y);

	void setPointsColour(sf::Color& pointsColour, sf::Color& winningColour);
	void setSelectedColour(sf::Color& selectedColour);
	void setPointsBackgroundColour(sf::Color& colour);

	void update(float dt);

	sf::FloatRect getGlobalBounds() const;
	sf::FloatRect getLocalBounds() const;

	sf::Vector2f getPosition() const;

	void draw(sf::RenderWindow& window);

	void setSelected(bool state);
	void setWinningPlayer(bool state);

	void changePoints(int newPointValue);

private:
	bool m_isSelected = false;
	bool m_isWinning = false;

	std::string m_playerName;
	int m_points = 0; //Default value

	sf::Font m_playerNameFont;
	sf::Font m_pointsFont;

	sf::RectangleShape displayBackground;

	sf::Text playerNameText;
	int m_playerNameCharSize;

	sf::RectangleShape pointBox;
	sf::Text playerPoints;
	int m_playerPointsCharSize;

	sf::Color m_pointsColour = sf::Color::White;
	sf::Color m_winningColour = sf::Color(250, 0, 188, 255);

	sf::Color m_pointsBackground = sf::Color(16, 83, 138, 255);

	sf::Color m_selectedColour = sf::Color(112, 3, 154);

	void resizeObjects();	  //Helper
	void repositionObjects(); //Helper

};


#endif //PLAYERBOARDDISPLAY_H