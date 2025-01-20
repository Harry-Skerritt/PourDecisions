#include "Confetti.h"
#include <cstdlib>
#include <ctime>

// Confetti constructor
Confetti::Confetti(float x, float y) {
    // Choose random shape: circle or rectangle
    if (randomBool()) {
        auto* circle = new sf::CircleShape(5.f);  // Circle with radius 5
        circle->setFillColor(randomColor());
        circle->setPosition(x, y);
        shape = circle;
    }
    else {
        auto* rectangle = new sf::RectangleShape(sf::Vector2f(10.f, 10.f));  // Rectangle 10x5
        rectangle->setFillColor(randomColor());
        rectangle->setPosition(x, y);
        shape = rectangle;
    }

    // Random velocity
    velocity.x = (rand() % 5 - 2) * 0.5f;  // Small horizontal drift
    velocity.y = (rand() % 3 + 1) * 0.5f;  // Slow vertical speed
}

// Update position of the confetti
void Confetti::update() {
    shape->move(velocity);
}

// Return reference to shape for drawing
const sf::Shape& Confetti::getShape() const {
    return *shape;
}

// Generate a random color
sf::Color Confetti::randomColor() {
    switch (rand() % 3) {
    case 0: return sf::Color(0, 238, 255, 255);
    case 1: return sf::Color(255, 0, 208, 255);
    case 2: return sf::Color(255, 149, 0, 255);
    default: return sf::Color::White;  // Shouldn't occur
    }
}

// Helper to randomly decide between circle or rectangle
bool Confetti::randomBool() {
    return rand() % 2 == 0;
}

// ConfettiManager constructor
ConfettiManager::ConfettiManager() {
    srand(static_cast<unsigned int>(time(0)));  // Seed random number generator
}

// Add new confetti at random positions
void ConfettiManager::addConfetti(sf::RenderWindow& window) {
    if (rand() % 5 == 0) {  // 1 in 5 chance to add a new confetti
        float x = static_cast<float>(rand() % window.getSize().x);
        confettiList.emplace_back(x, 0.f);
    }
}

// Update all confetti
void ConfettiManager::update(sf::RenderWindow& window) {
    addConfetti(window);

    for (auto& confetti : confettiList) {
        confetti.update();
    }

    // Remove confetti that has fallen out of the screen
    confettiList.erase(std::remove_if(confettiList.begin(), confettiList.end(),
        [&](const Confetti& c) { return c.getShape().getPosition().y > window.getSize().y; }),
        confettiList.end());
}

// Draw all confetti
void ConfettiManager::draw(sf::RenderWindow& window) {
    for (const auto& confetti : confettiList) {
        window.draw(confetti.getShape());
    }
}