#pragma once

#include "global.h"
#include <SFML/Graphics.hpp>
#include <list>
#include "grid.h"

/**
 * @brief Sanke of the game
 */
class Snake
{
private:
    std::list<sf::Vector2u>     m_snake_body_pos;       /**< Positions of the snake body part in head to tail order in grid coordinate */
    Direction                   m_current_direction;    /**< Current moving direction of the snake*/
    Grid                        *m_pt_grid;             /**< Pointer to the game grid where the snake can move */

public:
    /**
     * @brief Construct a new Snake object
     * @param game_grid : pointer to the game grid where the snake can move
     */
    Snake(Grid * game_grid);

    /**
     * @brief Change the direction of the snake
     * 
     * @param new_dir : new direction
     */
    void ChangeDirection(Direction new_dir);

    /**
     * @brief Apply snake movements
     * @return true if everything went fine, false otherwise (gameover).
     */
    bool UpdateSnake();

    /**
     * @brief Draw the snake on the input render window
     * 
     * @param window : render window on which to draw the snake
     */
    void DrawSnake(sf::RenderWindow & window);

private:
    /**
     * @brief Find the next position of the head of the snake (which depend on the current position and the movement direction)
     * 
     * @return sf::Vector2u 
     */
    sf::Vector2u _FindNextHeadPosition();

};
