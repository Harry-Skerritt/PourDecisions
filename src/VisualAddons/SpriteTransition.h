#ifndef SPRITETRANSITION_H
#define SPRITETRANSITION_H

#include <SFML/Graphics.hpp>

class SpriteTransition {
public:
    // Constructor
    SpriteTransition();

    void init(const sf::Texture& texture, float durationIn, sf::RenderWindow& window);

    // Update the sprite's state (called every frame)
    void update(float deltaTime);

    // Render the sprite to the window
    void render(sf::RenderWindow& window);

    // Check if the transition is complete
    bool isComplete() const;

    // Reset transition
    void reset();

private:
    sf::Sprite sprite;
    float duration;           // Total time for the transition
    float elapsedTime;        // Time that has passed since start
    float maxScale;           // Maximum scale to fill the screen
    bool transitionComplete;  // Whether the transition is complete
};

#endif // SPRITETRANSITION_H
