#include "Card.h"
#include "../Managers/AudioManager.h"
#include "../Screens/MainGame.h"


Card::Card() {};
Card::~Card() {};

void Card::setMainGameInstance(MainGame* game) {
	m_mainGame = game;
}

void Card::initialise(sf::Color& colour, sf::Font& mainFont, sf::Font& secondaryFont, std::string title, std::string body, std::string imgLoc, float scaleX, sf::RenderWindow& window, bool group) {
	cardColour = colour;
	cardBodyFont = mainFont;
	cardHeaderFont = secondaryFont;
	cardHeaderText = title;
	cardBodyText = body;
	groupCard = group;

	//Load Motif Texture
	if (!cardMotifTex.loadFromFile(imgLoc)) {
		std::cerr << "Card Motif did not load" << std::endl;
	}

	cardMotif.setTexture(cardMotifTex);

	//Darken Screen
	screenDarken.setSize(sf::Vector2f(window.getSize().x, window.getSize().y));
	screenDarken.setFillColor(sf::Color(0, 0, 0, 179));

	//Set Background Up
	cardBackground.setSize(sf::Vector2f(window.getSize().x * 0.35f, window.getSize().y * 0.8f));
	cardBackground.setFillColor(cardBackColour);
	cardBackground.setPosition(window.getSize().x / 2 - cardBackground.getGlobalBounds().width / 2, window.getSize().y / 2 - cardBackground.getGlobalBounds().height / 2); //Centre the card to the screen
	cardBackground.setOutlineThickness(4.0f);
	cardBackground.setOutlineColor(borderColour);

	


	//Header
	cardHeader.setSize(sf::Vector2f(cardBackground.getSize().x, cardBackground.getSize().y * 0.17f));
	cardHeader.setFillColor(cardColour);
	cardHeader.setPosition(cardBackground.getPosition().x, cardBackground.getPosition().y); //Set header position
	cardHeader.setOutlineThickness(4.0f);
	cardHeader.setOutlineColor(borderColour);

	//Title
	cardTitle.setFont(cardHeaderFont);
	cardTitle.setFillColor(cardBackColour);
	cardTitle.setString(cardHeaderText);
	cardTitle.setCharacterSize(cardHeader.getSize().y * 0.8f);

	// Calculate bounds and adjust origin
	sf::FloatRect bounds = cardTitle.getLocalBounds();
	cardTitle.setOrigin(bounds.left + bounds.width / 2, bounds.top + bounds.height / 2);

	// Calculate target position for centering
	sf::Vector2f targetPosition(
		cardHeader.getPosition().x + cardHeader.getGlobalBounds().width / 2,
		cardHeader.getPosition().y + cardHeader.getGlobalBounds().height / 2);
	cardTitle.setPosition(targetPosition);

	// Resize the text to fit within the header width
	fitTextToWidth(cardTitle, cardHeader.getSize().x - 10);

	// Recalculate the bounds after resizing
	bounds = cardTitle.getLocalBounds();
	cardTitle.setOrigin(bounds.left + bounds.width / 2, bounds.top + bounds.height / 2);

	// Adjust vertical alignment
	cardTitle.setPosition(targetPosition.x, targetPosition.y - bounds.top / 2);
	

	// Message
	cardMessage.setFont(cardBodyFont);
	cardMessage.setFillColor(borderColour);
	cardMessage.setCharacterSize(window.getSize().y * 0.042f);
	cardMessage.setString(cardBodyText);
	wrapText(cardMessage, cardBackground.getSize().x * 0.9f);




	// Motif
	cardMotif.setScale(scaleX * 0.6f, scaleX * 0.6f);

	// Buttons
	forfeitButton.setBackgroundColor(cardColour, cardBackground.getSize().x * 0.43f, cardBackground.getSize().y * 0.1f);
	forfeitButton.setBorder(borderColour, 2.0f);
	forfeitButton.setPosition(
		cardBackground.getPosition().x + cardBackground.getGlobalBounds().width / 2 - forfeitButton.getGlobalBounds().width - 10, // Left button
		cardBackground.getPosition().y + cardBackground.getGlobalBounds().height - forfeitButton.getGlobalBounds().height - 20 // 20px from the bottom
	);
	forfeitButton.setText("Forfeit", secondaryFont, window.getSize().y * 0.055f);
	forfeitButton.setTextColor(cardBackColour);
	

	passButton.setBackgroundColor(cardBackColour, cardBackground.getSize().x * 0.43f, cardBackground.getSize().y * 0.1f);
	passButton.setBorder(cardColour, 2.0f);
	passButton.setPosition(
		cardBackground.getPosition().x + cardBackground.getGlobalBounds().width / 2 + 10, // Right button
		cardBackground.getPosition().y + cardBackground.getGlobalBounds().height - passButton.getGlobalBounds().height - 20 // 20px from the bottom
	);
	passButton.setText("Pass", secondaryFont, window.getSize().y * 0.055f);
	passButton.setTextColor(cardColour);
	

	adjustLayout(cardMessage, cardBackground, cardMotif, forfeitButton, passButton);
}

