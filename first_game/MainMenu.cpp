#include "MainMenu.h"

Main_menu::Main_menu(float window_w, float window_h)
{
    main_font.loadFromFile("assets/minecraft.ttf");

    float center_x = window_w / 2.0f;
    float center_y = window_h / 2.0f;

    //main menu header
    main_title_text.setFont(main_font);
    main_title_text.setString("SAVE STROLLER");
    main_title_text.setCharacterSize(48);
    main_title_text.setFillColor(sf::Color::Cyan);
    sf::FloatRect title_b = main_title_text.getLocalBounds();
    main_title_text.setOrigin(title_b.left + title_b.width / 2.0f, title_b.top + title_b.height / 2.0f);
    main_title_text.setPosition(center_x, center_y - 120.0f);

    //play button
    main_play_btn.setSize(sf::Vector2f(240.0f, 50.0f));
    main_play_btn.setFillColor(sf::Color(40, 160, 60));
    main_play_btn.setOutlineThickness(2.0f);
    main_play_btn.setOutlineColor(sf::Color::White);
    main_play_btn.setOrigin(120.0f, 25.0f);
    main_play_btn.setPosition(center_x, center_y);

    main_play_btn_text.setFont(main_font);
    main_play_btn_text.setString("PLAY");
    main_play_btn_text.setCharacterSize(22);
    main_play_btn_text.setFillColor(sf::Color::White);
    sf::FloatRect play_b = main_play_btn_text.getLocalBounds();
    main_play_btn_text.setOrigin(play_b.left + play_b.width / 2.0f, play_b.top + play_b.height / 2.0f);
    main_play_btn_text.setPosition(center_x, center_y);

    //exit button
    main_exit_btn.setSize(sf::Vector2f(240.0f, 50.0f));
    main_exit_btn.setFillColor(sf::Color(180, 40, 40));
    main_exit_btn.setOutlineThickness(2.0f);
    main_exit_btn.setOutlineColor(sf::Color::White);
    main_exit_btn.setOrigin(120.0f, 25.0f);
    main_exit_btn.setPosition(center_x, center_y + 80.0f);

    main_exit_btn_text.setFont(main_font);
    main_exit_btn_text.setString("EXIT");
    main_exit_btn_text.setCharacterSize(22);
    main_exit_btn_text.setFillColor(sf::Color::White);
    sf::FloatRect exit_b = main_exit_btn_text.getLocalBounds();
    main_exit_btn_text.setOrigin(exit_b.left + exit_b.width / 2.0f, exit_b.top + exit_b.height / 2.0f);
    main_exit_btn_text.setPosition(center_x, center_y + 80.0f);
}

Main_menu_option Main_menu::handle_click(sf::Vector2i mouse_pos)
{
    sf::Vector2f m_pos(static_cast<float>(mouse_pos.x), static_cast<float>(mouse_pos.y));

    if (main_play_btn.getGlobalBounds().contains(m_pos))
    {
        return Main_menu_option::PLAY;
    }
    if (main_exit_btn.getGlobalBounds().contains(m_pos))
    {
        return Main_menu_option::EXIT;
    }
    return Main_menu_option::NONE;
}

void Main_menu::render(sf::RenderWindow& window)
{
    window.draw(main_title_text);
    window.draw(main_play_btn);
    window.draw(main_play_btn_text);
    window.draw(main_exit_btn);
    window.draw(main_exit_btn_text);
}