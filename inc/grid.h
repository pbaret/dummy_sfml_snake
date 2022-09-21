#pragma once

#include "global.h"
#include "grid_cell.h"
#include <array>
#include <random>
#include <SFML/Graphics.hpp>

/**
 * @brief Holds the game grid
 */
class Grid
{
private:
    std::array<std::array<GridCell, dss::width>, dss::height> m_grid; /**< 2D grid */
    std::random_device rd;  /**< to drop food randomly */
    std::mt19937 mt;        /**< to drop food randomly */
    std::uniform_int_distribution<> dist_x; /**< randomly generate x coordinate */
    std::uniform_int_distribution<> dist_y; /**< randomly generate y coordinate */
    sf::Vector2u m_food_pos;    /**< current position of the food item */

public:
    /**
     * @brief Construct a new Grid object
     */
    Grid();

    /**
     * @brief Empty all the grid cells
     */
    void ResetGrid();

    /**
     * @brief Randomly drop a food item somewhere on the grid.
     */
    void DropFood();

    /*
    GridCell operator()(const sf::Vector2u & pos)
    {
        return m_grid[pos.y][pos.x];
    }

    void SetGridCell(const sf::Vector2u & pos, GridCell value)
    {
        m_grid[pos.y][pos.x] = value;
    }*/
};