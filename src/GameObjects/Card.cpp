#include "Card.h"


Card::Card() {};
Card::~Card() {};

void Card::initialise(sf::Color& colour, sf::Font& mainFont, sf::Font& secondaryFont, std::string title, std::string body, std::string imgLoc, float scaleX, sf::RenderWindow& window) {
	cardColour = colour;
	cardBodyFont = mainFont;
	cardHeaderFont = secondaryFont;
	cardHeaderText = title;
	cardBodyText = body;

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

	cardMotif.setScale(scaleX * 0.6f, scaleX * 0.6f);
	cardMotif.setPosition((cardBackground.getPosition().x + cardBackground.getGlobalBounds().width / 2) - cardMotif.getGlobalBounds().width / 2,
		(cardBackground.getPosition().y + cardBackground.getGlobalBounds().height / 2)); //Place Motif

	cardHeader.setSize(sf::Vector2f(cardBackground.getSize().x, cardBackground.getSize().y * 0.17f));
	cardHeader.setFillColor(cardColour);
	cardHeader.setPosition(cardBackground.getPosition().x, cardBackground.getPosition().y); //Set header position
	cardHeader.setOutlineThickness(4.0f);
	cardHeader.setOutlineColor(borderColour);

	cardTitle.setFont(cardHeaderFont);
	cardTitle.setFillColor(cardBackColour);
	cardTitle.setString(cardHeaderText);
	cardTitle.setCharacterSize(cardHeader.getSize().y * 0.8f); //Make dyanmic to make it all fit
	cardTitle.setOrigin(cardTitle.getGlobalBounds().width / 2, cardTitle.getGlobalBounds().height / 2);
	cardTitle.setPosition((cardHeader.getPosition().x + cardHeader.getGlobalBounds().width / 2),
		(cardHeader.getPosition().y + cardHeader.getGlobalBounds().height / 2) - cardHeader.getSize().y * 0.2f); //Place title

	cardMessage.setFont(cardBodyFont);
	cardMessage.setFillColor(borderColour);
	cardMessage.setCharacterSize(window.getSize().y * 0.042f);
	cardMessage.setString(cardBodyText);
	wrapText(cardMessage, cardBackground.getSize().x * 0.9f);
	cardMessage.setOrigin(cardMessage.getGlobalBounds().width / 2, cardMessage.getGlobalBounds().height / 2);
	cardMessage.setPosition((cardBackground.getPosition().x + cardBackground.getGlobalBounds().width / 2),
		(cardBackground.getPosition().y + cardBackground.getGlobalBounds().height / 2) - cardMessage.getGlobalBounds().height*0.9f);

	forfeitButton.setBackgroundColor(cardColour, cardBackground.getSize().x * 0.43f, cardBackground.getSize().y * 0.1f);
	forfeitButton.setBorder(borderColour, 2.0f);
	forfeitButton.setText("Forfeit", secondaryFont, window.getSize().y * 0.055f);
	forfeitButton.setTextColor(cardBackColour);
	forfeitButton.setPosition((cardBackground.getPosition().x + cardBackground.getGlobalBounds().width / 2) - forfeitButton.getGlobalBounds().width - 10,
		cardBackground.getSize().y - 30);

	passButton.setBackgroundColor(cardBackColour, cardBackground.getSize().x * 0.43f, cardBackground.getSize().y * 0.1f);
	passButton.setBorder(cardColour, 2.0f);
	passButton.setText("Pass", secondaryFont, window.getSize().y * 0.055f);
	passButton.setTextColor(cardColour);
	passButton.setPosition((cardBackground.getPosition().x + cardBackground.getGlobalBounds().width / 2) + 10,
		cardBackground.getSize().y - 30);

}

void Card::setPosition(float x, float y) {
	cardBackground.setPosition(sf::Vector2f(x, y));
}

void Card::update(float dt, sf::Vector2f clickPos) {
	forfeitButton.handleHover(clickPos);
	passButton.handleHover(clickPos);
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

void Card::draw(sf::RenderWindow& window) {
	window.draw(screenDarken);
	window.draw(cardBackground);
	window.draw(cardHeader);
	window.draw(cardTitle);
	window.draw(cardMotif);
	window.draw(cardMessage);
	forfeitButton.draw(window);
	passButton.draw(window);
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