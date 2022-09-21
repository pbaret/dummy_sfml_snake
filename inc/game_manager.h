#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

#include "game_state.h"

/**
 * @brief Game manager : handles all the application and game logic
 */
class GameManager
{
private:
    sf::RenderWindow * m_pt_display_window;   /**< Pointer to the display window of the game */
    dss::GameScreen m_current_screen;         /**< Current screen */

    sf::Font m_txt_font;        /**< Font to use for the different texts */

    sf::Text m_txt_title;       /**< Title of the game */
    sf::Text m_txt_body;        /**< Text to display info */
    sf::Text m_txt_footer;      /**< Footer text if needed */
    sf::Text m_txt_score;       /**< Text to display the score */
    sf::Text m_txt_highscore;   /**< Text to display the highscore */

public:
    /**
     * @brief Construct a new Game Manager object
     * 
     * @param pt_display_window : pointer to the display window that the game manager will use to display game updates.
     */
    GameManager(sf::RenderWindow * pt_display_window);

    /**
     * @brief Destroy the Game Manager object
     */
    ~GameManager();

    /**
     * @brief Process all the user inputs and events (Keyboard, mouse, window close etc...)
     */
    void ProcessUserInputs();

    /**
     * @brief Update display by rendering a full frame
     * @note clears the previous window (fill with black)
     */
    void UpdateDisplay();
};

