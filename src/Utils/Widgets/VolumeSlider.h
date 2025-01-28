#ifndef VOLUME_SLIDER_H
#define VOLUME_SLIDER_H

#include <SFML/Graphics.hpp>
#include <functional>

class VolumeSlider : public sf::Drawable {
public:
    // Constructor
    VolumeSlider();

    // Setters
    void setSize(float width, float height);
    void setPosition(float x, float y);
    void setRange(float minValue, float maxValue);
    void setHandleColor(const sf::Color& color);
    void setTrackColor(const sf::Color& color);
    void setFilledTrackColor(const sf::Color& color); // Set the filled track color
    void setValue(float value);
    void setOnValueChangedCallback(std::function<void(float)> callback);
    void updateFilledTrackSize();
    void updateHandlePosition();

    // Getters
    float getValue() const;

    // Handle mouse input for dragging the handle
    void handleMouseInput(const sf::Vector2i& mousePos, bool mousePressed);

private:
    // Override the draw method to render the slider components
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    // Slider properties
    float m_minValue;
    float m_maxValue;
    float m_value;
    bool m_dragging;

    // Slider components
    sf::RectangleShape m_track;           // Track background
    sf::RectangleShape m_filledTrack;     // Filled portion of the track (representing current value)
    sf::RectangleShape m_handle;          // Slider handle

    // Slider colors
    sf::Color m_trackColor;
    sf::Color m_filledTrackColor;
    sf::Color m_handleColor;

    // Callback function when the value changes
    std::function<void(float)> m_onValueChangedCallback;
};

#endif // VOLUME_SLIDER_H
