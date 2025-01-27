#include "ForfeitCard.h"
#include "../Managers/AudioManager.h"
#include "../Screens/MainGame.h"

ForfeitCard::ForfeitCard() {};
ForfeitCard::~ForfeitCard() {};

void ForfeitCard::setMainGameInstance(MainGame* game) {
	m_mainGame = game;
}

void ForfeitCard::initialise(sf::Font& font1, sf::Font& font2, std::string title, std::string body, std::string imgLoc, float scaleX, sf::RenderWindow& window, bool group) {
	righteousFont = font1;
	ryeFont = font2;
	titleText = title;
	messageText = body;
	groupCard = group;
	headerText = "FORFEIT";

	if (!motifTexture.loadFromFile(imgLoc)) {
		std::cerr << "Card Motif did not load" << std::endl;
	}

	motifSprite.setTexture(motifTexture);

	//Darken Screen
	screenDarken.setSize(sf::Vector2f(window.getSize().x, window.getSize().y));
	screenDarken.setFillColor(sf::Color(0, 0, 0, 179));

	//Set Background Up
	cardBackground.setSize(sf::Vector2f(window.getSize().x * 0.35f, window.getSize().y * 0.8f));
	cardBackground.setFillColor(cardBackColour);
	cardBackground.setPosition(window.getSize().x / 2 - cardBackground.getGlobalBounds().width / 2, window.getSize().y / 2 - cardBackground.getGlobalBounds().height / 2); //Centre the card to the screen
	cardBackground.setOutlineThickness(4.0f);
	cardBackground.setOutlineColor(borderColour);

	//Set header up
	cardHeader.setSize(sf::Vector2f(cardBackground.getSize().x, cardBackground.getSize().y * 0.17f));
	cardHeader.setFillColor(cardColour);
	cardHeader.setPosition(cardBackground.getPosition().x, cardBackground.getPosition().y); //Set header position
	cardHeader.setOutlineThickness(4.0f);
	cardHeader.setOutlineColor(borderColour);

	//Set header text up
	cardHeaderText.setFont(ryeFont);
	cardHeaderText.setFillColor(cardBackColour);
	cardHeaderText.setString(headerText);
	cardHeaderText.setCharacterSize(cardHeader.getSize().y * 0.8f); //Make dyanmic to make it all fit
	cardHeaderText.setOrigin(cardHeaderText.getLocalBounds().width / 2, cardHeaderText.getLocalBounds().height / 2);
	cardHeaderText.setPosition(cardHeader.getPosition().x + cardHeader.getSize().x / 2,
		cardHeader.getPosition().y + cardHeader.getSize().y / 2 - cardHeaderText.getCharacterSize() * 0.2f); //Place header

	//Set title up
	cardTitleText.setFont(righteousFont);
	cardTitleText.setFillColor(borderColour);
	cardTitleText.setString(titleText);
	cardTitleText.setCharacterSize(cardHeader.getSize().y * 0.6f); //Make dyanmic to make it all fit
	fitToWidth(cardTitleText, cardBackground);
	cardTitleText.setOrigin(cardTitleText.getLocalBounds().width / 2, cardTitleText.getLocalBounds().height / 2);
	cardTitleText.setPosition(cardHeader.getPosition().x + cardHeader.getSize().x / 2,
		cardHeader.getPosition().y + cardHeader.getSize().y * 1.25f); //Place title

	// Message
	cardMessageText.setFont(righteousFont);
	cardMessageText.setFillColor(borderColour);
	cardMessageText.setCharacterSize(window.getSize().y * 0.042f);
	cardMessageText.setString(messageText);
	wrapText(cardMessageText, cardBackground.getSize().x * 0.9f);




	// Motif
	motifSprite.setScale(scaleX * 0.6f, scaleX * 0.6f);

	//Done button
	doneButton.setBackgroundColor(cardColour, cardBackground.getSize().x * 0.89f, cardBackground.getSize().y * 0.1f);
	doneButton.setBorder(borderColour, 2.0f);
	doneButton.setText("DONE", ryeFont, window.getSize().y * 0.055f);
	doneButton.setTextColor(cardBackColour);
	doneButton.setPosition(cardBackground.getPosition().x + cardBackground.getSize().x / 2 - doneButton.getGlobalBounds().width / 2,
		cardBackground.getPosition().y + cardBackground.getSize().y - doneButton.getGlobalBounds().height - 20);


	adjustLayout(cardMessageText, cardBackground, motifSprite, doneButton);

	/*
	//Set Message up
	cardMessageText.setFont(righteousFont);
	cardMessageText.setFillColor(borderColour);
	cardMessageText.setCharacterSize(window.getSize().y * 0.037f);
	cardMessageText.setString(messageText);
	wrapText(cardMessageText, cardBackground.getSize().x * 0.9f);
	cardMessageText.setOrigin(cardMessageText.getLocalBounds().width / 2, cardMessageText.getLocalBounds().height / 2);
	cardMessageText.setPosition(cardBackground.getPosition().x + cardBackground.getSize().x / 2,
		cardBackground.getPosition().y + cardBackground.getSize().y * 0.4f); //place message


	//Set up motif
	motifSprite.setScale(scaleX * 0.6f, scaleX * 0.6f);
	motifSprite.setOrigin(motifSprite.getLocalBounds().width / 2, motifSprite.getLocalBounds().height / 2);
	motifSprite.setPosition(cardBackground.getPosition().x + cardBackground.getSize().x / 2,
		cardBackground.getPosition().y + cardBackground.getSize().y * 0.75f); //place motif
	*/
}

