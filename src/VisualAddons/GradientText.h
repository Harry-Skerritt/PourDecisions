#ifndef GRADIENTTEXT_H
#define GRADIENTTEXT_H

#include <SFML/Graphics.hpp>
#include <string>

class GradientText : public sf::Drawable, public sf::Transformable {
public:
    GradientText();

    void setString(const std::string& text);
    void setFont(const sf::Font& font);
    void setCharacterSize(unsigned int size);
    void setGradientColors(const sf::Color& topColor, const sf::Color& bottomColor);
    void setPosition(float x, float y);

    sf::FloatRect getGlobalBounds() const;
    sf::FloatRect getLocalBounds() const;

private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    sf::Text text;           // Base text object
    sf::VertexArray vertices; // Gradient vertices
    sf::Texture* fontTexture; // Pointer to font texture
    sf::Color topColor;      // Top gradient color
    sf::Color bottomColor;   // Bottom gradient color

    void updateGradient();   // Updates the gradient
};

#endif // GRADIENTTEXT_H
