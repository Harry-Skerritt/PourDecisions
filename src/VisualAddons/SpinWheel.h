#ifndef SPINWHEEL_H
#define SPINWHEEL_H

#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <ctime>

class SpinWheel {
public:
    SpinWheel();
    void init(const sf::Texture& texture, const sf::Vector2f& position, float radius);
    void spin();
    void update(float dt);
    void draw(sf::RenderWindow& window);
    int getResult() const;

private:
    sf::Sprite wheelSprite;
    sf::Vector2f position;
    float radius;
    int result;             // The result the wheel lands on (0-7)
    bool isSpinning;       // Whether the wheel is currently spinning
    float rotationSpeed;   // How fast the wheel is spinning
    float elapsedTime;     // Time since the spin started
    float spinDuration;    // Duration of the spin in seconds
    float targetRotation;  // The final angle at which the wheel should stop
    float currentRotation; // The current rotation of the wheel, allowing continuous spinning

    void setRandomSpinDuration();
    int getRandomResult() const;
    void calculateTargetRotation();
};

#endif
