#pragma once
#include <SFML/Graphics.hpp>

enum class Main_menu_option
{
    NONE,
    PLAY,
    EXIT
};

class Main_menu
{
private:
    sf::Font main_font;
    sf::Text main_title_text;

    sf::RectangleShape main_play_btn;
    sf::Text main_play_btn_text;

    sf::RectangleShape main_exit_btn;
    sf::Text main_exit_btn_text;

public:
    Main_menu(float, float);
    Main_menu_option handle_click(sf::Vector2i);
    void render(sf::RenderWindow&);
};