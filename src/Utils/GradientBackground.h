#ifndef GRADIENT_BACKGROUND_H
#define GRADIENT_BACKGROUND_H

#include <SFML/Graphics.hpp>

class GradientBackground {
public:
    static void setBackgroundGradient(sf::RenderWindow& window,
        const sf::Color& topColor = sf::Color(42, 3, 60, 255),
        const sf::Color& bottomColor = sf::Color(254, 0, 190, 255));
};

#endif // GRADIENT_BACKGROUND_H
