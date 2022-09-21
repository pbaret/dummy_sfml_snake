#ifndef GLOBAL__H
#define GLOBAL__H

#include <stdint.h>
#include <string>
#include <SFML/Graphics.hpp>

/**
 * @brief Dummy SFML Snake namespace
 */
namespace dss
{
    constexpr uint32_t width = 40;  /**< Width of the Snake grid (the 2D array where the snake can move). */
    constexpr uint32_t height = 30; /**< Height of the Snake grid (the 2D array where the snake can move). */
    constexpr uint32_t scale = 20;  /**< Scaling factor for display. If the Snake grid is W*H cells, the display window will be (scale*W)*(scale*H) pixels. */

    /**
     * @brief Convert from grid space coordinates to display pixel coordinate.
     * 
     * @param grid_pos : input (x,y) position in the grid (cell unit)
     * @return sf::Vector2f : output (x,y) position in the display window (pixel unit)
     */
    inline sf::Vector2f GridPositionToWindowCoordinate(sf::Vector2u grid_pos)
    {
        return sf::Vector2f(static_cast<float>(grid_pos.x * scale), static_cast<float>(grid_pos.y * scale));
    }

    /**
     * @brief Convert from grid space coordinates to display pixel coordinate.
     * 
     * @param grid_pos_x : x position in grid cell unit
     * @param grid_pos_y : y position in grid cell unit
     * @return sf::Vector2f : output (x,y) position in the display window (pixel unit)
     */
    inline sf::Vector2f GridPositionToWindowCoordinate(uint32_t grid_pos_x, uint32_t grid_pos_y)
    {
        return GridPositionToWindowCoordinate(sf::Vector2u(grid_pos_x, grid_pos_y));
    }

    /**
     * @brief Local anchor to place displayable elements
     */
    enum class LocalOrigin
    {
        TopLeft, Top, TopRight,
        Left, Center, Right,
        BottomLeft, Bottom, BottomRight
    };

    /**
     * @brief Set the Text Local Origin 
     * 
     * @param txt : input/output text to process
     * @param anchor : new local origin to take
     */
    inline void SetTextLocalOrigin(sf::Text & txt, LocalOrigin anchor)
    {
        auto rect = txt.getLocalBounds();
        sf::Vector2f new_anchor(0,0);

        switch (anchor)
        {
        case LocalOrigin::TopLeft:
            new_anchor = sf::Vector2f(0,0);
            break;
        case LocalOrigin::Top:
            new_anchor = sf::Vector2f(rect.width/2,0);
            break;
        case LocalOrigin::TopRight:
            new_anchor = sf::Vector2f(rect.width,0);
            break;
        case LocalOrigin::Left:
            new_anchor = sf::Vector2f(0,rect.height/2);
            break;
        case LocalOrigin::Center:
            new_anchor = sf::Vector2f(rect.width/2,rect.height/2);
            break;
        case LocalOrigin::Right:
            new_anchor = sf::Vector2f(rect.width,rect.height/2);
            break;
        case LocalOrigin::BottomLeft:
            new_anchor = sf::Vector2f(0,rect.height);
            break;
        case LocalOrigin::Bottom:
            new_anchor = sf::Vector2f(rect.width/2,rect.height);
            break;
        case LocalOrigin::BottomRight:
            new_anchor = sf::Vector2f(rect.width,rect.height);
            break;
        
        default:
            break;
        }

        txt.setOrigin(new_anchor);
    }
}


#endif // GLOBAL__H
