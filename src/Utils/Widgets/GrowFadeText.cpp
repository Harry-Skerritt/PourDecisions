#include "GrowFadeText.h"

GrowFadeText::GrowFadeText()
    : m_angle(0.0f), m_duration(1.0f), m_elapsedTime(0.0f), m_scaleFactor(1.0f), m_finished(true) {}

void GrowFadeText::init(const sf::Font& font, float duration, float charSize) {
    m_text.setFont(font);
    m_duration = duration;
    m_elapsedTime = 0.0f;
    m_finished = true;
    m_charSize = charSize;
}

void GrowFadeText::reset(const std::string& text, sf::Color color, float angle, const sf::Vector2f& position) {
    m_text.setString(text);
    m_text.setCharacterSize(m_charSize);
    m_text.setPosition(position);
    m_text.setOrigin(m_text.getGlobalBounds().width / 2, m_text.getGlobalBounds().height / 2);
    m_text.setRotation(angle);

    m_initialColor = color;
    m_finalColor = sf::Color(color.r, color.g, color.b, 0); // Fade to transparent
    m_angle = angle;

    m_text.setFillColor(m_initialColor);
    m_scaleFactor = 1.0f;
    m_elapsedTime = 0.0f;
    m_finished = true; // Reset the effect
}

void GrowFadeText::go() {
    m_elapsedTime = 0.0f;
    m_finished = false;
}

void GrowFadeText::update(float dt) {
    if (m_finished) return;

    m_elapsedTime += dt;

    if (m_elapsedTime >= m_duration) {
        m_finished = true;
        return;
    }

    // Calculate progress (0.0 to 1.0)
    float progress = m_elapsedTime / m_duration;

    // Scale the text (grows)
    m_scaleFactor = 1.0f + progress; // Grows smoothly
    m_text.setScale(m_scaleFactor, m_scaleFactor);

    // Interpolate color (fades out)
    m_text.setFillColor(sf::Color(
        static_cast<sf::Uint8>(m_initialColor.r + (m_finalColor.r - m_initialColor.r) * progress),
        static_cast<sf::Uint8>(m_initialColor.g + (m_finalColor.g - m_initialColor.g) * progress),
        static_cast<sf::Uint8>(m_initialColor.b + (m_finalColor.b - m_initialColor.b) * progress),
        static_cast<sf::Uint8>(m_initialColor.a + (m_finalColor.a - m_initialColor.a) * progress)
    ));
}

void GrowFadeText::draw(sf::RenderWindow& window) {
    if (!m_finished) {
        window.draw(m_text);
    }
}

bool GrowFadeText::isFinished() const {
    return m_finished;
}
