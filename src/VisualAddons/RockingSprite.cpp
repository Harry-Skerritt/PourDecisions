#include "RockingSprite.h"
#include <iostream>
#include <cmath>

RockingSprite::RockingSprite()
    : isRocking(false), angle(0.0f), rockingSpeed(35.0f), rockingDuration(2.0f), elapsedTime(0.0f) {
}

void RockingSprite::init(const sf::Texture& texture, sf::RenderWindow& window) {
    sprite.setTexture(texture);

    scale = 0.f;

    sprite.setScale(scale, scale);

    // Set the sprite position to the center of the screen
    originalPosition = sf::Vector2f(window.getSize().x / 2.f, window.getSize().y / 2.f);
    sprite.setPosition(originalPosition);

    // Set the origin of the sprite to its center for smooth rotation
    sprite.setOrigin(texture.getSize().x / 2.f, texture.getSize().y / 2.f);
}

void RockingSprite::startRocking() {
    isRocking = true;
    elapsedTime = 0.0f;  // Reset elapsed time
    sprite.setColor(sf::Color::White);
}

void RockingSprite::update(float dt) {
    if (!isRocking) {
        return;
    }

    // Increment elapsed time
    elapsedTime += dt;

    // Scale the sprite gradually from 1.1x (10% bigger) to its original size
    float scaleFactor = 0.9f - (elapsedTime / rockingDuration) * 0.9f; // Shrink by 10% over the duration
    sprite.setScale(scaleFactor, scaleFactor);

    // Slow down the rocking speed by reducing it over time
    float speedFactor = 1.0f - (elapsedTime / rockingDuration) * 0.5f; // Reduce speed by 50% over duration
    float currentRockingSpeed = rockingSpeed * speedFactor;

    // If we've completed the rocking duration, stop the animation
    if (elapsedTime >= rockingDuration) {
        isRocking = false;
        elapsedTime = 0.0f;
        angle = 0.0f;
        sprite.setRotation(angle); // Ensure the sprite ends with a rotation of 0 degrees
        sprite.setColor(sf::Color::Transparent);
    }
    else {
        // Rock the sprite back and forth using sine wave between -12 and 12 degrees
        angle = 20.0f * sin(currentRockingSpeed * elapsedTime);
        sprite.setRotation(angle);
    }
}

void RockingSprite::draw(sf::RenderWindow& window) {
    window.draw(sprite);
}
