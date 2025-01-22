#ifndef ROCKING_SPRITE_H
#define ROCKING_SPRITE_H

#include <SFML/Graphics.hpp>

class RockingSprite {
public:
    // Empty constructor
    RockingSprite();

    // Initialize the sprite with a texture and window reference
    void init(const sf::Texture& texture, sf::RenderWindow& window);

    // Starts the rocking animation
    void startRocking();

    // Updates the rocking motion (called every frame)
    void update(float dt);

    // Draw the sprite to the window
    void draw(sf::RenderWindow& window);

private:
    sf::Sprite sprite;
    sf::Vector2f originalPosition;
    bool isRocking;
    float angle;
    float rockingSpeed;
    float rockingDuration;
    float elapsedTime;

    float scale;
};

#endif // ROCKING_SPRITE_H
