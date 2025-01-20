#include "DropdownMenu.h"

DropdownMenu::DropdownMenu()
    : m_menuOpen(false), m_selectedIndex(0) {
    // Default values for colors
    setColors(sf::Color::White, sf::Color::Black, sf::Color(200, 200, 200), sf::Color(100, 100, 255), sf::Color::Black);
}

void DropdownMenu::initialize(float x, float y, float width, float height, const std::vector<std::string>& items, sf::Font& font) {
    m_items = items;

    m_font = font;

    // Set button appearance
    m_button.setSize(sf::Vector2f(width, height));
    m_button.setPosition(x, y);
    m_button.setFillColor(m_bgColor);
    m_button.setOutlineThickness(2); // Border thickness
    m_button.setOutlineColor(m_borderColor); // Border color

    // Set button text
    m_buttonText.setFont(m_font);
    m_buttonText.setString(m_items[m_selectedIndex]);
    m_buttonText.setCharacterSize(20);
    m_buttonText.setFillColor(m_textColor);
    m_buttonText.setPosition(x + 10, y + 5);

    // Prepare the menu items
    m_itemTexts.clear(); // Clear any previous items
    for (const auto& item : m_items) {
        sf::Text text;
        text.setFont(m_font);
        text.setString(item);
        text.setCharacterSize(20);
        text.setFillColor(m_textColor);
        m_itemTexts.push_back(text);
    }
}

void DropdownMenu::setColors(const sf::Color& bgColor, const sf::Color& textColor, const sf::Color& highlightColor, const sf::Color& selectedColor, const sf::Color& borderColor) {
    m_bgColor = bgColor;
    m_textColor = textColor;
    m_highlightColor = highlightColor;
    m_selectedColor = selectedColor;
    m_borderColor = borderColor;

    m_button.setFillColor(bgColor);

    // Update item colors
    for (auto& itemText : m_itemTexts) {
        itemText.setFillColor(textColor);
    }
}

void DropdownMenu::handleEvent(const sf::Event& event, const sf::Vector2i& mousePos) {
    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
        // Check if the dropdown button is clicked
        if (m_button.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
            toggleMenuVisibility();
        }
        else if (m_menuOpen) {
            // Check if any item is clicked
            for (size_t i = 0; i < m_items.size(); ++i) {
                if (m_itemTexts[i].getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
                    setSelectedItem(m_items[i]);
                    toggleMenuVisibility();
                    break;
                }
            }
        }
    }
}

std::string DropdownMenu::getSelectedItem() const {
    return m_items[m_selectedIndex];
}

void DropdownMenu::setSelectedItem(const std::string& item) {
    for (size_t i = 0; i < m_items.size(); ++i) {
        if (m_items[i] == item) {
            m_selectedIndex = i;
            m_buttonText.setString(m_items[i]);
            break;
        }
    }
}

void DropdownMenu::toggleMenuVisibility() {
    m_menuOpen = !m_menuOpen;
}

void DropdownMenu::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(m_button, states);
    target.draw(m_buttonText, states);

    if (m_menuOpen) {
        // Draw the menu items
        float itemHeight = m_itemTexts[0].getLocalBounds().height;

        // Get the mouse position relative to the window
        const sf::Vector2i mousePos = sf::Mouse::getPosition(static_cast<const sf::RenderWindow&>(target));

        for (size_t i = 0; i < m_items.size(); ++i) {
            m_itemTexts[i].setPosition(m_button.getPosition().x, m_button.getPosition().y + m_button.getSize().y + i * itemHeight);

            // Highlight items when hovered
            if (m_itemTexts[i].getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
                m_itemTexts[i].setFillColor(m_highlightColor);
            }
            else {
                m_itemTexts[i].setFillColor(m_textColor);
            }

            // Change the selected item color
            if (i == m_selectedIndex) {
                m_itemTexts[i].setFillColor(m_selectedColor);
            }

            target.draw(m_itemTexts[i], states);
        }
    }
}