void Card::adjustLayout(sf::Text& cardMessage, sf::RectangleShape& cardBackground, sf::Sprite& cardMotif, SolidButton& forfeitButton, SolidButton& passButton) {
	const float padding = 30.0f; // Space between elements

	// Get button top position (since they are at the bottom of the card)
	float buttonsTop = forfeitButton.getPosition().y;

	// Calculate the space required for the cardMessage and motif
	float messageAndMotifHeight = cardMessage.getGlobalBounds().height + padding + cardMotif.getGlobalBounds().height;

	// Check if the cardMessage and motif fit between the cardHeader and buttons
	while ((cardHeader.getPosition().y + cardHeader.getGlobalBounds().height + padding + messageAndMotifHeight > buttonsTop) &&
		cardMessage.getCharacterSize() > 10) { // Minimum font size of 10
		// Reduce the character size of cardMessage
		cardMessage.setCharacterSize(cardMessage.getCharacterSize() - 1);
		wrapText(cardMessage, cardBackground.getSize().x * 0.9f); // Re-wrap text after resizing

		// Recalculate the message height
		messageAndMotifHeight = cardMessage.getGlobalBounds().height + padding + cardMotif.getGlobalBounds().height;
	}

	// Position cardMessage below cardHeader
	cardMessage.setOrigin(cardMessage.getGlobalBounds().width / 2, 0); // Top center origin
	cardMessage.setPosition(
		cardBackground.getPosition().x + cardBackground.getGlobalBounds().width / 2, // Center horizontally
		cardHeader.getPosition().y + cardHeader.getGlobalBounds().height + padding // Below cardHeader
	);

	// Position cardMotif below cardMessage
	cardMotif.setPosition(
		cardBackground.getPosition().x + cardBackground.getGlobalBounds().width / 2 - cardMotif.getGlobalBounds().width / 2, // Center horizontally
		cardMessage.getPosition().y + cardMessage.getGlobalBounds().height + padding // Below cardMessage
	);
}

void Card::setPosition(float x, float y) {
	cardBackground.setPosition(sf::Vector2f(x, y));
}

void Card::update(float dt, sf::Vector2f clickPos) {
	forfeitButton.handleHover(clickPos);
	passButton.handleHover(clickPos);
}

void Card::handleMouse(sf::Vector2f clickPos) {
	if (passButton.isClicked(clickPos)) {
		m_mainGame->cardPass(groupCard);
	}

	if (forfeitButton.isClicked(clickPos)) {
		m_mainGame->cardForfeit(groupCard);
	}
}

sf::FloatRect Card::getGlobalBounds() const {
	return cardBackground.getGlobalBounds();
}

sf::FloatRect Card::getLocalBounds() const {
	return cardBackground.getLocalBounds();
}

sf::Vector2f Card::getPosition() const {
	return cardBackground.getPosition();
}

void Card::showCard(sf::RenderWindow& window, float dt) {
	drawFadeComponents(
		window,
		screenDarken,
		cardBackground,
		cardHeader,
		cardTitle,
		cardMessage,
		cardMotif,
		forfeitButton,
		passButton,
		dt,        // Delta time
		1.5f,       // Fade speed (normalized, 0.5 = 2 seconds for full fade)
		true
	);
	
}

void Card::hideCard(sf::RenderWindow& window, float dt) {
	drawFadeComponents(
		window,
		screenDarken,
		cardBackground,
		cardHeader,
		cardTitle,
		cardMessage,
		cardMotif,
		forfeitButton,
		passButton,
		dt,        // Delta time
		1.0f,       // Fade speed (normalized, 0.5 = 2 seconds for full fade)
		false
	);
}

