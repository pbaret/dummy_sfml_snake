#include "snake.h"

using namespace dss;


Snake::Snake(Grid * game_grid) :m_pt_grid(game_grid)
{
    const sf::Vector2u initial_position = sf::Vector2u(width/2, height/2);        
    m_snake_body_pos.push_back(initial_position);
    m_current_direction = Direction::UP;
}


bool Snake::UpdateSnake()
{
    const auto current_tail_position = m_snake_body_pos.back();
    auto next_head_position = _FindNextHeadPosition();

    GridCell next_head_position_cell_value = m_pt_grid->operator()(next_head_position);
    if ((next_head_position_cell_value == GridCell::EMPTY) ||
        ((next_head_position_cell_value == GridCell::SNAKE_BODY) && (next_head_position == current_tail_position)))
    {
        // if future head pos is empty
        // then simple move forward
        const sf::Vector2u tail_pos = m_snake_body_pos.back(); // get current postion of tail

        m_snake_body_pos.pop_back();                          // rm tail position
        m_pt_grid->SetGridCell(tail_pos, GridCell::EMPTY);    // set tail grid cell empty        
    }
    else if (next_head_position_cell_value == GridCell::SNAKE_BODY)
    {
        // if future head pos contains snake body, then game over
        // loose
        return false;
    }
    else // GridCell::Food
    {
        // If food, don't rm tail, but still move head forward
        // As food will be eaten, we need to drop new food item

        if (m_snake_body_pos.size() == (dss::height * dss::width - 1))
        {
            return false;   // Grid is full
        }
        else
        {
            m_pt_grid->DropFood(); // drop new food
        }
    }
    
    // move forward
    m_snake_body_pos.push_front(next_head_position);
    m_pt_grid->SetGridCell(next_head_position, GridCell::SNAKE_BODY);
    return true;
}


sf::Vector2u Snake::_FindNextHeadPosition()
{
    sf::Vector2u current_head_pos = m_snake_body_pos.front();

    uint32_t future_x = current_head_pos.x;
    uint32_t future_y = current_head_pos.y;

    switch (m_current_direction)
    {
    case Direction::UP:
    {
        if (future_y == 0)
        {
            future_y = height - 1;
        }
        else
        {
            --future_y;
        }
    }
    break;
    case Direction::DOWN:
    {
        if (future_y == height - 1)
        {
            future_y = 0;
        }
        else
        {
            ++future_y;
        }
    }
    break;
    case Direction::LEFT:
    {
        if (future_x == 0)
        {
            future_x = width - 1;
        }
        else
        {
            --future_x;
        }
    }
    break;
    case Direction::RIGHT:
    {
        if (future_x == width - 1)
        {
            future_x = 0;
        }
        else
        {
            ++future_x;
        }
    }
    break;
    
    default:
        break;
    }

    return sf::Vector2u(future_x, future_y);
}


void Snake::DrawSnake(sf::RenderWindow & window)
{
    sf::CircleShape shape = sf::CircleShape(scale/2, 15);
    shape.setFillColor(snake_color);

    for (const auto & pos : m_snake_body_pos)
    {
        shape.setPosition(ToFloatVector(pos, scale));
        window.draw(shape);
    }
}


void Snake::ChangeDirection(Direction new_dir)
{
    if (new_dir == m_current_direction)
    {
        return;
    }
    if ((m_current_direction == Direction::DOWN) || (m_current_direction == Direction::UP))
    {
        if ((new_dir == Direction::LEFT) || (new_dir == Direction::RIGHT))
        {
            m_current_direction = new_dir;
        }
    }
    else
    {
        if ((new_dir == Direction::UP) || (new_dir == Direction::DOWN))
        {
            m_current_direction = new_dir;
        }
    }
}