void ForfeitCard::setPosition(float x, float y) {
	cardBackground.setPosition(sf::Vector2f(x, y));
}

void ForfeitCard::update(float dt, sf::Vector2f clickPos) {
	doneButton.handleHover(clickPos);
}

sf::FloatRect ForfeitCard::getGlobalBounds() const {
	return cardBackground.getGlobalBounds();
}

sf::FloatRect ForfeitCard::getLocalBounds() const {
	return cardBackground.getLocalBounds();
}

sf::Vector2f ForfeitCard::getPosition() const {
	return cardBackground.getPosition();
}

void ForfeitCard::handleMouse(sf::Vector2f clickPos) {
	if (doneButton.isClicked(clickPos)) {
		m_mainGame->forfeitComplete(groupCard);
	}
}

void ForfeitCard::showCard(sf::RenderWindow& window, float dt) {
	drawFadeComponents(
		window,
		screenDarken,
		cardBackground,
		cardHeader,
		cardHeaderText,
		cardTitleText,
		cardMessageText,
		motifSprite,
		doneButton,        
		dt, // Delta time
		1.5f, // Fade speed (normalized, 0.5 = 2 seconds for full fade)
		true
	);

}

void ForfeitCard::hideCard(sf::RenderWindow& window, float dt) {
	drawFadeComponents(
		window,
		screenDarken,
		cardBackground,
		cardHeader,
		cardHeaderText,
		cardTitleText,
		cardMessageText,
		motifSprite,
		doneButton,
		dt, // Delta time
		1.0f, // Fade speed (normalized, 0.5 = 2 seconds for full fade)
		false
	);
}

void ForfeitCard::drawFadeComponents(
	sf::RenderWindow& window,
	sf::RectangleShape& screenDarken,
	sf::RectangleShape& cardBackground,
	sf::RectangleShape& cardHeader,
	sf::Text& cardHeaderText,
	sf::Text& cardTitle,
	sf::Text& cardMessage,
	sf::Sprite& cardMotif,
	SolidButton& doneButton,
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

	sf::Color headerTextColour = cardHeaderText.getFillColor();
	headerTextColour.a = alpha;
	cardHeaderText.setFillColor(headerTextColour);

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
	doneButton.setAlpha(alpha);

	// Draw everything
	window.draw(screenDarken);
	window.draw(cardBackground);
	window.draw(cardHeader);
	window.draw(cardHeaderText);
	window.draw(cardTitle);
	window.draw(cardMessage);
	window.draw(cardMotif);
	doneButton.draw(window);

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

bool ForfeitCard::isCardVisible() {
	return cardVisible;
}

void ForfeitCard::wrapText(sf::Text& text, float maxWidth)
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

void ForfeitCard::adjustLayout(sf::Text& cardMessage, sf::RectangleShape& cardBackground, sf::Sprite& cardMotif, SolidButton& doneButton) {
	const float padding = 30.0f; // Space between elements

	// Get button top position (since they are at the bottom of the card)
	float buttonsTop = doneButton.getPosition().y;

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
		cardTitleText.getPosition().y + cardTitleText.getGlobalBounds().height + padding // Below cardTitleText
	);

	// Position cardMotif below cardMessage
	cardMotif.setPosition(
		cardBackground.getPosition().x + cardBackground.getGlobalBounds().width / 2 - cardMotif.getGlobalBounds().width / 2, // Center horizontally
		cardMessage.getPosition().y + cardMessage.getGlobalBounds().height + padding // Below cardMessage
	);
}

void ForfeitCard::fitToWidth(sf::Text& text, const sf::RectangleShape& rectangle) {
	sf::FloatRect textBounds = text.getLocalBounds();
	float rectangleWidth = rectangle.getGlobalBounds().width;

	// Reduce the font size until the text fits within the rectangle's width
	while (textBounds.width > rectangleWidth && text.getCharacterSize() > 5) {
		unsigned int currentSize = text.getCharacterSize();
		text.setCharacterSize(currentSize - 1);
		textBounds = text.getLocalBounds();
	}

	// Re-center the text to account for updated size
	text.setOrigin(textBounds.left + textBounds.width / 2, textBounds.top + textBounds.height / 2);
	text.setPosition(
		rectangle.getPosition().x + rectangle.getGlobalBounds().width / 2,
		rectangle.getPosition().y + rectangle.getGlobalBounds().height / 2
	);
}