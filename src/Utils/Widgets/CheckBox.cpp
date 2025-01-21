#include "CheckBox.h"

Checkbox::Checkbox()
    : m_checked(false) {
    // Default size for the checkbox
    m_box.setSize(sf::Vector2f(30.f, 30.f));  // Default size is 30x30
    m_box.setOutlineThickness(2.f);            // Add border to the checkbox

    // Set default colors
    m_box.setFillColor(sf::Color::Transparent); // Transparent by default
    m_box.setOutlineColor(sf::Color::Black);    // Default border color

    // Initialize the checkmark (invisible by default)
    m_checkmark.setSize(sf::Vector2f(20.f, 20.f));  // Checkmark size
    m_checkmark.setFillColor(sf::Color::Green);     // Green checkmark
    m_checkmark.setPosition(5.f, 5.f);               // Centered in the checkbox
}

void Checkbox::setSize(float width, float height) {
    m_box.setSize(sf::Vector2f(width, height));
    m_checkmark.setSize(sf::Vector2f(width - 10.f, height - 10.f));  // Slightly smaller to fit inside the box
}

void Checkbox::setPosition(float x, float y) {
    m_box.setPosition(x, y);
    m_checkmark.setPosition(x + 5.f, y + 5.f);  // Keep the checkmark inside the box
}

void Checkbox::setFillColor(const sf::Color& uncheckedColor, const sf::Color& checkedColor) {
    // Update the colors based on the checked state
    m_checkedColor = checkedColor;
    m_box.setFillColor(uncheckedColor);
    if (m_checked) {
        m_checkmark.setFillColor(checkedColor);
    }
    else {
        m_checkmark.setFillColor(sf::Color::Transparent);  // No checkmark when unchecked
    }
}

void Checkbox::setBorderColor(const sf::Color& borderColor) {
    m_box.setOutlineColor(borderColor);
}

bool Checkbox::isChecked() const {
    return m_checked;
}

void Checkbox::setChecked(bool checked) {
    m_checked = checked;
}

void Checkbox::handleMouseInput(const sf::Vector2i& mousePos, bool mousePressed) {
    // Toggle the checkbox when clicked
    if (m_box.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos)) && mousePressed) {
        m_checked = !m_checked;  // Toggle the checked state
        // Update the checkmark visibility based on the new state
        if (m_checked) {
            m_checkmark.setFillColor(m_checkedColor);  // Set the color when checked
        }
        else {
            m_checkmark.setFillColor(sf::Color::Transparent);  // Hide the checkmark when unchecked
        }

        // Trigger the callback when the state changes
        if (m_onStateChangedCallback) {
            m_onStateChangedCallback(m_checked);
        }
    }
}

void Checkbox::setOnStateChangedCallback(std::function<void(bool)> callback) {
    m_onStateChangedCallback = callback;
}

void Checkbox::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(m_box, states);         // Draw the checkbox border and background
    target.draw(m_checkmark, states);   // Draw the checkmark (if checked)
}
