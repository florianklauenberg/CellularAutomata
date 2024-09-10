#ifndef CELLULARAUTOMATA_GAMEOFLIFE_HPP
#define CELLULARAUTOMATA_GAMEOFLIFE_HPP

#include <SFML/Graphics.hpp>
#include <iostream>

class GameOfLife
{
private:
    int rows;
    int cols;
    int tileSize = 4;
    int** currentBoard;
    int** nextBoard;
    sf::VertexArray quad;
public:
    GameOfLife(sf::RenderWindow& window);
    void update();
    void draw(sf::RenderWindow& window);
    int getLivingNeighborCount(int row, int col);
};


#endif //CELLULARAUTOMATA_GAMEOFLIFE_HPP
