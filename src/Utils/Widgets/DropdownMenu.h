#ifndef DROPDOWNMENU_H
#define DROPDOWNMENU_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

class DropdownMenu : public sf::Drawable {
public:
    DropdownMenu();

    void initialize(float x, float y, float width, float height, const std::vector<std::string>& items, sf::Font& font, float charSize);
    void handleEvent(const sf::Event& event, const sf::Vector2i& mousePos);
    void setColors(const sf::Color& bgColor, const sf::Color& textColor, const sf::Color& highlightColor, const sf::Color& selectedColor, const sf::Color& borderColor);

    std::string getSelectedItem() const;
    void setSelectedItem(const std::string& item);

private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    void toggleMenuVisibility();

    sf::RectangleShape m_button; // For the dropdown button
    sf::Text m_buttonText; // Display the current selection
    sf::Font m_font;

    std::vector<std::string> m_items;
    mutable std::vector<sf::Text> m_itemTexts; // For displaying menu items

    bool m_menuOpen;
    size_t m_selectedIndex;

    sf::Color m_bgColor;
    sf::Color m_textColor;
    sf::Color m_highlightColor;
    sf::Color m_selectedColor;
    sf::Color m_borderColor;
};

#endif // DROPDOWNMENU_H
