#ifndef CELLULARAUTOMATA_GAMEOFLIFE_HPP
#define CELLULARAUTOMATA_GAMEOFLIFE_HPP

#include <SFML/Graphics.hpp>
#include <iostream>

class GameOfLife
{
private:
    int rows;
    int cols;
    int tileSize = 3; // should be a divider of 1600 AND 900 and then one substracted from it
    int** currentBoard;
    int** nextBoard;
    sf::VertexArray quad;
public:
    GameOfLife(sf::RenderWindow& window);
    void update();
    void draw(sf::RenderWindow& window);
    void randomizeBoard();
    void clearBoard();
    int getLivingNeighborCount(int row, int col);
    void updateQuadsAndCurrentBoard();
};


#endif //CELLULARAUTOMATA_GAMEOFLIFE_HPP
