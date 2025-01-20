#include "GradientBackground.h"

void GradientBackground::setBackgroundGradient(sf::RenderWindow& window,
    const sf::Color& topColor,
    const sf::Color& bottomColor)
{
    sf::VertexArray background(sf::Quads, 4);

    background[0].position = sf::Vector2f(0, 0);
    background[1].position = sf::Vector2f(window.getSize().x, 0);
    background[2].position = sf::Vector2f(window.getSize().x, window.getSize().y);
    background[3].position = sf::Vector2f(0, window.getSize().y);

    for (int i = 0; i < 4; i++) {
        float factor = static_cast<float>(background[i].position.y) / static_cast<float>(window.getSize().y);

        background[i].color = sf::Color(
            static_cast<sf::Uint8>((1.0f - factor) * topColor.r + factor * bottomColor.r),
            static_cast<sf::Uint8>((1.0f - factor) * topColor.g + factor * bottomColor.g),
            static_cast<sf::Uint8>((1.0f - factor) * topColor.b + factor * bottomColor.b)
        );
    }

    window.draw(background);
}
