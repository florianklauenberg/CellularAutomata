#include <iostream>
#include "SFML/Graphics.hpp"
#include "GameOfLife.hpp"

int main()
{
    // Create the main window
    sf::RenderWindow window(sf::VideoMode(1600, 900), "SFML window");
    window.setFramerateLimit(15);

    // Seed rand() for the generation of randomness in starting cells
    // Bad seed / generation doesn't matter for my purpose
    srand(std::time(0));
    GameOfLife gameOfLife(window);

    // Start the game loop
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
                std::cout << "Click!" << std::endl;
            }
            else if (event.type == sf::Event::KeyPressed)
            {

            }
        }
        // Clear screen
        window.clear({66, 66, 66});

        // Draw Simulation
        gameOfLife.update();
        gameOfLife.draw(window);

        // Update the window
        window.display();
    }
    return EXIT_SUCCESS;
}
