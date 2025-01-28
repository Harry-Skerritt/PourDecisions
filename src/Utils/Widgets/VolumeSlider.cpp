#include "VolumeSlider.h"

VolumeSlider::VolumeSlider()
    : m_minValue(0.f), m_maxValue(100.f), m_value(0.f) {
    // Initialize the slider components
    m_track.setFillColor(sf::Color::Transparent);  // Initially invisible (transparent) for the track
    m_track.setOutlineColor(sf::Color::Black);    // Track border color
    m_track.setOutlineThickness(1.f);

    m_filledTrack.setFillColor(sf::Color::Green);  // Default color for the filled part of the track

    m_handle.setFillColor(sf::Color::Red);  // Default handle color
    m_handle.setOrigin(m_handle.getSize() / 2.f);  // Center the handle
}

void VolumeSlider::setSize(float width, float height) {
    m_track.setSize(sf::Vector2f(width, height));

    // Recalculate the filled portion size based on the initial value
    updateFilledTrackSize();

    m_handle.setSize(sf::Vector2f(height, height));  // Handle size is based on height
}

void VolumeSlider::setPosition(float x, float y) {
    m_track.setPosition(x, y);
    m_filledTrack.setPosition(x, y);
    updateHandlePosition();
}

void VolumeSlider::setRange(float minValue, float maxValue) {
    m_minValue = minValue;
    m_maxValue = maxValue;
}

void VolumeSlider::setHandleColor(const sf::Color& color) {
    m_handleColor = color;
    m_handle.setFillColor(m_handleColor);
}

void VolumeSlider::setTrackColor(const sf::Color& color) {
    m_trackColor = color;
    m_track.setFillColor(m_trackColor);
}

void VolumeSlider::setFilledTrackColor(const sf::Color& color) {
    m_filledTrackColor = color;
    m_filledTrack.setFillColor(m_filledTrackColor); // Update the filled track color
}

float VolumeSlider::getValue() const {
    return m_value;
}

void VolumeSlider::setValue(float value) {
    if (value < m_minValue) value = m_minValue;
    if (value > m_maxValue) value = m_maxValue;

    m_value = value;

    // Update the filled track size
    updateFilledTrackSize();

    // Update the handle position
    updateHandlePosition();

    // Trigger the callback if it exists
    if (m_onValueChangedCallback) {
        m_onValueChangedCallback(m_value);
    }
}

void VolumeSlider::setOnValueChangedCallback(std::function<void(float)> callback) {
    m_onValueChangedCallback = callback;
}

void VolumeSlider::handleMouseInput(const sf::Vector2i& mousePos, bool mousePressed) {
    // Check if the mouse is pressed anywhere on the track
    if (mousePressed && m_track.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
        // Calculate the value based on the mouse position on the track
        float newValue = (mousePos.x - m_track.getPosition().x) / m_track.getSize().x * (m_maxValue - m_minValue) + m_minValue;
        setValue(newValue);  // Set the new value, this will update the filled track and handle position
    }
}

void VolumeSlider::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    // Draw the solid filled track color
    target.draw(m_filledTrack, states);

    // Draw the track outline
    target.draw(m_track, states);

    // Draw the handle
    target.draw(m_handle, states);
}

void VolumeSlider::updateFilledTrackSize() {
    float trackWidth = m_track.getSize().x;
    float filledWidth = (m_value - m_minValue) / (m_maxValue - m_minValue) * trackWidth;
    m_filledTrack.setSize(sf::Vector2f(filledWidth, m_filledTrack.getSize().y));
}

void VolumeSlider::updateHandlePosition() {
    float trackWidth = m_track.getSize().x;
    // Calculate the handle's X position based on the current value
    float handleX = m_track.getPosition().x + (m_value - m_minValue) / (m_maxValue - m_minValue) * trackWidth;

    // Adjust the Y position to vertically center the handle on the track
    float handleY = m_track.getPosition().y + m_track.getSize().y / 2.f - m_handle.getSize().y / 2.f;

    m_handle.setPosition(handleX, handleY);  // Update the handle's position
}
