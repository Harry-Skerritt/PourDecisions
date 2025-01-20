#include "RoundedRectangle.h"

RoundedRectangle::RoundedRectangle()
    : m_width(0), m_height(0), m_radius(0) {}

void RoundedRectangle::setSize(float width, float height) {
    m_width = width;
    m_height = height;

    // Reconfigure the shapes based on the new size
    m_center.setSize(sf::Vector2f(width - 2 * m_radius, height - 2 * m_radius));
    m_center.setPosition(m_radius, m_radius);

    m_topBottom.setSize(sf::Vector2f(width - 2 * m_radius, m_radius));
    m_topBottom.setPosition(m_radius, 0);

    m_leftRight.setSize(sf::Vector2f(m_radius, height - 2 * m_radius));
    m_leftRight.setPosition(0, m_radius);
}

void RoundedRectangle::setRadius(float radius) {
    m_radius = radius;

    // Reconfigure the shapes based on the new radius
    m_center.setSize(sf::Vector2f(m_width - 2 * radius, m_height - 2 * radius));
    m_center.setPosition(radius, radius);

    m_topBottom.setSize(sf::Vector2f(m_width - 2 * radius, radius));
    m_topBottom.setPosition(radius, 0);

    m_leftRight.setSize(sf::Vector2f(radius, m_height - 2 * radius));
    m_leftRight.setPosition(0, radius);
}

void RoundedRectangle::setPosition(float x, float y) {
    float offsetX = x - m_radius;
    float offsetY = y - m_radius;

    m_center.setPosition(offsetX + m_radius, offsetY + m_radius);
    m_topBottom.setPosition(offsetX + m_radius, offsetY);
    m_leftRight.setPosition(offsetX, offsetY + m_radius);
}

void RoundedRectangle::setFillColor(const sf::Color& color) {
    m_center.setFillColor(color);
    m_topBottom.setFillColor(color);
    m_leftRight.setFillColor(color);
}

void RoundedRectangle::drawQuarterCircle(sf::RenderTarget& target, float centerX, float centerY, float radius, const sf::Color& color, float angleStart, float angleEnd) const {
    // Use an sf::CircleShape but adjust it to only draw a segment
    sf::CircleShape quarterCircle(radius, 30); // More points for smoothness
    quarterCircle.setFillColor(color);

    // Center the circle at the corner position
    quarterCircle.setPosition(centerX - radius, centerY - radius);  // Offset by radius to position correctly

    // Set the cut angles to draw only a quarter of the circle
    quarterCircle.setPointCount(30); // Use more points to make it a smooth quarter circle

    target.draw(quarterCircle);  // Draw the corner slice
}

void RoundedRectangle::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(m_center, states);
    target.draw(m_topBottom, states);
    target.draw(m_leftRight, states);

    // Draw each corner as a quarter circle
    drawQuarterCircle(target, 0, 0, m_radius, m_center.getFillColor(), 3.14f, 4.71f); // Top-left
    drawQuarterCircle(target, m_width - m_radius * 2, 0, m_radius, m_center.getFillColor(), 4.71f, 6.28f); // Top-right
    drawQuarterCircle(target, 0, m_height - m_radius * 2, m_radius, m_center.getFillColor(), 1.57f, 3.14f); // Bottom-left
    drawQuarterCircle(target, m_width - m_radius * 2, m_height - m_radius * 2, m_radius, m_center.getFillColor(), 0, 1.57f); // Bottom-right
}
