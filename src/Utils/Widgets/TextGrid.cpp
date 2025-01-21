#include "TextGrid.h"

TextGrid::TextGrid() {
    m_background.setFillColor(sf::Color::White); // Default background color
    m_defaultTextColor = sf::Color::Black;
    m_borderColor = sf::Color::Black;
    m_hoverColor = sf::Color::Red;
}

void TextGrid::setSize(float width, float height) {
    m_background.setSize(sf::Vector2f(width, height));
    arrangeTextFields();
}

void TextGrid::setPosition(float x, float y) {
    m_background.setPosition(x, y);
    arrangeTextFields();
}

void TextGrid::setBackgroundColor(const sf::Color& color) {
    m_background.setFillColor(color);
}

void TextGrid::setBorder(float thickness, sf::Color color) {
    m_borderColor = color;
    m_background.setOutlineThickness(thickness);
    m_background.setOutlineColor(m_borderColor);
}

void TextGrid::setTextColor(const sf::Color& color) {
    m_defaultTextColor = color;
}

void TextGrid::setTextHoverColor(const sf::Color& color) {
    m_hoverColor = color;
}

void TextGrid::initialize(size_t textFieldCount, const sf::Font& font, unsigned int characterSize, bool hasHeader) {
    m_hasHeader = hasHeader;

    // Initialize header if required
    if (m_hasHeader) {
        m_header.setFont(font);
        m_header.setCharacterSize(characterSize);
        m_header.setFillColor(m_defaultTextColor);
        m_header.setString("");                 // Empty by default
    }

    // Initialize text fields
    m_textFields.clear();
    for (size_t i = 0; i < textFieldCount; ++i) {
        sf::Text textField;
        textField.setFont(font);
        textField.setCharacterSize(characterSize);
        textField.setFillColor(m_defaultTextColor);
        textField.setString("");                 // Empty by default
        m_textFields.push_back(textField);
    }
    arrangeTextFields();
}

void TextGrid::setText(size_t index, const std::string& text) {
    if (index < m_textFields.size()) {
        m_textFields[index].setString(text);
        fitTextToWidth(m_textFields[index], m_background.getSize().x / 2 - 2 * m_padding);
        arrangeTextFields();
    }
}

std::string TextGrid::getText(size_t index) {
    if (index < m_textFields.size()) {
        std::string fieldText;
        fieldText = m_textFields[index].getString();
        return fieldText;
    }
    else {
        return "";
    }
}

void TextGrid::setHeader(const std::string& headerText) {
    if (m_hasHeader) {
        m_header.setString(headerText);
        fitTextToWidth(m_header, m_background.getSize().x - 2 * m_padding);
        arrangeTextFields();
    }
}


void TextGrid::clearTextFields() {
    for (auto& textField : m_textFields) {
        textField.setString("");
    }
}

void TextGrid::handleHover(const sf::Vector2f& mousePosition) {
    for (auto& textField : m_textFields) {
        sf::FloatRect bounds = textField.getGlobalBounds();
        if (bounds.contains(mousePosition)) {
            textField.setFillColor(m_hoverColor); // Change color on hover
        }
        else {
            textField.setFillColor(m_defaultTextColor); // Reset to default
        }
    }
}

void TextGrid::handleClick(const sf::Vector2f& mousePosition) {
    for (size_t i = 0; i < m_textFields.size(); ++i) {
        sf::FloatRect bounds = m_textFields[i].getGlobalBounds();
        if (bounds.contains(mousePosition)) {
            if (m_clickCallback) {
                m_clickCallback(); // Call the callback
            }
            m_textFields[i].setString(""); // Clear text on click
            shiftTextFields();
            break; // Exit after handling the first match
        }
    }
}

void TextGrid::setClickCallback(std::function<void()> callback) {
    m_clickCallback = callback;
}


sf::FloatRect TextGrid::getGlobalBounds() const {
    return m_background.getGlobalBounds();
}

sf::FloatRect TextGrid::getLocalBounds() const {
    return m_background.getLocalBounds();
}

void TextGrid::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(m_background, states);

    if (m_hasHeader) {
        target.draw(m_header, states);
    }

    for (const auto& text : m_textFields) {
        target.draw(text, states);
    }
}

void TextGrid::arrangeTextFields() {
    if (m_textFields.empty()) return;

    float rectX = m_background.getPosition().x;
    float rectY = m_background.getPosition().y;
    float rectWidth = m_background.getSize().x;
    float rectHeight = m_background.getSize().y;

    float headerHeight = 0.0f;

    if (m_hasHeader) {
        headerHeight = m_header.getLocalBounds().height + m_padding;
        m_header.setPosition(
            rectX + rectWidth / 2 - m_header.getLocalBounds().width / 2,
            rectY + m_padding
        );
    }

    size_t totalFields = m_textFields.size();
    size_t rowCount = (totalFields + 1) / 2; // Two rows, split evenly
    float rowHeight = (rectHeight - headerHeight) / rowCount;
    float columnWidth = rectWidth / 2; // Two columns

    for (size_t i = 0; i < totalFields; ++i) {
        size_t rowIndex = i / 2;
        size_t columnIndex = i % 2;

        float x = rectX + columnWidth * columnIndex + m_padding;
        float y = rectY + headerHeight + rowHeight * rowIndex + m_padding;

        m_textFields[i].setPosition(x, y);
    }
}

void TextGrid::shiftTextFields() {
    std::vector<sf::Text> updatedFields;
    for (const auto& textField : m_textFields) {
        if (!textField.getString().isEmpty()) {
            updatedFields.push_back(textField);
        }
    }

    while (updatedFields.size() < m_textFields.size()) {
        sf::Text emptyText = m_textFields[0];
        emptyText.setString("");
        updatedFields.push_back(emptyText);
    }

    m_textFields = std::move(updatedFields);
    arrangeTextFields();
}

void TextGrid::fitTextToWidth(sf::Text& text, float maxWidth) {
    float textWidth = text.getLocalBounds().width;
    unsigned int currentSize = text.getCharacterSize();

    while (textWidth > maxWidth && currentSize > 5) { // Prevent too small text
        currentSize--;
        text.setCharacterSize(currentSize);
        textWidth = text.getLocalBounds().width;
    }
}
