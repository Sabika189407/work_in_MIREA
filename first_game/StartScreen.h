#pragma once
#include <SFML/Graphics.hpp>

class Start_screen
{
private:
    sf::Texture start_background_texture;
    sf::Sprite start_background_sprite;

    sf::Font start_font;
    sf::Text start_title_text;
    sf::Text start_subtitle_text;

    sf::RectangleShape start_btn;
    sf::Text start_btn_text;

public:
    Start_screen(float, float);
    bool is_start_clicked(sf::Vector2i);
    void render(sf::RenderWindow&);
};