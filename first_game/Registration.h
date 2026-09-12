#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

enum class Card_field //registration menu
{
    NUMBER,
    MONTH,
    YEAR,
    NAME,
    CVC,
    NONE
};

struct Input_box //input label
{
    sf::RectangleShape box;
    sf::Text text;
    sf::Text label;
    std::string value;
    size_t max_chars;
    Card_field field_type;
};

class Card_form
{
private:
    sf::RectangleShape reg_card_background;
    sf::RectangleShape reg_magnetic_stripe; //magnitnaya polosa
    sf::Font reg_font;

    std::vector<Input_box> reg_fields;
    Card_field reg_active_field = Card_field::NUMBER;

    sf::RectangleShape reg_submit_btn;
    sf::Text reg_submit_text;

public:
    Card_form(float, float);
    void handle_click(sf::Vector2i);
    void handle_text_input(uint32_t);
    bool is_submit_clicked(sf::Vector2i);
    void render(sf::RenderWindow&);
};