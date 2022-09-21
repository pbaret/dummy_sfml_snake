#include "snake.h"

using namespace dss;

Snake::Snake()
{
    const sf::Vector2u initial_position = sf::Vector2u(width/2, height/2);        
    m_snake_body_pos.push_back(initial_position);
    m_current_direction = Direction::UP;
}

/*
void Snake::SetDirection(Direction new_dir)
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

/*   
void Snake::DrawSnakeOnWindow(sf::RenderWindow & window)
{
    window.clear(sf::Color::Black);
    for (auto& body_part : m_snake_body)
    {        
        body_part.setFillColor(sf::Color(150, 50, 250));
        window.draw(body_part);
    }
}

bool Snake::Move(Grid & grid, sf::RenderWindow & window)
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

    sf::CircleShape tmp     = m_snake_body.back();      // Former tail shape
    sf::Vector2u tmp_pos    = sf::Vector2u(future_x, future_y); // position in front of snake head (future head position)
    tmp.setPosition(GridPositionToWindowCoordinate(tmp_pos)); // set new shape to future head position

    GridCell front_cell = grid(tmp_pos);
    if (front_cell == GridCell::EMPTY)
    {
        // if future head pos is empty
        // then simple move forward
        const sf::Vector2u tail_pos = m_snake_body_pos.back(); // get current postion of tail
        m_snake_body.pop_back();                               // rm tail shape
        m_snake_body_pos.pop_back();                           // rm tail position
        grid.SetGridCell(tail_pos, GridCell::EMPTY);           // set tail grid cell empty        
    }
    else if (front_cell == GridCell::SNAKE_BODY)
    {
        // if future head pos contains snake body, then game over
        // loose
        return false;
    }
    else
    {
        // If food, don't rm tail, but still move head forward
        grid.DropFood(); // drop new food
    }
    
    // move forward
    m_snake_body.push_front(tmp);
    m_snake_body_pos.push_front(tmp_pos);
    grid.SetGridCell(tmp_pos, GridCell::SNAKE_BODY);
    return true;
}
*/