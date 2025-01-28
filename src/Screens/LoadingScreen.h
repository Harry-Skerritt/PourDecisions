#ifndef LOADINGSCREEN_H
#define LOADINGSCREEN_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <functional>

class LoadingScreen {
public:
    LoadingScreen(sf::RenderWindow& window, const std::string& spriteTexturePath, const std::vector<std::string>& messages);
    void update(float deltaTime);
    void render();
    bool isLoadingComplete() const;

    // Set callback functions for each message
    void setMessageCallback(int index, const std::function<bool()>& callback);

private:
    sf::RenderWindow& m_window;
    sf::Texture m_spriteTexture;
    sf::Sprite m_sprite;

    std::vector<std::string> m_loadingMessages;
    std::vector<std::function<bool()>> m_callbacks;

    int m_currentMessageIndex;
    bool m_loadingComplete;

    sf::Font m_font;
    sf::Text m_messageText;

    sf::RectangleShape m_loadingBarBorder;
    sf::RectangleShape m_loadingBar;

    float m_loadingProgress;
    bool m_isBarGrowing;

    void updateLoadingBar();
    void drawLoadingBar();
};

#endif // LOADINGSCREEN_H
