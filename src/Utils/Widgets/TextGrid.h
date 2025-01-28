#ifndef TEXTGRID_H
#define TEXTGRID_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <functional>

class TextGrid : public sf::Drawable {
public:
    TextGrid();

    // Set size and position of the grid
    void setSize(float width, float height);
    void setPosition(float x, float y);

    // Set background color
    void setBackgroundColor(const sf::Color& color);

    // Set a border - Default color black
    void setBorder(float thickness, sf::Color color = sf::Color::Black);

    // Set text color
    void setTextColor(const sf::Color& color);

    // Set text hover color
    void setTextHoverColor(const sf::Color& color);

    // Initialize grid with optional header and a specific number of text fields
    void initialize(size_t textFieldCount, const sf::Font& font, unsigned int characterSize = 20, bool hasHeader = false);

    // Populate text fields one by one
    void setText(size_t index, const std::string& text);

    // Get value from a text field
    std::string getText(size_t index);

    // Set header text
    void setHeader(const std::string& headerText);

    // Clear all text fields
    void clearTextFields();

    // Handles hover events
    void handleHover(const sf::Vector2f& mousePosition);

    // Handles click events
    void handleClick(const sf::Vector2f& mousePosition);  

    // Sets call back function
    void setClickCallback(std::function<void()> callback);

    // Get bounds of the grid
    sf::FloatRect getGlobalBounds() const;
    sf::FloatRect getLocalBounds() const;

protected:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
    sf::RectangleShape m_background;                 // Background rectangle
    std::vector<sf::Text> m_textFields;              // List of text fields
    sf::Text m_header;                               // Header text
    bool m_hasHeader = false;                        // Flag to indicate header usage

    float m_padding = 10.0f;                         // Padding between text and edges
    float m_textVerticalSpacing = 5.0f;              // Vertical spacing between rows

    sf::Color m_hoverColor;                          // Text hover color
    sf::Color m_defaultTextColor;                    // Text color
    sf::Color m_borderColor;                         // Border color

    std::function<void()> m_clickCallback; // Callback for click events

    void arrangeTextFields();                        // Recalculate positions of text fields

    // Utility function to fit text within a given width
    void fitTextToWidth(sf::Text& text, float maxWidth);

    // Utility function to shift text fields
    void shiftTextFields();
};

#endif // TEXTGRID_H
