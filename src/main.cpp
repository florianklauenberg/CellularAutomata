#include <iostream>
#include "SFML/Graphics.hpp"
#include "GameOfLife.hpp"

void inputHandler(sf::Event event);

int main()
{
    // Create the main window
    sf::RenderWindow window(sf::VideoMode(1600, 900), "SFML window");
    window.setFramerateLimit(15);

    // Seed rand() for the generation of randomness in starting cells
    // Bad seed / generation doesn't matter for my purpose
    srand(std::time(0));
    GameOfLife gameOfLife(window);

    // TODO Add some kind of gamestate to track important events
    // Initialize gameState and constants
    bool mouseButtonPressed = false;
    bool simulationPaused = false;
    sf::Color CELL_BORDER_COLOR = {0, 0, 0};

    // Start the game loop blablabla
    while (window.isOpen())
    {
        // Process events
        sf::Event event {};
        while (window.pollEvent(event))
        {
            // Close window: exit
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
            else if (event.type == sf::Event::MouseButtonPressed)
            {
                mouseButtonPressed = true;
                std::cout << "Click!" << std::endl;
            }
            else if (event.type == sf::Event::MouseButtonReleased)
            {
                mouseButtonPressed = false;
                std::cout << "Unclick" << std::endl;
            }
            else if (event.type == sf::Event::KeyPressed)
            {
                // TODO
                //  Implement some form of inputhandling
                //  What inputs do I even need to handle?
                if(event.key.scancode == sf::Keyboard::Scan::Space)
                {
                    simulationPaused = !simulationPaused;
                }
                inputHandler(event);
            }
        }

        // Clear screen
        window.clear(CELL_BORDER_COLOR);

        // Run and draw simulation
        if(simulationPaused)
        {
            // TODO If pause we want to use the mouse to manually create a Board state
        }
        else
        {
            gameOfLife.update();
        }
        gameOfLife.draw(window);

        // Update the window
        window.display();
    }
    return EXIT_SUCCESS;
}

void inputHandler(sf::Event event) {
    std::cout << event.key.code << std::endl;
}