void Card::drawFadeComponents(
	sf::RenderWindow& window,
	sf::RectangleShape& screenDarken,
	sf::RectangleShape& cardBackground,
	sf::RectangleShape& cardHeader,
	sf::Text& cardTitle,
	sf::Text& cardMessage,
	sf::Sprite& cardMotif,
	SolidButton& forfeitButton,
	SolidButton& passButton,
	float deltaTime,
	float fadeSpeed,
	bool fadeIn // true for fade in, false for fade out
)
{
	static float fadeProgress = fadeIn ? 0.0f : 1.0f;

	// Update fade progress
	fadeProgress += (fadeIn ? fadeSpeed : -fadeSpeed) * deltaTime;
	fadeProgress = std::clamp(fadeProgress, 0.0f, 1.0f);

	// Calculate alpha values
	sf::Uint8 alpha = static_cast<sf::Uint8>(fadeProgress * 255);
	sf::Uint8 darkenAlpha = static_cast<sf::Uint8>(fadeProgress * 179); // screenDarken max alpha is 179

	// Set screenDarken alpha
	sf::Color darkenColor = screenDarken.getFillColor();
	darkenColor.a = darkenAlpha;
	screenDarken.setFillColor(darkenColor);

	// Set alpha for all other components
	sf::Color backgroundColour = cardBackground.getFillColor();
	backgroundColour.a = alpha;
	cardBackground.setFillColor(backgroundColour);

	sf::Color backgroundBorderColour = cardBackground.getOutlineColor();
	backgroundBorderColour.a = alpha;
	cardBackground.setOutlineColor(backgroundBorderColour);

	sf::Color headerColour = cardHeader.getFillColor();
	headerColour.a = alpha;
	cardHeader.setFillColor(headerColour);

	sf::Color headerBorderColour = cardBackground.getOutlineColor();
	headerBorderColour.a = alpha;
	cardHeader.setOutlineColor(headerBorderColour);

	sf::Color titleColour = cardTitle.getFillColor();
	titleColour.a = alpha;
	cardTitle.setFillColor(titleColour);

	sf::Color messageColour = cardMessage.getFillColor();
	messageColour.a = alpha;
	cardMessage.setFillColor(messageColour);

	sf::Color motifColour = cardMotif.getColor();
	motifColour.a = alpha;
	cardMotif.setColor(motifColour);

	// Update button alpha
	forfeitButton.setAlpha(alpha);
	passButton.setAlpha(alpha);

	// Draw everything
	window.draw(screenDarken);
	window.draw(cardBackground);
	window.draw(cardHeader);
	window.draw(cardMotif);
	window.draw(cardTitle);
	window.draw(cardMessage);
	forfeitButton.draw(window);
	passButton.draw(window);

	//If the fade is done and fading in
	if (fadeProgress == 1.0f && fadeIn) {
		//Then it must be visible
		cardVisible = true;
	}
	else if (fadeProgress == 0.0f && !fadeIn) {
		//If the fade is done and fading out
		//Then it must be hidden
		cardVisible = false;
	}
}

bool Card::isCardVisible() {
	return cardVisible;
}

void Card::wrapText(sf::Text& text, float maxWidth)
{
	const sf::Font* font = text.getFont();
	if (!font)
	{
		throw std::runtime_error("Font not set for sf::Text object.");
	}

	unsigned int characterSize = text.getCharacterSize();
	sf::String originalString = text.getString();

	std::wstring wrappedString;
	std::wstringstream wordStream(originalString.toWideString());
	std::wstring word;
	float lineWidth = 0.f;

	while (wordStream >> word)
	{
		float wordWidth = 0.f;
		for (auto ch : word)
		{
			wordWidth += font->getGlyph(ch, characterSize, false).advance;
		}

		// Check if the word fits on the current line
		if (lineWidth + wordWidth > maxWidth)
		{
			// Start a new line
			wrappedString += L'\n';
			lineWidth = 0.f;
		}

		// Add the word to the line
		wrappedString += word + L' ';
		lineWidth += wordWidth + font->getGlyph(L' ', characterSize, false).advance;
	}

	// Update the sf::Text object with the wrapped text
	text.setString(wrappedString);
}

void Card::fitTextToWidth(sf::Text& text, float targetWidth) {
	float characterSize = text.getCharacterSize();
	sf::FloatRect textBounds = text.getLocalBounds();

	while (textBounds.width > targetWidth && characterSize > 1) {
		characterSize -= 1;
		text.setCharacterSize(characterSize);
		textBounds = text.getLocalBounds();
	}
}