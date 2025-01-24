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
    sf::FloatRect bounds = getLocalBounds();
    sf::Vector2f position = getPosition() - getOrigin();
    return sf::FloatRect(position.x, position.y, bounds.width, bounds.height);
}

sf::FloatRect GradientText::getLocalBounds() const {
    // Calculate bounds based on vertices if they exist
    if (vertices.getVertexCount() == 0) {
        return text.getLocalBounds();
    }

    float left = std::numeric_limits<float>::max();
    float top = std::numeric_limits<float>::max();
    float right = std::numeric_limits<float>::lowest();
    float bottom = std::numeric_limits<float>::lowest();

    for (std::size_t i = 0; i < vertices.getVertexCount(); ++i) {
        const sf::Vector2f& pos = vertices[i].position;
        left = std::min(left, pos.x);
        top = std::min(top, pos.y);
        right = std::max(right, pos.x);
        bottom = std::max(bottom, pos.y);
    }

    return sf::FloatRect(0, 0, right - left, bottom - top);
}


void GradientText::updateGradient() {
    const sf::String& str = text.getString();
    const sf::Font* font = text.getFont();
    if (str.isEmpty() || !font) return;

    unsigned int characterSize = text.getCharacterSize();
    vertices.clear();

    sf::Vector2f originOffset = getOrigin(); // Account for origin
    float xOffset = 0.0f;

    // Calculate the full height of the font to adjust vertical centering
    float fontAscent = font->getGlyph('A', characterSize, false).bounds.top;
    float fontDescent = font->getGlyph('g', characterSize, false).bounds.top +
        font->getGlyph('g', characterSize, false).bounds.height;
    float verticalOffset = -fontAscent; // Align text vertically

    for (std::size_t i = 0; i < str.getSize(); ++i) {
        sf::Uint32 character = str[i];
        const sf::Glyph& glyph = font->getGlyph(character, characterSize, false);

        float left = xOffset + glyph.bounds.left - originOffset.x;
        float top = glyph.bounds.top + verticalOffset - originOffset.y;
        float right = left + glyph.bounds.width;
        float bottom = top + glyph.bounds.height;

        sf::FloatRect uv(
            static_cast<float>(glyph.textureRect.left),
            static_cast<float>(glyph.textureRect.top),
            static_cast<float>(glyph.textureRect.width),
            static_cast<float>(glyph.textureRect.height)
        );

        vertices.append(sf::Vertex(sf::Vector2f(left, top), topColor, sf::Vector2f(uv.left, uv.top)));
        vertices.append(sf::Vertex(sf::Vector2f(right, top), topColor, sf::Vector2f(uv.left + uv.width, uv.top)));
        vertices.append(sf::Vertex(sf::Vector2f(left, bottom), bottomColor, sf::Vector2f(uv.left, uv.top + uv.height)));

        vertices.append(sf::Vertex(sf::Vector2f(right, top), topColor, sf::Vector2f(uv.left + uv.width, uv.top)));
        vertices.append(sf::Vertex(sf::Vector2f(right, bottom), bottomColor, sf::Vector2f(uv.left + uv.width, uv.top + uv.height)));
        vertices.append(sf::Vertex(sf::Vector2f(left, bottom), bottomColor, sf::Vector2f(uv.left, uv.top + uv.height)));

        xOffset += glyph.advance;
    }
}

void GradientText::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    if (!fontTexture) return;

    states.transform *= getTransform();
    states.texture = fontTexture;
    target.draw(vertices, states);
}

void GradientText::setAlpha(sf::Uint8 alpha) {
    topColor.a = alpha;
    bottomColor.a = alpha;

    updateGradient();
}
