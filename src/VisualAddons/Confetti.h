#ifndef CONFETTI_H
#define CONFETTI_H

#include <SFML/Graphics.hpp>
#include <vector>

class Confetti {
public:
    Confetti(float x, float y);
    void update();
    const sf::Shape& getShape() const;

private:
    sf::Shape* shape;
    sf::Vector2f velocity;

    static sf::Color randomColor();
    static bool randomBool();  // Helper to decide between circle or rectangle
};

class ConfettiManager {
public:
    ConfettiManager();
    void update(sf::RenderWindow& window);
    void draw(sf::RenderWindow& window);

private:
    std::vector<Confetti> confettiList;

    void addConfetti(sf::RenderWindow& window);
};

#endif // CONFETTI_H