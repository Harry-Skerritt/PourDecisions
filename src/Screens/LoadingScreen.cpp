#include "LoadingScreen.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <random>
#include "../Utils/GradientBackground.h"

LoadingScreen::LoadingScreen(sf::RenderWindow& window, const std::string& spriteTexturePath, const std::vector<std::string>& messages)
    : m_window(window), m_loadingMessages(messages), m_currentMessageIndex(0), m_loadingProgress(0.f), m_isBarGrowing(true), m_loadingComplete(false) {

    // Debug: Check the vector size
    std::cout << "Number of loading messages: " << m_loadingMessages.size() << std::endl;

    // Load sprite texture
    if (!m_spriteTexture.loadFromFile(spriteTexturePath)) {
        std::cerr << "Error loading texture file: " << spriteTexturePath << std::endl;
    }

    float scaleX = static_cast<float>(window.getSize().x) / 1080.0f;
    m_sprite.setTexture(m_spriteTexture);
    m_sprite.setScale(scaleX * 0.3f, scaleX * 0.3f);
    m_sprite.setPosition(window.getSize().x / 2 - m_sprite.getGlobalBounds().width / 2, window.getSize().y * 0.067f);

    // Load font for text
    if (!m_font.loadFromFile("../Data/Fonts/Righteous-Regular.ttf")) {
        std::cerr << "Error loading font file." << std::endl;
    }

    m_messageText.setFont(m_font);
    m_messageText.setCharacterSize(window.getSize().y * 0.037f);
    m_messageText.setFillColor(sf::Color::White);
    m_messageText.setPosition(window.getSize().x * 0.416f, window.getSize().y * 0.774f);


    // Set up loading bar
    m_loadingBarBorder.setSize(sf::Vector2f(window.getSize().x * 0.36f, window.getSize().y * 0.05f));
    m_loadingBarBorder.setFillColor(sf::Color(185, 0, 102, 255));
    m_loadingBarBorder.setOrigin(m_loadingBarBorder.getLocalBounds().width / 2, m_loadingBarBorder.getLocalBounds().height / 2);
    m_loadingBarBorder.setPosition(window.getSize().x / 2, window.getSize().y - window.getSize().y * 0.136f);

    m_loadingBar.setSize(sf::Vector2f(m_loadingBarBorder.getSize().x * 0.98f, m_loadingBarBorder.getSize().y * 0.81f));
    m_loadingBar.setFillColor(sf::Color(0, 219, 252, 255));
    m_loadingBar.setPosition(m_loadingBarBorder.getPosition().x - m_loadingBarBorder.getGlobalBounds().width / 2 + 5, m_loadingBarBorder.getPosition().y - m_loadingBarBorder.getGlobalBounds().height / 2 + 5);

    // Prepare callback storage
    m_callbacks.resize(messages.size());
}

void LoadingScreen::setMessageCallback(int index, const std::function<bool()>& callback) {
    if (index >= 0 && index < m_callbacks.size()) {
        m_callbacks[index] = callback;
    }
}

void LoadingScreen::update(float deltaTime) {
    if (m_loadingComplete) return;

    // Debug: Print current loading index
    std::cout << "Current loading index: " << m_currentMessageIndex << std::endl;

    // Execute the current loading message callback
    if (m_callbacks[m_currentMessageIndex]()) {
        // If the current task completes, move to the next message
        m_currentMessageIndex++;

        // Ensure index stays within bounds
        if (m_currentMessageIndex >= m_loadingMessages.size()) {
            m_currentMessageIndex = m_loadingMessages.size() - 1;  // Set to last message
            m_loadingComplete = true;  // Mark loading as complete
            std::cout << "Loading complete!" << std::endl;
        }

        m_loadingProgress = 0.f; // Reset the loading bar for the next message
    }

    // Update loading bar progress
    updateLoadingBar();
}

void LoadingScreen::updateLoadingBar() {
    if (m_isBarGrowing) {
        m_loadingProgress += (rand() % 10 + 1) * 0.01f;  // Random progress between 1% and 10%
        if (m_loadingProgress >= 1.f) {
            m_loadingProgress = 1.f;
            m_isBarGrowing = false;
        }
    }
    else {
        // Shrinking the bar or idle state after reaching 100%
        if (m_loadingProgress >= 1.f && m_currentMessageIndex == m_loadingMessages.size()) {
            m_loadingComplete = true;  // Set loading complete once all tasks are done
        }

        if (m_loadingProgress > 0.f) {
            m_loadingProgress -= 0.02f;  // Gradually shrink the bar to simulate next progress
        }
    }
}

void LoadingScreen::drawLoadingBar() {
    sf::Vector2f loadingSize = sf::Vector2f(m_loadingBarBorder.getSize().x * 0.98f, m_loadingBarBorder.getSize().y * 0.81f);
    m_loadingBar.setSize(sf::Vector2f(loadingSize.x * m_loadingProgress, loadingSize.y));
    m_window.draw(m_loadingBarBorder);
    m_window.draw(m_loadingBar);
}

void LoadingScreen::render() {
    // Draw the gradient background
    GradientBackground::setBackgroundGradient(m_window);

    // Draw the sprite
    m_window.draw(m_sprite);

    // Display the current loading message
    if (m_currentMessageIndex < m_loadingMessages.size()) {
        m_messageText.setString(m_loadingMessages[m_currentMessageIndex]);
    }

    m_window.draw(m_messageText);

    // Draw the loading bar
    drawLoadingBar();

    // Display everything
    m_window.display();
}

bool LoadingScreen::isLoadingComplete() const {
    return m_loadingComplete;
}
