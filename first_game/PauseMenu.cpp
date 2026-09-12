#include "PauseMenu.h"

Pause_menu::Pause_menu(float window_w, float window_h)
{
    font.loadFromFile("assets/minecraft.ttf");

    pause_overlay.setSize(sf::Vector2f(window_w, window_h)); //pause overlay fullscreen
    pause_overlay.setFillColor(sf::Color(0, 0, 0, 150));

    pause_panel.setSize(sf::Vector2f(320.0f, 260.0f)); //pause panel
    pause_panel.setFillColor(sf::Color(30, 30, 30));
    pause_panel.setOutlineThickness(3.0f);
    pause_panel.setOutlineColor(sf::Color::Blue);
    pause_panel.setPosition((window_w - 320.0f) / 2.0f, (window_h - 260.0f) / 2.0f);

    float center_x = window_w / 2.0f;
    float panel_top = pause_panel.getPosition().y;

    paused_text.setFont(font); //text PAUSED
    paused_text.setString("PAUSED");
    paused_text.setCharacterSize(32);
    paused_text.setFillColor(sf::Color::Yellow);
    sf::FloatRect title_bounds = paused_text.getLocalBounds();
    paused_text.setOrigin(title_bounds.width / 2.0f, 0.0f);
    paused_text.setPosition(center_x, panel_top + 15.0f);

    pause_score_text.setFont(font); //score bar in pause panel
    pause_score_text.setCharacterSize(20);
    pause_score_text.setFillColor(sf::Color::White);
    pause_score_text.setPosition(center_x - 100.0f, panel_top + 65.0f);

    pause_continue_btn.setSize(sf::Vector2f(220.0f, 40.0f)); //continue button
    pause_continue_btn.setFillColor(sf::Color(60, 60, 60));
    pause_continue_btn.setOrigin(220.0f / 2.0f, 40.0f / 2.0f);
    pause_continue_btn.setPosition(center_x, panel_top + 135.0f);
    pause_continue_text.setFont(font);
    pause_continue_text.setString("Continue");
    pause_continue_text.setCharacterSize(18);
    pause_continue_text.setFillColor(sf::Color::White);
    sf::FloatRect cont_bounds = pause_continue_text.getLocalBounds();
    pause_continue_text.setOrigin(cont_bounds.left + cont_bounds.width / 2.0f, cont_bounds.top + cont_bounds.height / 2.0f);
    pause_continue_text.setPosition(center_x, panel_top + 135.0f);

    pause_exit_btn.setSize(sf::Vector2f(220.0f, 40.0f)); //exit button
    pause_exit_btn.setFillColor(sf::Color(60, 60, 60));
    pause_exit_btn.setPosition(center_x - 110.0f, panel_top + 175.0f);
    pause_exit_text.setFont(font);
    pause_exit_text.setString("Leave the Game");
    pause_exit_text.setCharacterSize(18);
    pause_exit_text.setFillColor(sf::Color::White);
    sf::FloatRect exit_b = pause_exit_text.getLocalBounds();
    pause_exit_text.setOrigin(exit_b.width / 2.0f, exit_b.height / 2.0f);
    pause_exit_text.setPosition(center_x, panel_top + 190.0f);
}

void Pause_menu::update_score(int score)
{
    pause_score_text.setString("Score: " + std::to_string(score));
}

Menu_option Pause_menu::handle_click(sf::Vector2i mouse_pos)
{
    sf::Vector2f m_pos(static_cast<float>(mouse_pos.x), static_cast<float>(mouse_pos.y));

    if (pause_continue_btn.getGlobalBounds().contains(m_pos))
    {
        return Menu_option::CONTINUE;
    }
    if (pause_exit_btn.getGlobalBounds().contains(m_pos))
    {
        return Menu_option::EXIT;
    }
    return Menu_option::NONE;
}

void Pause_menu::render(sf::RenderWindow& window)
{
    window.draw(pause_overlay);
    window.draw(pause_panel);
    window.draw(paused_text);
    window.draw(pause_score_text);

    window.draw(pause_continue_btn);
    window.draw(pause_continue_text);

    window.draw(pause_exit_btn);
    window.draw(pause_exit_text);
}