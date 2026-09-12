#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

enum class Menu_option
{
    NONE,
    CONTINUE,
    EXIT
};

class Pause_menu
{
private:
    sf::RectangleShape pause_overlay;
    sf::RectangleShape pause_panel;
    sf::Text paused_text;
    sf::Text pause_score_text;

    sf::RectangleShape pause_continue_btn;
    sf::Text pause_continue_text;

    sf::RectangleShape pause_exit_btn;
    sf::Text pause_exit_text;

    sf::Font font;

public:
    Pause_menu(float, float);

    void update_score(int);
    Menu_option handle_click(sf::Vector2i);
    void render(sf::RenderWindow&);
};