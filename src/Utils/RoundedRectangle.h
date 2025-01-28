#ifndef ROUNDED_RECTANGLE_H
#define ROUNDED_RECTANGLE_H

#include <SFML/Graphics.hpp>

class RoundedRectangle : public sf::Drawable {
public:
    RoundedRectangle();

    void setSize(float width, float height);
    void setRadius(float radius);
    void setPosition(float x, float y);
    void setFillColor(const sf::Color& color);

protected:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
    float m_width;
    float m_height;
    float m_radius;
    sf::RectangleShape m_center;
    sf::RectangleShape m_topBottom;
    sf::RectangleShape m_leftRight;

    void drawQuarterCircle(sf::RenderTarget& target, float centerX, float centerY, float radius, const sf::Color& color, float angleStart, float angleEnd) const;
};

#endif // ROUNDED_RECTANGLE_H

