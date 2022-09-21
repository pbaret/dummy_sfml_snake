#pragma once

/**
 * @brief Grid cell possible values
 */
enum class GridCell 
{
    EMPTY,      /**< Empty grid cell */
    FOOD,       /**< Food item */
    SNAKE_BODY  /**< Snake body parts */
};

/**
 * @brief 
 * 4 possible moving directions for the snake
 */
enum class Direction
{
    UP, DOWN, LEFT, RIGHT
};
