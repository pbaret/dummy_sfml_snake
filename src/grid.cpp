#include "grid.h"

using namespace dss;

Grid::Grid() : mt(rd())
{
    ResetGrid();
    dist_x = std::uniform_int_distribution<>(0, width-1);
    dist_y = std::uniform_int_distribution<>(0, height-1);
}

void Grid::ResetGrid()
{
    for (auto& l : m_grid)
    {
        l.fill(GridCell::EMPTY);
    }
}

void Grid::DropFood()
{
    bool found_empty_pos = false;
    while (!found_empty_pos)
    {
        int x = dist_x(mt);
        int y = dist_y(mt);
        if (m_grid[y][x] == GridCell::EMPTY)
        {
            found_empty_pos = true;
            m_grid[y][x] = GridCell::FOOD;
            m_food_pos = sf::Vector2u(x, y);
        }
    }
}

void Grid::DrawFoodItem(sf::RenderWindow & window)
{
    sf::CircleShape shape = sf::CircleShape(scale/2, 15);
    shape.setFillColor(food_color);
    shape.setPosition(ToFloatVector(m_food_pos, scale));

    window.draw(shape);
}