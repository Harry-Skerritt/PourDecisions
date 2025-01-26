#include "ForfeitScreen.h"
#include "../Game.h"
#include "MainGame.h"

ForfeitScreen::ForfeitScreen(sf::RenderWindow& window, sf::Font& font1, sf::Font& font2, sf::Font& font3) : window(window), righteousFont(font1), ryeFont(font2), lcdFont(font3) {};
ForfeitScreen::~ForfeitScreen() {};

void ForfeitScreen::setGameInstance(Game* game) {
	this->m_game = game;
}

void ForfeitScreen::setMainGameInstance(MainGame* mainGame) {
	this->m_mainGame = mainGame;
}

void ForfeitScreen::init(std::string playerName, int playerPoints, bool groupCard) {
	isVisible = false;
	group = groupCard;

	//Forfeit Sign
	forfeitSign.setTexture(m_game->forfeitTexture);
	forfeitSign.setScale(m_game->scaleX * 0.3f, m_game->scaleX * 0.3f);
	forfeitSign.setRotation(-12.0f);
	forfeitSign.setPosition(window.getSize().x * 0.22f - forfeitSign.getGlobalBounds().width/2, window.getSize().y * 0.175f);

	//Forfeit Player
	forfeitPlayer.initialise(playerName, righteousFont, lcdFont, window.getSize().x * 0.037f, window.getSize().y / 2,
		window.getSize().x * 0.31f, window.getSize().y * 0.11f, playerPoints);
	forfeitPlayer.setSelected(true);

	spinButton.setBackgroundImage(m_game->buttonRectTexture);
	spinButton.setBackgroundScale(m_game->scaleX * 0.45f, m_game->scaleX * 0.45f);
	spinButton.setHoverColor(m_game->buttonHoverColour);
	spinButton.setTextColor(m_game->buttonNormalColour);
	spinButton.setOrigin(spinButton.getLocalBounds().width / 2, spinButton.getLocalBounds().height / 2);
	spinButton.setText("SPIN", ryeFont, window.getSize().y * 0.088f);
	spinButton.setPosition(forfeitPlayer.getPosition().x + forfeitPlayer.getGlobalBounds().width / 2, forfeitPlayer.getPosition().y + window.getSize().y * 0.27f);

	if (!forfeitWheelTexture.loadFromFile("../Data/Assets/Wheels/forfeitWheel.png")) {
		std::cout << "Forfeit wheel failed to load";
	}

	forfeitWheelSprite.setTexture(forfeitWheelTexture);
	forfeitWheelSprite.setScale(m_game->scaleX * 0.55f, m_game->scaleX * 0.55f);
	forfeitWheelSprite.setOrigin(forfeitWheelSprite.getLocalBounds().width / 2, forfeitWheelSprite.getLocalBounds().height / 2);
	forfeitWheelSprite.setPosition(window.getSize().x - window.getSize().x * 0.267f, window.getSize().y / 2);

	std::cout << "Passed spin wheel sprite setup" << std::endl; //DEBUG

	forfeitSpinner.setSprite(forfeitWheelSprite);

	forfeitSpinner.setOnSpinCompleteCallback([this]() {
		std::cout << "CALLBACK!!!" << std::endl;
		std::cout << "Forfiet Spin Complete!" << std::endl;
		setVisible(false);
		m_mainGame->setForfeitCardVisible(true);
		});

	std::cout << "Passed spinner setup" << std::endl; //DEBUG

	spinWheelClicker.setTexture(m_mainGame->spinWheelClickerTexture);
	spinWheelClicker.setScale(m_game->scaleX * 0.55f, m_game->scaleX * 0.55f);
	spinWheelClicker.setOrigin(spinWheelClicker.getLocalBounds().left, spinWheelClicker.getLocalBounds().height / 2);
	spinWheelClicker.setPosition(window.getSize().x / 2 - spinWheelClicker.getGlobalBounds().width + window.getSize().x * 0.026f, window.getSize().y / 2);

}

void ForfeitScreen::chooseForfeitCard() {
	int amountOfForfeits = m_game->forfeitQuantity;

	//Check if all the cards are used, if so reset the cards and allow to be used again
	if (m_game->usedForfeits.size() == amountOfForfeits) {
		m_game->usedForfeits.clear();
	}

	bool nonUsedForfeit = false;
	int chosenForfeit;

	while(!nonUsedForfeit) {
		chosenForfeit = rand() % amountOfForfeits; //0 - max (15)

		int count = std::count(m_game->usedForfeits.begin(), m_game->usedForfeits.end(), chosenForfeit);

		if (count > 0) {
			//Card used
			nonUsedForfeit = false;
		}
		else {
			//Card not used
			nonUsedForfeit = true;
			m_game->usedForfeits.push_back(chosenForfeit);
			break;
		}
	}

	std::string forfeitTitle = m_game->forfeitTitles.at(chosenForfeit);
	std::string forfeitBody = m_game->forfeitCards.at(chosenForfeit);
	std::string forfeitMotif = m_game->forfeitMotifNames.at(chosenForfeit);

	m_mainGame->initForfeitCard(forfeitTitle, forfeitBody, forfeitMotif, group); //Init the card
	
	if (!forfeitSpinner.isSpinning()) {
		forfeitSpinner.spinToCategory(chosenForfeit, 1, 500.f, 15.f);
	}
	
}

void ForfeitScreen::update(float dt, sf::Vector2f clickPos) {
	spinButton.handleHover(clickPos);
	forfeitSpinner.update(dt);
}

void ForfeitScreen::handleMouse(sf::Vector2f clickPos) {
	if (spinButton.isClicked(clickPos)) {
		chooseForfeitCard();
	}

	
}

bool ForfeitScreen::getVisible() {
	return isVisible;
}

void ForfeitScreen::setVisible(bool state) {
	isVisible = state;
}

void ForfeitScreen::handleKeypress(sf::Event event) {
	//Make this work
	if (isVisible) {
		if (event.key.code == sf::Keyboard::Escape) {
			m_mainGame->menu_visible = m_mainGame->pauseMenu.getVisible();
			m_mainGame->menu_visible = !m_mainGame->menu_visible;
			m_mainGame->pauseMenu.showMenu(m_mainGame->menu_visible);
		}
	}
	
}

void ForfeitScreen::draw(sf::RenderWindow& window) {
	if (isVisible) {
		GradientBackground::setBackgroundGradient(window);
		window.draw(forfeitSign);
		forfeitPlayer.draw(window);
		spinButton.draw(window);

		forfeitSpinner.draw(window);
		window.draw(spinWheelClicker);
	}
}
