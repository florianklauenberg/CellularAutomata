#include "GameOfLife.hpp"

GameOfLife::GameOfLife(sf::RenderWindow &window)
{
    // Initialize cols and rows
    int width = window.getSize().x;
    int height = window.getSize().y;        // TODO
    cols = (width - 1) / (tileSize + 1);    //  Problem: Because of the cellborders it is harder to calculate cols and rows properly
    rows = (height - 1) / (tileSize + 1);   //  First implementation just cut off some pixels (or at small tileSize cells) on the right and bottom
                                            //  Now we have to add one to our ScreenSize in the main and choose the tileSize carefully, but it works as intended

    // std::cout << "rows: " << rows << " cols: " << cols << std::endl;

    // Initialize Board
    currentBoard = new int* [rows];
    nextBoard = new int* [rows];
    for(int row = 0; row < rows; row++)
    {
        currentBoard[row] = new int[cols];
        nextBoard[row] = new int[cols];
        for(int col = 0; col < cols; col++)
        {
            currentBoard[row][col] = 0;
            // Approximately 30% of Cells (randomly chosen) set alive
            if(rand() % 100 < 30)
                currentBoard[row][col] = 1;
            nextBoard[row][col] = currentBoard[row][col];
        }
    }

    // Initialize VertexArray
    quad = sf::VertexArray(sf::Quads, rows * cols * 4);
    int currentCellStartingQuad = 0;
    for(int row = 0; row < rows; row++)
    {
        for(int col = 0; col < cols; col++)
        {
            float screenPosX = 1 + col * (tileSize + 1);
            float screenPosY = 1 + row * (tileSize + 1);
            // Give Quadpositions into Array (Clockwise)
            quad[currentCellStartingQuad]    .position = sf::Vector2f(screenPosX, screenPosY);
            quad[currentCellStartingQuad + 1].position = sf::Vector2f(screenPosX + tileSize, screenPosY);
            quad[currentCellStartingQuad + 2].position = sf::Vector2f(screenPosX + tileSize, screenPosY + tileSize);
            quad[currentCellStartingQuad + 3].position = sf::Vector2f(screenPosX, screenPosY + tileSize);
            // Give Quadcolors into Array
            quad[currentCellStartingQuad]    .color = sf::Color::White;
            quad[currentCellStartingQuad + 1].color = sf::Color::White;
            quad[currentCellStartingQuad + 2].color = sf::Color::White;
            quad[currentCellStartingQuad + 3].color = sf::Color::White;
            // Increment currentCellStartingQuad by 4 because 4 Quads per Cell
            currentCellStartingQuad += 4;
        }
    }
}

void GameOfLife::draw(sf::RenderWindow& window)
{
    window.draw(quad);
}

void GameOfLife::update()
{
    // Logical rules of Game
     for(int row = 0; row < rows; row++)
     {
         for(int col = 0; col < cols; col++)
         {
             int neighborCount = getLivingNeighborCount(row, col);

             // Rules:
             //Any live cell with fewer than two live neighbours dies, as if by underpopulation.
             //Any live cell with two or three live neighbours lives on to the next generation.
             //Any live cell with more than three live neighbours dies, as if by overpopulation.
             if(currentBoard[row][col] == 1)
             {
                 if(neighborCount < 2)
                     nextBoard[row][col] = 0;
                 // if(neighborCount == 2 || neighborCount == 3)
                 //    nextGrid[row][col] = 1
                 // Not needed because no change and every other case is handled
                 if(neighborCount > 3)
                     nextBoard[row][col] = 0;
             }
             //Any dead cell with exactly three live neighbours becomes a live cell, as if by reproduction.
             else if(neighborCount == 3)
             {
                 nextBoard[row][col] = 1;
             }
         }
     }
    updateQuadsAndCurrentBoard();
}

int GameOfLife::getLivingNeighborCount(int row, int col)
{
    // Define all 8 possible offsets for neighbors
    int rowOffsets[8] = {-1, -1, -1, 0 , 0, 1, 1, 1};
    int colOffsets[8] = {-1 , 0, 1, -1 , 1, -1 , 0, 1};

    // Go through every neighbor
    int count = 0;
    for(int offsetCounter = 0; offsetCounter < 8; offsetCounter++)
    {
        // Calculate current neighbor with offsets
        int neighborRow = row + rowOffsets[offsetCounter];
        int neighborCol = col + colOffsets[offsetCounter];
        // Check board constraints
        if(neighborRow < 0 || neighborRow > rows - 1 || neighborCol < 0 || neighborCol > cols - 1)
            continue;
        // Count
        if(currentBoard[neighborRow][neighborCol] == 1)
            count++;
    }
    return count;
}

void GameOfLife::clearBoard()
{
    for(int row = 0; row < rows; row++)
    {
        for(int col = 0; col < cols; col++)
        {
            currentBoard[row][col] = 0;
            nextBoard[row][col] = 0;
        }
    }
    updateQuadsAndCurrentBoard();
}

void GameOfLife::randomizeBoard()
{
    for(int row = 0; row < rows; row++)
    {
        for(int col = 0; col < cols; col++)
        {
            // Approximately 30% of Cells (randomly chosen) set alrive
            if(rand() % 100 < 30)
                currentBoard[row][col] = 1;
            else
                currentBoard[row][col] = 0;
            nextBoard[row][col] = currentBoard[row][col];
        }
    }
    updateQuadsAndCurrentBoard();
}

void GameOfLife::updateQuadsAndCurrentBoard()
{
    int currentCellStartingQuad = 0;
    for(int row = 0; row < rows; row++)
    {
        for(int col = 0; col < cols; col++)
        {
            currentBoard[row][col] = nextBoard[row][col];
            if(currentBoard[row][col] == 1)
            {
                quad[currentCellStartingQuad].color = sf::Color::Black;
                quad[currentCellStartingQuad + 1].color = sf::Color::Black;
                quad[currentCellStartingQuad + 2].color = sf::Color::Black;
                quad[currentCellStartingQuad + 3].color = sf::Color::Black;
            }
            else
            {
                quad[currentCellStartingQuad].color = sf::Color::White;
                quad[currentCellStartingQuad + 1].color = sf::Color::White;
                quad[currentCellStartingQuad + 2].color = sf::Color::White;
                quad[currentCellStartingQuad + 3].color = sf::Color::White;
            }
            // Increment currentCellStartingQuad by 4 because 4 Quads per Cell
            currentCellStartingQuad += 4;
        }
    }
}

