//
//  Game.cpp
//  SFML Game
//
//  Created by Joseph Herkness on 7/4/16.
//  Copyright © 2016 Joseph Herkness. All rights reserved.
//
//  Rules:
//  1. Any live cell with fewer than two live neighbours dies, as if caused by under-population.
//  2. Any live cell with two or three live neighbours lives on to the next generation.
//  3. Any live cell with more than three live neighbours dies, as if by over-population.
//  4. Any dead cell with exactly three live neighbours becomes a live cell, as if by reproduction.


#include "Grid.hpp"
#include <iostream>
    
Grid::Grid(int width, int height)
{
    this->width = width;
    this->height = height;
    this->paused = false;
    this->cells = new bool[width * height];
    this->newCells = new bool[width * height];
    
    // Initialize the array
    for(int i = 0; i < width * height; i ++){
        cells[i] = false;
        newCells[i] = false;
    }
    
}

void Grid::update()
{
    if (!paused)
    {
        // Update all cells to the new grid
        for(int i = 0; i < width*height; i++){
            int x = i % width;
            int y = i / width;
            
            bool alive = cells[i];
            int aliveNeighbors = neighbors(x, y);
            newCells[i] = shouldLive(alive, aliveNeighbors);
        }
        
        // Swap the grids
        bool *swap = cells;
        cells = newCells;
        newCells = swap;
    }
}

/**
 Returns a boolean indicating whether the cell should live based on the whether or not
 the cell is alive and the number of alive neighbors.
 
 @param  alive      A boolean indicating whether the cell is alive
 @param  neighbors  The number of alive neighbors
 @return A boolean indicating whether the cell should live
 */
bool Grid::shouldLive(bool alive, int neighbors)
{

    if(alive && neighbors < 2)
    {
        return false;
    }
    else if(alive && neighbors > 3)
    {
        return false;
    }
    else if(alive && (neighbors == 2 || neighbors == 3))
    {
        return true;
    }
    else if(!alive && neighbors == 3)
    {
        return true;
    }
    else {
        return false;
    }
}

/**
 Returns the number of alive neighbors at a specified position on the grid.
 
 @param  x the specified x position
 @param  y the specified y position
 @return The number of alive neighbors
 */
int Grid::neighbors(int x, int y)
{
    int num = 0;
    for (int i = -1; i <= 1; i++)
    {
        for (int j = -1; j <= 1; j++)
        {
            if (!(i == 0 && j == 0) && isAlive(x + i, y + j))
            {
                num++;
            }
        }
    }
    return num;
}

/**
 Returns a boolean indicating whether a cell is alive
 
 @param  x the specified x position
 @param  y the specified y position
 @return A boolean indicating the cells life
 */
bool Grid::isAlive(int x, int y)
{
    if(x == -1)x = width - 1;
    if(x == width)x = 0;
    if(y == -1)y = height - 1;
    if(y == height)y = 0;
    
    int pos = y * width + x;
    return cells[pos];
}

void Grid::toggleState(int x, int y)
{
    cells[y * width + x] = !cells[y * width + x];
}

void Grid::randomize(){
    for (int i = 0; i < width*height; i++) {
        cells[i] = rand()%2;
    }
}
