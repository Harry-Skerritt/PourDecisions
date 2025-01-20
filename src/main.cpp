#include <SFML/Graphics.hpp>
#include <iostream>
#include "Game.h"

int main()
{
    const std::string VERSION_NO = "beta-0.1.2";
    const sf::String WINDOW_TITLE = "Pour Decisions - " + VERSION_NO;
    //Creates the window
    sf::RenderWindow window(sf::VideoMode({1080u, 720u}), WINDOW_TITLE);
    window.setFramerateLimit(60);

    auto image = sf::Image{};
    if (!image.loadFromFile("../Data/Assets/Favicon.png")) {
        std::cout << "App Icon did not load" << std::endl;
    }

    window.setIcon(image.getSize().x, image.getSize().y, image.getPixelsPtr());

    //Starts clock
    sf::Clock clock;

    //Initialises instance of game
    Game game(window);


    //Game init
    if (!game.init()) {
        return 0;
    }

    while (window.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;

        //calculate delta time
        sf::Time time = clock.restart();
        float dt = time.asSeconds();

        //'process inputs' element of the game loop
        while (window.pollEvent(event))
        {

            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
            {
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

        }


        //'update' element of the game loop
        game.update(dt);

        window.clear(sf::Color::Black);
        //game.setBackgroundGradient(window); //Draw the background gradient -> only for the home screen - add this functionality later

        //'render' element of the game loop
        game.render();
        window.display();
    }

    return 0;
}
