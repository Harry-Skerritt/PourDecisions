#ifndef GROWFADETEXT_H
#define GROWFADETEXT_H

#include <SFML/Graphics.hpp>
#include <string>

class GrowFadeText {
public:
    GrowFadeText();

    // Initialize the text effect
    void init(const sf::Font& font, float duration, float charSize = 50);

    // Reset the effect with new text and color
    void reset(const std::string& text, sf::Color color, float angle, const sf::Vector2f& position);

    // Start the effect
    void go();

    // Update the effect over time
    void update(float dt);

    // Draw the text effect
    void draw(sf::RenderWindow& window);

    // Check if the effect is finished
    bool isFinished() const;

private:
    sf::Text m_text;
    sf::Color m_initialColor;
    sf::Color m_finalColor;
    float m_angle;
    float m_duration;
    float m_elapsedTime;
    float m_scaleFactor;
    float m_charSize;
    bool m_finished;
};

#endif // GROWFADETEXT_H
