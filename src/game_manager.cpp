#include "game_manager.h"
#include "font-arial.h"
#include "global.h"

#include <iostream>
#include <string>

using namespace dss;

GameManager::GameManager(sf::RenderWindow * pt_display_window) :
    m_pt_display_window(pt_display_window),
    m_grid(),
    m_snake(&m_grid)
{
    if (!m_txt_font.loadFromMemory(&arial_ttf, arial_ttf_len))
    {
        std::cerr << "problem with font" << std::endl;
    }

    m_highscore = LoadHighScore();

    m_current_screen = GameScreen::HOME;

    m_txt_title = sf::Text("Dummy SFML Snake", m_txt_font, 50);
    SetTextLocalOrigin(m_txt_title, LocalOrigin::Top);
    m_txt_title.setPosition(GridPositionToWindowCoordinate((width)/2, 0));
    m_txt_title.setStyle(sf::Text::Bold);
    m_txt_title.setFillColor(sf::Color::Red);

    m_txt_body = sf::Text("Press 'P' to play/pause\nControl with ARROW keys", m_txt_font, 20);
    SetTextLocalOrigin(m_txt_body, LocalOrigin::Center);
    m_txt_body.setPosition(GridPositionToWindowCoordinate((width)/2, 10));
    m_txt_body.setFillColor(sf::Color(128,0,0));
    

    m_txt_footer = sf::Text("Developped by Pierre BARET - WTFPL License", m_txt_font, 20);
    SetTextLocalOrigin(m_txt_footer, LocalOrigin::Bottom);
    m_txt_footer.setPosition(GridPositionToWindowCoordinate((width)/2, (height - 1)));
    m_txt_footer.setFillColor(sf::Color(128,0,255));

    
    m_txt_score = sf::Text(std::to_string(0), m_txt_font, 20);
    SetTextLocalOrigin(m_txt_score, LocalOrigin::TopRight);
    m_txt_score.setPosition(GridPositionToWindowCoordinate((width-2), 4));
    m_txt_score.setFillColor(sf::Color(128,255,255));

    m_txt_highscore = sf::Text(std::string("Highscore: ") + std::to_string(m_highscore), m_txt_font, 20);
    SetTextLocalOrigin(m_txt_highscore, LocalOrigin::BottomRight);
    m_txt_highscore.setPosition(GridPositionToWindowCoordinate((width - 2), (height - 4)));
    m_txt_highscore.setFillColor(sf::Color(128,255,255));
}


GameManager::~GameManager()
{
}


void GameManager::ProcessUserInputs()
{
    // check all the window's events that were triggered since the last iteration of the loop
    sf::Event event;
    while (m_pt_display_window->pollEvent(event))
    {
        switch (m_current_screen)
        {
        case GameScreen::HOME :
            ProcessEventHome(event);
            break;
        case GameScreen::GAME :
            ProcessEventGame(event);
            break;
        case GameScreen::PAUSE :
            ProcessEventPause(event);
            break;
        
        default:
            break;
        }

        // "close requested" event: we close the window
        if (event.type == sf::Event::Closed)
        {
            m_pt_display_window->close();
        }
    }
}


void GameManager::ProcessEventHome(sf::Event & event)
{
    if (event.type == sf::Event::KeyPressed)
        {
            switch (event.key.code)
            {
                case sf::Keyboard::P:
                {
                    m_current_screen = GameScreen::GAME;
                    m_grid.ResetGrid();
                    m_grid.DropFood();
                    m_snake = Snake(&m_grid);
                }
                break;
                default:
                break;
            }
        }
}


