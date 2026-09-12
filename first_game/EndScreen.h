#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class End_screen
{
private:
    float win_w;
    float win_h;

    sf::Texture victory_texture;
    sf::Texture game_over_texture;
    sf::Sprite background_sprite;
    bool has_background = false;

    sf::Font end_font;
    sf::Text end_title_text;
    sf::Text end_score_text;
    sf::Text end_time_text;

    sf::RectangleShape end_restart_btn;
    sf::Text end_restart_btn_text;

public:
    End_screen(float, float);
    void setup(bool is_victory, int score, float play_time);
    bool is_restart_clicked(sf::Vector2i mouse_pos);
    void render(sf::RenderWindow& window);
};