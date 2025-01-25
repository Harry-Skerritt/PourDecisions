#include <SFML/Graphics.hpp>
#include <SFML/GpuPreference.hpp>
#include <iostream>
#include "Game.h"
#include "Utils/JSON/Settings.h"
#include "Screens/LoadingScreen.h"


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

        const int FPS = 60;
        const std::string VERSION_NO = "beta-0.3.4";
        const std::string RES = std::to_string(width) + "x" + std::to_string(height);
        const sf::String BASE_WINDOW_TITLE = "Pour Decisions - " + VERSION_NO + " @" + RES;


        sf::VideoMode videoMode(width, height);
        sf::Uint32 style = settings.getFullscreen() ? sf::Style::Fullscreen : sf::Style::Default;

        // Create the window with the current settings
        sf::RenderWindow window(videoMode, BASE_WINDOW_TITLE, style);
        window.setFramerateLimit(FPS);

        auto image = sf::Image{};
        if (!image.loadFromFile("../Data/Assets/Favicon.png")) {
            std::cout << "App Icon did not load" << std::endl;
        }
        window.setIcon(image.getSize().x, image.getSize().y, image.getPixelsPtr());

        // Start the clock
        sf::Clock clock;

        // Initialize the game instance
        Game game(window, FPS);

        //Loading Screen
        std::vector<std::string> loadingMessages = {
            "Loading Fonts...",
            "Loading Audio...",
            "Loading Assets...",
            "Loading Settings...",
            "Initialising Game...",
            "Loading Cards...",
            "Loading Forfeits..."
        };

        LoadingScreen loadingScreen(window, "../Data/Assets/gameLogo.png", loadingMessages);

        loadingScreen.setMessageCallback(0, [&game]() { return game.loadFonts();  });
        loadingScreen.setMessageCallback(1, [&game]() { return game.loadAudio();  });
        loadingScreen.setMessageCallback(2, [&game]() { return game.loadAssets();  });
        loadingScreen.setMessageCallback(3, [&game]() { return game.loadSettings("../Data/Settings.json");  });
        loadingScreen.setMessageCallback(4, [&game]() { return game.init();  });
        loadingScreen.setMessageCallback(5, [&game]() { return game.loadCards();  });
        loadingScreen.setMessageCallback(6, [&game]() {
            std::cout << "Starting to load forfeits..." << std::endl;
            bool success = game.loadForfeits();
            std::cout << "Forfeits loaded successfully: " << success << std::endl;
            return success;

            });


        //Loading screen loop
        while (window.isOpen()) {
            float deltaTime = clock.restart().asSeconds();
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window.close();
                }
            }

            //Update loading screen
            loadingScreen.update(deltaTime);

            //Render the loading screen
            loadingScreen.render();

            //Check if its all loaded
            if (loadingScreen.isLoadingComplete()) {
                break;
            }
        }

        std::cout << "Loading has completed!" << std::endl;

        /*
        if (!game.init()) {
            return 0; // Exit if the game initialization fails
        }
        */


        // Main game loop
        bool restartRequested = false; // Flag to indicate if restart is needed
        
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