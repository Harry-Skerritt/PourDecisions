#include "SpinWheel.h"

SpinWheel::SpinWheel()
    : result(0), isSpinning(false), rotationSpeed(0.0f), elapsedTime(0.0f), spinDuration(0.0f), targetRotation(0.0f), currentRotation(0.0f) {
    std::srand(static_cast<unsigned>(std::time(0))); // Seed for random number generation
}

void SpinWheel::init(const sf::Texture& texture, const sf::Vector2f& position, float radius) {
    wheelSprite.setTexture(texture);
    this->position = position;
    this->radius = radius;
    wheelSprite.setOrigin(texture.getSize().x / 2.f, texture.getSize().y / 2.f);  // Set the origin to the center
    wheelSprite.setPosition(position);
    wheelSprite.setScale(0.5f, 0.5f);
}

void SpinWheel::spin() {
    if (isSpinning) return;  // Prevent multiple spins at once
    isSpinning = true;
    result = getRandomResult();  // Pick a random result
    calculateTargetRotation();    // Calculate the rotation angle the wheel should land on
    setRandomSpinDuration();      // Set a random duration for the spin
    elapsedTime = 0.0f;           // Reset elapsed time
    rotationSpeed = 3600.0f;       // Start with a full rotation per second
    currentRotation = wheelSprite.getRotation();  // Track the current rotation angle
}

void SpinWheel::update(float dt) {
    if (!isSpinning) return;

    elapsedTime += dt;

    // Spin the wheel
    currentRotation += rotationSpeed * dt;  // Increment the current rotation by speed*time
    wheelSprite.setRotation(currentRotation);  // Apply the current rotation

    // Slow down the spin over time
    rotationSpeed = rotationSpeed * 0.98f;  // Decrease speed by 2% each frame

    // Smooth deceleration: if the wheel is near its target, slow it down further
    if (elapsedTime >= spinDuration * 0.8f) {
        rotationSpeed *= 0.98f;  // Decelerate more strongly as we approach the target
    }

    // Stop spinning after the duration and set the final rotation
    if (elapsedTime >= spinDuration) {
        isSpinning = false;
        wheelSprite.setRotation(targetRotation);  // Set the final target rotation
    }
}

void SpinWheel::draw(sf::RenderWindow& window) {
    window.draw(wheelSprite);
}

int SpinWheel::getResult() const {
    return result;  // Return the result (0-7)
}

void SpinWheel::setRandomSpinDuration() {
    // Random duration between 2 and 5 seconds for the spin
    //spinDuration = 4.0f + std::rand() % 8;  // 2-5 seconds
    spinDuration = 6.0f;
}

int SpinWheel::getRandomResult() const {
    // Pick a random index (0 to 7)
    return std::rand() % 8;
}

void SpinWheel::calculateTargetRotation() {
    // Each segment of the wheel is 45 degrees (360 / 8 = 45)
    targetRotation = 45.0f * result + (360.0f * 100);  // Spin extra 10 full rotations for effect
}
