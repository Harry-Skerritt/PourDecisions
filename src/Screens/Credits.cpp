#include "Credits.h"
#include "../Utils/GradientBackground.h"
#include "../Managers/AudioManager.h"
#include "../Game.h"

CreditsScreen::CreditsScreen(sf::RenderWindow& window, sf::Font& font1) : window(window), righteousFont(font1) {};
CreditsScreen::~CreditsScreen() {};


void CreditsScreen::setGameInstance(Game* game) {
	m_game = game;
}

void CreditsScreen::init() {
	//Back Button
	backButton.setBackgroundImage(m_game->buttonCircleTexture);
	backButton.setBackgroundScale(m_game->scaleX * 0.4f, m_game->scaleX * 0.4f);
	backButton.setText("<", righteousFont, window.getSize().y * 0.0416f);
	backButton.setTextColor(m_game->buttonNormalColour);
	backButton.setHoverColor(m_game->buttonHoverColour);
	backButton.setPosition(window.getSize().y * 0.0231f, window.getSize().y * 0.0231f);

	//Title
	creditText.setFont(righteousFont);
	creditText.setString("CREDITS");
	creditText.setCharacterSize(80);
	creditText.setGradientColors(gradientColour1, gradientColour2);
	creditText.setPosition(((window.getSize().x / 2) - (creditText.getGlobalBounds().width / 2)), window.getSize().y * 0.05f);

	//The Game
	gameText.setFont(righteousFont);
	gameText.setFillColor(blueColour);
	gameText.setCharacterSize(window.getSize().y * 0.059f);
	gameText.setString("The Game");
	gameText.setOrigin(gameText.getLocalBounds().width / 2, gameText.getLocalBounds().height / 2);
	gameText.setPosition(window.getSize().x / 2, creditText.getPosition().y + window.getSize().y * 0.13f);

	ideaText.setFont(righteousFont);
	ideaText.setFillColor(sf::Color::White);
	ideaText.setCharacterSize(window.getSize().y * 0.044f);
	ideaText.setString("Idea by: Harry Skerritt");
	ideaText.setOrigin(ideaText.getLocalBounds().width / 2, ideaText.getLocalBounds().height / 2);
	ideaText.setPosition(window.getSize().x / 2, gameText.getPosition().y + window.getSize().y * 0.064f);

	devText.setFont(righteousFont);
	devText.setFillColor(sf::Color::White);
	devText.setCharacterSize(window.getSize().y * 0.044f);
	devText.setString("Developed & Programmed by: Harry Skerritt");
	devText.setOrigin(devText.getLocalBounds().width / 2, devText.getLocalBounds().height / 2);
	devText.setPosition(window.getSize().x / 2, ideaText.getPosition().y + window.getSize().y * 0.064f);

	//Audio Text
	audioText.setFont(righteousFont);
	audioText.setFillColor(blueColour);
	audioText.setCharacterSize(window.getSize().y * 0.059f);
	audioText.setString("Audio");
	audioText.setOrigin(audioText.getLocalBounds().width / 2, audioText.getLocalBounds().height / 2);
	audioText.setPosition(window.getSize().x * 0.23f, window.getSize().y * 0.43f);

	menuText.setFont(righteousFont);
	menuText.setFillColor(sf::Color::White);
	menuText.setCharacterSize(window.getSize().y * 0.044f);
	menuText.setString("Menu music from: Zapsplat");
	menuText.setOrigin(menuText.getLocalBounds().width / 2, menuText.getLocalBounds().height / 2);
	menuText.setPosition(audioText.getPosition().x, audioText.getPosition().y + window.getSize().y * 0.064f);

	otherText.setFont(righteousFont);
	otherText.setFillColor(sf::Color::White);
	otherText.setCharacterSize(window.getSize().y * 0.044f);
	otherText.setString("Other music form: Pixabay");
	otherText.setOrigin(otherText.getLocalBounds().width / 2, otherText.getLocalBounds().height / 2);
	otherText.setPosition(audioText.getPosition().x, menuText.getPosition().y + window.getSize().y * 0.064f);

	sfxText.setFont(righteousFont);
	sfxText.setFillColor(sf::Color::White);
	sfxText.setCharacterSize(window.getSize().y * 0.044f);
	sfxText.setString("Sound Effects form: Pixabay");
	sfxText.setOrigin(sfxText.getLocalBounds().width / 2, sfxText.getLocalBounds().height / 2);
	sfxText.setPosition(audioText.getPosition().x, otherText.getPosition().y + window.getSize().y * 0.064f);

	//Graphics Text
	graphicsText.setFont(righteousFont);
	graphicsText.setFillColor(blueColour);
	graphicsText.setCharacterSize(window.getSize().y * 0.059f);
	graphicsText.setString("Graphics");
	graphicsText.setOrigin(graphicsText.getLocalBounds().width / 2, graphicsText.getLocalBounds().height / 2);
	graphicsText.setPosition(window.getSize().x * 0.729f, window.getSize().y * 0.43f);

	motifText.setFont(righteousFont);
	motifText.setFillColor(sf::Color::White);
	motifText.setCharacterSize(window.getSize().y * 0.044f);
	motifText.setString("Card Motifs from: FlatIcon");
	motifText.setOrigin(motifText.getLocalBounds().width / 2, motifText.getLocalBounds().height / 2);
	motifText.setPosition(graphicsText.getPosition().x, graphicsText.getPosition().y + window.getSize().y * 0.064f);

	assetText.setFont(righteousFont);
	assetText.setFillColor(sf::Color::White);
	assetText.setCharacterSize(window.getSize().y * 0.044f);
	assetText.setString("Asset Creation: Harry Skerritt");
	assetText.setOrigin(assetText.getLocalBounds().width / 2, assetText.getLocalBounds().height / 2);
	assetText.setPosition(graphicsText.getPosition().x, motifText.getPosition().y + window.getSize().y * 0.064f);

	addAssetText.setFont(righteousFont);
	addAssetText.setFillColor(sf::Color::White);
	addAssetText.setCharacterSize(window.getSize().y * 0.044f);
	addAssetText.setString("Additional Asset Creation: Kate Maslen");
	addAssetText.setOrigin(addAssetText.getLocalBounds().width / 2, addAssetText.getLocalBounds().height / 2);
	addAssetText.setPosition(graphicsText.getPosition().x, assetText.getPosition().y + window.getSize().y * 0.064f);

	//Playtesting 
	playText.setFont(righteousFont);
	playText.setFillColor(blueColour);
	playText.setCharacterSize(window.getSize().y * 0.059f);
	playText.setString("Playe Testing");
	playText.setOrigin(playText.getLocalBounds().width / 2, playText.getLocalBounds().height / 2);
	playText.setPosition(window.getSize().x * 0.23f, window.getSize().y * 0.744f);

	pt1.setFont(righteousFont);
	pt1.setFillColor(sf::Color::White);
	pt1.setCharacterSize(window.getSize().y * 0.044f);
	pt1.setString("Harry Skerritt");
	pt1.setOrigin(pt1.getLocalBounds().width / 2, pt1.getLocalBounds().height / 2);
	pt1.setPosition(playText.getPosition().x, playText.getPosition().y + window.getSize().y * 0.064f);

	pt2.setFont(righteousFont);
	pt2.setFillColor(sf::Color::White);
	pt2.setCharacterSize(window.getSize().y * 0.044f);
	pt2.setString("Kate Maslen");
	pt2.setOrigin(pt2.getLocalBounds().width / 2, pt2.getLocalBounds().height / 2);
	pt2.setPosition(playText.getPosition().x, pt1.getPosition().y + window.getSize().y * 0.064f);

	pt3.setFont(righteousFont);
	pt3.setFillColor(sf::Color::White);
	pt3.setCharacterSize(window.getSize().y * 0.044f);
	pt3.setString("Samuel West");
	pt3.setOrigin(pt3.getLocalBounds().width / 2, pt3.getLocalBounds().height / 2);
	pt3.setPosition(playText.getPosition().x, pt2.getPosition().y + window.getSize().y * 0.064f);

	//Questions
	questionText.setFont(righteousFont);
	questionText.setFillColor(blueColour);
	questionText.setCharacterSize(window.getSize().y * 0.059f);
	questionText.setString("Question Writing");
	questionText.setOrigin(questionText.getLocalBounds().width / 2, questionText.getLocalBounds().height / 2);
	questionText.setPosition(window.getSize().x * 0.729f, window.getSize().y * 0.744f);

	q1.setFont(righteousFont);
	q1.setFillColor(sf::Color::White);
	q1.setCharacterSize(window.getSize().y * 0.044f);
	q1.setString("Harry Skerritt");
	q1.setOrigin(q1.getLocalBounds().width / 2, q1.getLocalBounds().height / 2);
	q1.setPosition(questionText.getPosition().x, questionText.getPosition().y + window.getSize().y * 0.064f);

	q2.setFont(righteousFont);
	q2.setFillColor(sf::Color::White);
	q2.setCharacterSize(window.getSize().y * 0.044f);
	q2.setString("Kate Maslen");
	q2.setOrigin(q2.getLocalBounds().width / 2, q2.getLocalBounds().height / 2);
	q2.setPosition(questionText.getPosition().x, q1.getPosition().y + window.getSize().y * 0.064f);

	q3.setFont(righteousFont);
	q3.setFillColor(sf::Color::White);
	q3.setCharacterSize(window.getSize().y * 0.044f);
	q3.setString("-");
	q3.setOrigin(q3.getLocalBounds().width / 2, q3.getLocalBounds().height / 2);
	q3.setPosition(questionText.getPosition().x, q2.getPosition().y + window.getSize().y * 0.064f);

	//View more button
	viewMoreButton.setBackgroundImage(m_game->buttonRectTexture);
	viewMoreButton.setBackgroundScale(m_game->scaleX * 0.4f, m_game->scaleX * 0.4f);
	viewMoreButton.setText("View More", righteousFont, window.getSize().y * 0.0416f);
	viewMoreButton.setTextColor(m_game->buttonNormalColour);
	viewMoreButton.setHoverColor(m_game->buttonHoverColour);
	viewMoreButton.setPosition(window.getSize().x / 2 - viewMoreButton.getGlobalBounds().width /2 , window.getSize().y * 0.89f);

}

