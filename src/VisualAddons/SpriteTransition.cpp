#include "SpriteTransition.h"

SpriteTransition::SpriteTransition() {
    
}

void SpriteTransition::init(const sf::Texture& texture, float durationIn)
{
    sprite.setTexture(texture);
    duration = durationIn;
    elapsedTime = 0;
    transitionComplete = false;

    // Set the sprite's origin to the center so it rotates around the middle
    sprite.setOrigin(sprite.getGlobalBounds().width / 2, sprite.getGlobalBounds().height / 2);

    // Set the initial scale to be very small
    sprite.setScale(0.1f, 0.1f);  // Start small (0.1 size)

    

    // Set the sprite's initial position to the center of the window
    sprite.setPosition(540, 360);  //Make dynamic as currently hardcoded for 1080x720
}

void SpriteTransition::update(float deltaTime) {
    if (transitionComplete) return;

    // Increment the elapsed time
    elapsedTime += deltaTime;

    // Calculate the progress (normalized value between 0 and 1)
    float progress = elapsedTime / duration;

    if (progress >= 2.0f) {
        progress = 2.0f;
        transitionComplete = true;
    }

    // Grow the sprite: scale from 0.1 to 1 (or maximum size)
    float scale = 0.1f + progress * (2.0f - 0.1f);  // Grow from 0.1 to 2
    sprite.setScale(scale, scale);

    // Spin the sprite: rotate from 0 to 360 degrees
    sprite.setRotation(progress * 360.0f);  // Rotate over time

    // Transition the sprite's color to black after it grows
    if (progress >= 2.0f) {
        sprite.setColor(sf::Color::Transparent);  // Turn the sprite transparent
    }
}

void SpriteTransition::render(sf::RenderWindow& window) {
    if (!transitionComplete) {
        window.draw(sprite);
    }
}

bool SpriteTransition::isComplete() const {
    return transitionComplete;
}

void SpriteTransition::reset() {
    elapsedTime = 0;
    transitionComplete = false;

    // Restore the initial scale
    sprite.setScale(0.1f, 0.1f);  // Start small

    // Restore the initial rotation
    sprite.setRotation(0.0f);  // Reset rotation

    // Restore the initial color to fully visible
    sprite.setColor(sf::Color::White);  // Reset to default visible state
}
