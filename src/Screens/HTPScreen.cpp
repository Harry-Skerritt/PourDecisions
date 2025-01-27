#include "HTPScreen.h"
#include "../Game.h"
#include "../Managers/AudioManager.h"

HowToPlayScreen::HowToPlayScreen(sf::RenderWindow& window, sf::Font& font1, sf::Font& font2) : window(window), righteousFont(font1), ryeFont(font2) {};

HowToPlayScreen::~HowToPlayScreen() {};

void HowToPlayScreen::setGameInstance(Game* game) {
	m_game = game;
}

void HowToPlayScreen::init() {
	
	//Title
	titleText.setFont(righteousFont);
	titleText.setString("HOW TO PLAY");
	titleText.setCharacterSize(80);
	titleText.setGradientColors(gradientColour1, gradientColour2);
	titleText.setPosition(((window.getSize().x / 2) - (titleText.getGlobalBounds().width / 2)), 60);

	//Section Background
	sf::Vector2f backgroundSize = sf::Vector2f(window.getSize().x * 0.423f, window.getSize().y * 0.69f);
	rulesBackground.setSize(backgroundSize);
	rulesBackground.setFillColor(purpleColour);
	rulesBackground.setPosition(window.getSize().x / 2 - (rulesBackground.getGlobalBounds().width) - (window.getSize().x * 0.028f), window.getSize().y * 0.217f);

	gameplayBackground.setSize(backgroundSize);
	gameplayBackground.setFillColor(purpleColour);
	gameplayBackground.setPosition(window.getSize().x / 2 + (window.getSize().x * 0.028f), window.getSize().y * 0.217f);

	//Back Button
	backButton.setBackgroundImage(m_game->buttonCircleTexture);
	backButton.setBackgroundScale(m_game->scaleX * 0.4f, m_game->scaleX * 0.4f);
	backButton.setText("<", righteousFont, window.getSize().y * 0.0416f);
	backButton.setTextColor(m_game->buttonNormalColour);
	backButton.setHoverColor(m_game->buttonHoverColour);
	backButton.setPosition(window.getSize().y * 0.0231f, window.getSize().y * 0.0231f);

	//Section Titles
	rulesTitle.setFont(ryeFont);
	rulesTitle.setFillColor(sf::Color::White);
	rulesTitle.setCharacterSize(window.getSize().y * 0.0694f);
	rulesTitle.setString("Rules");
	rulesTitle.setOrigin(rulesTitle.getLocalBounds().width / 2, rulesTitle.getLocalBounds().height / 2);
	rulesTitle.setPosition(rulesBackground.getPosition().x + rulesBackground.getSize().x / 2, rulesBackground.getPosition().y + window.getSize().y * 0.048f);

	gameplayTitle.setFont(ryeFont);
	gameplayTitle.setFillColor(sf::Color::White);
	gameplayTitle.setCharacterSize(window.getSize().y * 0.0694f);
	gameplayTitle.setString("Game Play");
	gameplayTitle.setOrigin(gameplayTitle.getLocalBounds().width / 2, gameplayTitle.getLocalBounds().height / 2);
	gameplayTitle.setPosition(gameplayBackground.getPosition().x + gameplayBackground.getSize().x / 2, gameplayBackground.getPosition().y + window.getSize().y * 0.048f);

	//Set up rules
	for(auto& rule : rules) {
		sf::Text text(rule, righteousFont, window.getSize().y * 0.033f);
		text.setFillColor(sf::Color::White);
		rulesText.push_back(text);
	}
	
	positionTextList(rulesTitle, rulesText, rulesBackground, righteousFont);

	//Setup gameplay
	for (auto& item : gameplay) {
		sf::Text text(item, righteousFont, window.getSize().y * 0.033f);
		text.setFillColor(sf::Color::White);
		gameplayText.push_back(text);
	}

	positionTextList(gameplayTitle, gameplayText, gameplayBackground, righteousFont);
	positionTextList(gameplayTitle, gameplayText, gameplayBackground, righteousFont);
}

void HowToPlayScreen::update(float dt, sf::Vector2f clickPos) {
	backButton.handleHover(clickPos);
}

void HowToPlayScreen::handleMouse(sf::Vector2f clickPos) {
	if (backButton.isClicked(clickPos)) {
		AudioManager::getInstance().playSoundEffect("buttonClick");
		m_game->backToMainMenu(1);
	}
}

void HowToPlayScreen::draw(sf::RenderWindow& window) {
	GradientBackground::setBackgroundGradient(window);

	window.draw(titleText);
	window.draw(rulesBackground);
	window.draw(gameplayBackground);
	backButton.draw(window);
	window.draw(rulesTitle);
	window.draw(gameplayTitle);

	for (auto& rule : rulesText) {
		window.draw(rule);
	}
	
	for (auto& item : gameplayText) {
		window.draw(item);
	}

	
}


std::string HowToPlayScreen::wrapText(const sf::Text& text, const sf::RectangleShape& rectangle, const sf::Font& font, unsigned int characterSize) {
	std::string originalString = text.getString();
	std::string wrappedString;
	float maxWidth = rectangle.getGlobalBounds().width - 10;

	std::string currentLine;
	float currentLineWidth = 0.f;

	std::istringstream wordStream(originalString);
	std::string word;

	while (wordStream >> word) {
		// Temporarily add the next word to the current line
		std::string tempLine = currentLine + (currentLine.empty() ? "" : " ") + word;

		// Measure the width of the temporary line
		sf::Text tempText(tempLine, font, characterSize);
		currentLineWidth = tempText.getLocalBounds().width;

		if (currentLineWidth > maxWidth) {
			// If the line is too wide, wrap before adding the word
			if (!currentLine.empty()) {
				wrappedString += currentLine + "\n";
			}
			currentLine = word; // Start a new line with the current word
		}
		else {
			// Otherwise, add the word to the current line
			currentLine = tempLine;
		}
	}

	// Add the last line to the wrapped string
	if (!currentLine.empty()) {
		wrappedString += currentLine;
	}

	return wrappedString;
}

void HowToPlayScreen::positionTextList(
	const sf::Text& headerText,
	std::vector<sf::Text>& textList,
	const sf::RectangleShape& rectangle,
	const sf::Font& font
) {
	float padding = 10.f;
	// Get rectangle bounds
	sf::FloatRect rectangleBounds = rectangle.getGlobalBounds();

	// Calculate the vertical space available for the text list
	float availableHeight = rectangleBounds.height - headerText.getGlobalBounds().height - 2.f * padding;

	// Start position for the first text (just below the header)
	float startY = headerText.getPosition().y + headerText.getGlobalBounds().height + padding;

	// Track the current Y position for placing text
	float currentY = startY;

	for (size_t i = 0; i < textList.size(); ++i) {
		sf::Text& text = textList[i];

		// Wrap text to fit within the rectangle
		text.setString(wrapText(text, rectangle, font, text.getCharacterSize()));

		// Get bounds of the wrapped text
		sf::FloatRect textBounds = text.getLocalBounds();

		// Position the text within the rectangle
		text.setPosition(
			rectangleBounds.left + padding,  // Left-aligned with padding
			currentY                         // Current vertical position
		);

		// Update the current Y position for the next text
		currentY += textBounds.height + padding; // Add text height and padding
	}
}

