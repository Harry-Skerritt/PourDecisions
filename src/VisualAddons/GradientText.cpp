#include "GradientText.h"

GradientText::GradientText()
    : vertices(sf::Triangles), fontTexture(nullptr), topColor(sf::Color::White), bottomColor(sf::Color::Black) {}

void GradientText::setString(const std::string& text) {
    this->text.setString(text);
    updateGradient();
}

void GradientText::setFont(const sf::Font& font) {
    text.setFont(font);
    fontTexture = const_cast<sf::Texture*>(&font.getTexture(text.getCharacterSize()));
    updateGradient();
}

void GradientText::setCharacterSize(unsigned int size) {
    text.setCharacterSize(size);
    fontTexture = const_cast<sf::Texture*>(&text.getFont()->getTexture(size));
    updateGradient();
}

void GradientText::setGradientColors(const sf::Color& topColor, const sf::Color& bottomColor) {
    this->topColor = topColor;
    this->bottomColor = bottomColor;
    updateGradient();
}

void GradientText::setPosition(float x, float y) {
    sf::Transformable::setPosition(x, y);
    updateGradient();
}

sf::FloatRect GradientText::getGlobalBounds() const {
    return text.getGlobalBounds();
}

sf::FloatRect GradientText::getLocalBounds() const {
    return text.getLocalBounds();
}

void GradientText::updateGradient() {
    const sf::String& str = text.getString();
    const sf::Font* font = text.getFont();
    if (str.isEmpty() || !font) return;

    unsigned int characterSize = text.getCharacterSize();
    vertices.clear();

    sf::Vector2f position = getPosition();
    float xOffset = 0.0f;

    for (std::size_t i = 0; i < str.getSize(); ++i) {
        sf::Uint32 character = str[i];
        const sf::Glyph& glyph = font->getGlyph(character, characterSize, false);

        float left = xOffset + glyph.bounds.left;
        float top = glyph.bounds.top;
        float right = left + glyph.bounds.width;
        float bottom = top + glyph.bounds.height;

        sf::FloatRect uv(
            static_cast<float>(glyph.textureRect.left),
            static_cast<float>(glyph.textureRect.top),
            static_cast<float>(glyph.textureRect.width),
            static_cast<float>(glyph.textureRect.height)
        );

        vertices.append(sf::Vertex(sf::Vector2f(left, top) + position, topColor, sf::Vector2f(uv.left, uv.top)));
        vertices.append(sf::Vertex(sf::Vector2f(right, top) + position, topColor, sf::Vector2f(uv.left + uv.width, uv.top)));
        vertices.append(sf::Vertex(sf::Vector2f(left, bottom) + position, bottomColor, sf::Vector2f(uv.left, uv.top + uv.height)));

        vertices.append(sf::Vertex(sf::Vector2f(right, top) + position, topColor, sf::Vector2f(uv.left + uv.width, uv.top)));
        vertices.append(sf::Vertex(sf::Vector2f(right, bottom) + position, bottomColor, sf::Vector2f(uv.left + uv.width, uv.top + uv.height)));
        vertices.append(sf::Vertex(sf::Vector2f(left, bottom) + position, bottomColor, sf::Vector2f(uv.left, uv.top + uv.height)));

        xOffset += glyph.advance;
    }
}

void GradientText::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    if (!fontTexture) return;

    states.transform *= getTransform();
    states.texture = fontTexture;
    target.draw(vertices, states);
}