void GameManager::ProcessEventGame(sf::Event & event)
{
    if (event.type == sf::Event::KeyPressed)
    {
        switch (event.key.code)
        {
            case sf::Keyboard::Up:
            {
                std::cout << "UP pressed" << std::endl;
                m_snake.ChangeDirection(Direction::UP);
                m_snake.UpdateSnake();
            }
            break;
            case sf::Keyboard::Down:
            {
                std::cout << "DOWN pressed" << std::endl;
                m_snake.ChangeDirection(Direction::DOWN);
                m_snake.UpdateSnake();
            }
            break;
            case sf::Keyboard::Left:
            {
                std::cout << "LEFT pressed" << std::endl;
                m_snake.ChangeDirection(Direction::LEFT);
                m_snake.UpdateSnake();
            }
            break;
            case sf::Keyboard::Right:
            {
                std::cout << "RIGHT pressed" << std::endl;
                m_snake.ChangeDirection(Direction::RIGHT);
                m_snake.UpdateSnake();
            }
            break;
            case sf::Keyboard::P:
            {
                m_txt_body = sf::Text("PAUSE \n Press 'P' to resume", m_txt_font, 30);
                SetTextLocalOrigin(m_txt_body, LocalOrigin::Center);
                m_txt_body.setPosition(GridPositionToWindowCoordinate((width)/2, (height/2)));
                m_txt_body.setFillColor(sf::Color(128,0,0));

                m_current_screen = GameScreen::PAUSE;
            }
            break;
            default:
            break;
        }
    }
}


void GameManager::ProcessEventPause(sf::Event & event)
{
    if (event.type == sf::Event::KeyPressed)
    {
        if (event.key.code == sf::Keyboard::P)
        {
            m_current_screen = GameScreen::GAME;
            m_txt_body = sf::Text("Press 'P' to play/pause\nControl with ARROW keys", m_txt_font, 20);
            SetTextLocalOrigin(m_txt_body, LocalOrigin::Center);
            m_txt_body.setPosition(GridPositionToWindowCoordinate((width)/2, 10));
            m_txt_body.setFillColor(sf::Color(128,0,0));
        }
    }
}

void GameManager::UpdateGameState()
{
    if (m_current_screen == GameScreen::GAME)
    {
        bool game_over = !m_snake.UpdateSnake();
        const uint32_t current_score = m_snake.GetCurrentScore();
        m_txt_score.setString(sf::String(std::to_string(current_score)));

        if (game_over)
        {
            if (current_score > m_highscore)
            {
                m_highscore = current_score;
                m_txt_highscore.setString(sf::String(std::string("Highscore: ") + std::to_string(m_highscore)));
                // TODO save highscore to disk
            }
            m_txt_title.setString("Game Over !");
            SetTextLocalOrigin(m_txt_title, LocalOrigin::Top);
            m_txt_title.setPosition(GridPositionToWindowCoordinate((width)/2, 0));

            m_current_screen = GameScreen::HOME;
        }
    }    
}

void GameManager::UpdateDisplay()
{
    m_pt_display_window->clear(sf::Color::Black);

    switch (m_current_screen)
    {
    case GameScreen::HOME :
    {
        m_pt_display_window->draw(m_txt_title);
        m_pt_display_window->draw(m_txt_body);
        m_pt_display_window->draw(m_txt_footer);
        m_pt_display_window->draw(m_txt_highscore);

        if (m_txt_title.getString() == sf::String("Game Over !"))
        {
            m_pt_display_window->draw(m_txt_score);
        }
    }
        break;
    case GameScreen::GAME :
    {
        m_grid.DrawFoodItem(*m_pt_display_window);
        m_snake.DrawSnake(*m_pt_display_window);
        m_pt_display_window->draw(m_txt_score);
    }
        break;
    case GameScreen::PAUSE :
    {
        m_pt_display_window->draw(m_txt_score);
        m_grid.DrawFoodItem(*m_pt_display_window);
        m_snake.DrawSnake(*m_pt_display_window);
        m_pt_display_window->draw(m_txt_body);
    }
        break;
    
    default:
        break;
    }

    m_pt_display_window->display();
}


uint32_t GameManager::LoadHighScore()
{
    // TODO
    return 0;
}