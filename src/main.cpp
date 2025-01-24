#include <SFML/Graphics.hpp>
#include <SFML/GpuPreference.hpp>
#include <iostream>
#include "Game.h"
#include "Utils/JSON/Settings.h"


#define SFML_DEFINE_DISCRETE_GPU_PREFERENCE // Use discrete GPU if available

int main()
{
    while (true) { // Loop to allow restarting the game
        // Load settings (resolution, fullscreen, etc.)
        Settings settings = Settings::fromFile("../Data/settings.json");

        //Get and split resolution
        std::string resolution = settings.getResolution();
        int width, height;
        size_t xPos = resolution.find('x');
        if (xPos == std::string::npos) {
            throw std::invalid_argument("Invalid resolution format. Expected format: 'widthxheight'");
        }

        // Extract the width and height as substrings
        std::string widthStr = resolution.substr(0, xPos);
        std::string heightStr = resolution.substr(xPos + 1);

        // Convert substrings to integers
        width = std::stoi(widthStr);
        height = std::stoi(heightStr);

        const std::string VERSION_NO = "beta-0.2.5";
        const std::string RES = std::to_string(width) + "x" + std::to_string(height);
        const sf::String BASE_WINDOW_TITLE = "Pour Decisions - " + VERSION_NO + " @" + RES;


        sf::VideoMode videoMode(width, height);
        sf::Uint32 style = settings.getFullscreen() ? sf::Style::Fullscreen : sf::Style::Default;

        // Create the window with the current settings
        sf::RenderWindow window(videoMode, BASE_WINDOW_TITLE, style);
        window.setFramerateLimit(60);

        auto image = sf::Image{};
        if (!image.loadFromFile("../Data/Assets/Favicon.png")) {
            std::cout << "App Icon did not load" << std::endl;
        }
        window.setIcon(image.getSize().x, image.getSize().y, image.getPixelsPtr());

        // Start the clock
        sf::Clock clock;

        // Initialize the game instance
        Game game(window);

        if (!game.init()) {
            return 0; // Exit if the game initialization fails
        }

        bool restartRequested = false; // Flag to indicate if restart is needed

        // Main game loop
        while (window.isOpen()) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window.close();
                }

                if (event.type == sf::Event::MouseButtonPressed) {
                    game.mouseClicked(event);
                }

                if (event.type == sf::Event::TextEntered) {
                    game.textEntered(event);
                }

                if (event.type == sf::Event::MouseMoved) {
                    game.mouseDragged(event);
                }

                if (event.type == sf::Event::KeyPressed) {
                    game.keyPressed(event);
                }
            }

            // Update game state
            float dt = clock.restart().asSeconds();
            game.update(dt);

            window.clear(sf::Color::Black);
            game.render(dt);
            window.display();

            // Check if the game requests a restart (e.g., due to settings change)
            if (game.isRestartRequired()) {
                restartRequested = true;
                window.close();
            }
        }

        if (!restartRequested) {
            break; // Exit the outer loop if no restart is needed
        }
    }

    return 0;
}