void CreditsScreen::update(sf::Vector2f clickPos) {
	backButton.handleHover(clickPos);
	viewMoreButton.handleHover(clickPos);
}

void CreditsScreen::handleMouse(sf::Vector2f clickPos) {
	if (backButton.isClicked(clickPos)) {
		m_game->backToMainMenu(4);
	}

	if (viewMoreButton.isClicked(clickPos)) {
		openLink(m_game->CREDIT_URL);
	}
}

void CreditsScreen::draw(sf::RenderWindow& window) {
	GradientBackground::setBackgroundGradient(window);
	backButton.draw(window);
	window.draw(creditText);

	//The Game
	window.draw(gameText);
	window.draw(ideaText);
	window.draw(devText);

	//Audio
	window.draw(audioText);
	window.draw(menuText);
	window.draw(otherText);
	window.draw(sfxText);

	//Graphics
	window.draw(graphicsText);
	window.draw(motifText);
	window.draw(assetText);
	window.draw(addAssetText);

	//Play Testing
	window.draw(playText);
	window.draw(pt1);
	window.draw(pt2);
	window.draw(pt3);

	//Questions
	window.draw(questionText);
	window.draw(q1);
	window.draw(q2);
	window.draw(q3);

	//VM
	viewMoreButton.draw(window);

}

void CreditsScreen::openLink(const std::string& url) {
	#ifdef _WIN32
		system(("start " + url).c_str());
	#elif __APPLE__
		system(("open " + url).c_str());
	#elif __linux__
		system(("xdg-open " + url).c_str());
	#else
		std::cerr << "Unsupported OS" << std::endl;
	#endif
}