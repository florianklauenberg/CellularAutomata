#include <iostream>
#include "SFML/Graphics.hpp"
#include "GameOfLife.hpp"

void inputHandler(sf::Event& event, GameOfLife& gol, bool& paused);

int main()
{
    // Create the main window
    sf::RenderWindow window(sf::VideoMode(1601, 901), "SFML window");
    window.setFramerateLimit(10);

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
                inputHandler(event, gameOfLife, simulationPaused);
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

// TODO
//   We need to think about GameState struct and give that to inputHandler
//   Alternatively use the GameOfLife class to handle GameState
void inputHandler(sf::Event& event, GameOfLife& gol, bool& paused) {
    std::cout << event.key.code << std::endl;
    switch(event.key.scancode)
    {
        case sf::Keyboard::Scan::Space:
            paused = !paused;
            break;
        case sf::Keyboard::Scan::R:
            if(paused)
                gol.randomizeBoard();
            break;
        case sf::Keyboard::Scan::C:
            if(paused)
                gol.clearBoard();
            break;
        case sf::Keyboard::Scan::F:
            if(paused)
                gol.update();
        default:
            break;
    }
}
