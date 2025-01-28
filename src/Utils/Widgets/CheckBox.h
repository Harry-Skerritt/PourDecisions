#ifndef CHECKBOX_H
#define CHECKBOX_H

#include <SFML/Graphics.hpp>
#include <functional>  // For std::function

class Checkbox : public sf::Drawable {
public:
    Checkbox();

    // Setters
    void setSize(float width, float height);
    void setPosition(float x, float y);
    void setFillColor(const sf::Color& uncheckedColor, const sf::Color& checkedColor);
    void setBorderColor(const sf::Color& borderColor);

    // Getter
    bool isChecked() const;

    // Setter
    void setChecked(bool checked);

    // Handle mouse input
    void handleMouseInput(const sf::Vector2i& mousePos, bool mousePressed);

    // Set callback function to be called when the state changes
    void setOnStateChangedCallback(std::function<void(bool)> callback);

protected:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
    sf::RectangleShape m_box;
    sf::RectangleShape m_checkmark;
    sf::Color m_checkedColor;
    bool m_checked;

    std::function<void(bool)> m_onStateChangedCallback;  // Callback for state change
};

#endif // CHECKBOX_H
