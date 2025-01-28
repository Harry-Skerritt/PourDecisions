#ifndef SPINWHEEL_H
#define SPINWHEEL_H

#include <SFML/Graphics.hpp>
#include <cmath>
#include <functional>
#include <iostream>
#include "../Managers/AudioManager.h"

class SpinWheel {
private:
    sf::Sprite m_wheelSprite;       // Wheel sprite
    float m_currentRotation = 0.f;  // Tracks the current rotation of the wheel
    float m_initialRotation = 0.f;  // Tracks the initial rotation (starting position)
    float m_targetRotation = 0.f;   // Target rotation to reach
    float m_rotationSpeed = 0.f;    // Current speed of rotation
    bool m_isSpinning = false;      // Indicates whether the wheel is spinning
    bool m_callbackCalled = false;  // Ensures callback is only called once
    std::function<void()> m_onSpinComplete;  // Callback for when the spin completes
    int m_previousCategory = -1;    // Tracks the last category passed to avoid repeated sound plays
    float m_minRoationSpeed;
    float m_segments;

public:
    SpinWheel() {}

    void setSprite(const sf::Sprite& sprite) {
        m_wheelSprite = sprite;
        m_wheelSprite.setOrigin(sprite.getTexture()->getSize().x / 2.f, sprite.getTexture()->getSize().y / 2.f); // Set the origin to the center of the wheel
        m_initialRotation = m_currentRotation; // Store the initial rotation
    }

    void setOnSpinCompleteCallback(std::function<void()> callback) {
        m_onSpinComplete = callback;
    }

    // Spin to a category, spinning n full rotations and stopping at the target category
    void spinToCategory(int targetCategory, int spinCount, float spinSpeed, float segments) {
        if (m_isSpinning) return; // Prevent starting another spin while already spinning

        m_segments = segments;
        const float segmentAngle = 360.f / m_segments;  // 8 segments on the wheel
        const float targetAngle = targetCategory * segmentAngle; // Angle of the target category

        // Calculate the total rotation needed to spin the desired number of times plus the target angle
        float fullRotation = spinCount * 360.f; // Number of full spins
        m_targetRotation = m_initialRotation - fullRotation - targetAngle; // Negative for anticlockwise

        // Normalize the target rotation to 0–360 range
        m_targetRotation = std::fmod(m_targetRotation, 360.f);
        if (m_targetRotation < 0) m_targetRotation += 360.f;

        // Set up the initial rotation speed
        m_rotationSpeed = spinSpeed;  // Initial rotation speed
        m_minRoationSpeed = spinSpeed / 10.0f;
        m_isSpinning = true;
        m_callbackCalled = false; // Reset callback flag
        
    }

    void update(float deltaTime) {
        if (m_isSpinning) {
            // Rotate by the speed * deltaTime (rotation per frame)
            float rotationStep = m_rotationSpeed * deltaTime;
            m_currentRotation -= rotationStep; // Subtract for anticlockwise rotation

            // Normalize current rotation to keep it in the 0–360 range
            m_currentRotation = std::fmod(m_currentRotation, 360.f);
            if (m_currentRotation < 0) m_currentRotation += 360.f;

            // Gradually decelerate the wheel's speed
            if (m_rotationSpeed > m_minRoationSpeed) {
                m_rotationSpeed -= m_minRoationSpeed * deltaTime; // Slow down over time
            }
            else {
                m_rotationSpeed = m_minRoationSpeed; // Set a minimum speed to stop smoothly
            }

            // Play sound when passing a category boundary
            int currentCategory = static_cast<int>(m_currentRotation / (360.f / m_segments)); 
            if (currentCategory != m_previousCategory) {
                if (m_previousCategory != -1) { // Skip the first category
                    AudioManager::getInstance().playSoundEffect("wheelClick"); // Play sound on category pass
                }
                m_previousCategory = currentCategory; // Update the previous category
            }

            // Update the sprite's rotation
            m_wheelSprite.setRotation(m_currentRotation);

            // Check if the wheel is close enough to the target and speed is slow enough to stop
            if (std::abs(m_targetRotation - m_currentRotation) < 1.f && m_rotationSpeed <= m_minRoationSpeed) {
                // Snap to the exact target angle to avoid floating point issues
                m_currentRotation = m_targetRotation;
                m_wheelSprite.setRotation(m_currentRotation);
                m_isSpinning = false; // Stop the spinning

                // Call the callback only once when the wheel has stopped
                if (!m_callbackCalled && m_onSpinComplete) {
                    m_callbackCalled = true;
                    m_onSpinComplete();
                }
            }
        }
    }

    void draw(sf::RenderWindow& window) {
        window.draw(m_wheelSprite);
    }

    bool isSpinning() const {
        return m_isSpinning;
    }
};



#endif //SPINWHEEL_H