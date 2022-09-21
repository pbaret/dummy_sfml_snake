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

public:
    /**
     * @brief Construct a new Snake object
     */
    Snake();    

};
