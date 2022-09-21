#include "game_manager.h"
#include "font-arial.h"
#include "global.h"

#include <iostream>
#include <string>

using namespace dss;

GameManager::GameManager(sf::RenderWindow * pt_display_window) :
    m_pt_display_window(pt_display_window)
{
    if (!m_txt_font.loadFromMemory(&arial_ttf, arial_ttf_len))
    {
        std::cerr << "problem with font" << std::endl;
    }

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

    m_txt_highscore = sf::Text(std::string("Highscore: ") + std::to_string(0), m_txt_font, 20);
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
        if (event.type == sf::Event::KeyPressed)
        {
            switch (event.key.code)
            {
                case sf::Keyboard::Up:
                {
                    std::cout << "UP pressed" << std::endl;
                }
                break;
                case sf::Keyboard::Down:
                {
                    std::cout << "DOWN pressed" << std::endl;
                }
                break;
                case sf::Keyboard::Left:
                {
                    std::cout << "LEFT pressed" << std::endl;
                }
                break;
                case sf::Keyboard::Right:
                {
                    std::cout << "RIGHT pressed" << std::endl;
                }
                break;
                default:
                break;
            }
        }

        // "close requested" event: we close the window
        if (event.type == sf::Event::Closed)
        {
            m_pt_display_window->close();
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
            
        }
    }
        break;
    
    default:
        break;
    }

    m_pt_display_window->display();
}