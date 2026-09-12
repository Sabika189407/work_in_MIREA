#include "Registration.h"
#include <iostream>

Card_form::Card_form(float window_w, float window_h)
{
    reg_font.loadFromFile("assets/minecraft.ttf");

    //scales of card and card
    float card_w = 500.0f;
    float card_h = 300.0f;
    float card_x = (window_w - card_w) / 2.0f;
    float card_y = (window_h - card_h) / 2.0f;
    reg_card_background.setSize(sf::Vector2f(card_w, card_h));
    reg_card_background.setFillColor(sf::Color(240, 240, 240));
    reg_card_background.setOutlineThickness(4.0f);
    reg_card_background.setOutlineColor(sf::Color(180, 180, 180));
    reg_card_background.setPosition(card_x, card_y);

    // generate input field
    auto create_field = [&](float x, float y, float w, float h, std::string label_str, size_t max_c, Card_field type)
    {
        Input_box box;
        box.field_type = type;
        box.max_chars = max_c;

        box.box.setSize(sf::Vector2f(w, h));
        box.box.setFillColor(sf::Color::White);
        box.box.setOutlineThickness(2.0f);
        box.box.setOutlineColor(sf::Color(150, 150, 150));
        box.box.setPosition(card_x + x, card_y + y);

        box.label.setFont(reg_font);
        box.label.setString(label_str);
        box.label.setCharacterSize(14);
        box.label.setFillColor(sf::Color::Black);
        box.label.setPosition(card_x + x, card_y + y - 18.0f);

        box.text.setFont(reg_font);
        box.text.setCharacterSize(16);
        box.text.setFillColor(sf::Color::Black);
        box.text.setPosition(card_x + x + 5.0f, card_y + y + 2.0f);

        reg_fields.push_back(box);
    };

    //make input fields like in card
    create_field(30.0f, 50.0f, 320.0f, 30.0f, "Card Number", 16, Card_field::NUMBER);
    create_field(30.0f, 120.0f, 60.0f, 30.0f, "Month", 2, Card_field::MONTH);
    create_field(100.0f, 120.0f, 60.0f, 30.0f, "Year", 2, Card_field::YEAR);
    create_field(30.0f, 200.0f, 320.0f, 30.0f, "Cardholder Name", 20, Card_field::NAME);
    create_field(380.0f, 120.0f, 80.0f, 30.0f, "CVC/CVV", 3, Card_field::CVC);

    //backlight the first active input
    reg_fields[0].box.setOutlineColor(sf::Color::Blue);

    //registration button
    reg_submit_btn.setSize(sf::Vector2f(220.0f, 40.0f));
    reg_submit_btn.setFillColor(sf::Color(40, 160, 60));
    reg_submit_btn.setPosition(window_w / 2.0f - 110.0f, card_y + card_h + 20.0f);
    reg_submit_text.setFont(reg_font);
    reg_submit_text.setString("Register");
    reg_submit_text.setCharacterSize(18);
    reg_submit_text.setFillColor(sf::Color::White);
    sf::FloatRect b = reg_submit_text.getLocalBounds();
    reg_submit_text.setOrigin(b.left + b.width / 2.0f, b.top + b.height / 2.0f);
    reg_submit_text.setPosition(window_w / 2.0f, card_y + card_h + 40.0f);
}

void Card_form::handle_click(sf::Vector2i mouse_pos)
{
    sf::Vector2f m_pos(static_cast<float>(mouse_pos.x), static_cast<float>(mouse_pos.y));

    for (auto& field : reg_fields)
    {
        if (field.box.getGlobalBounds().contains(m_pos))
        {
            reg_active_field = field.field_type;
            field.box.setOutlineColor(sf::Color::Blue);
        }
        else
        {
            field.box.setOutlineColor(sf::Color(150, 150, 150));
        }
    }
}

void Card_form::handle_text_input(uint32_t unicode)
{
    for (auto& field : reg_fields)
    {
        if (field.field_type == reg_active_field)
        {
            //backspace
            if (unicode == 8)
            {
                if (!field.value.empty())
                {
                    field.value.pop_back();
                }
            } 
            //input text symbols
            else if (unicode >= 32 && unicode <= 126)
            {
                if (field.value.size() < field.max_chars)
                {
                    field.value += static_cast<char>(unicode);
                }
            }
            field.text.setString(field.value);
            break;
        }
    }
}

bool Card_form::is_submit_clicked(sf::Vector2i mouse_pos)
{
    sf::Vector2f m_pos(static_cast<float>(mouse_pos.x), static_cast<float>(mouse_pos.y));
    return reg_submit_btn.getGlobalBounds().contains(m_pos);
}

void Card_form::render(sf::RenderWindow& window)
{
    window.draw(reg_card_background);

    for (const auto& field : reg_fields)
    {
        window.draw(field.label);
        window.draw(field.box);
        window.draw(field.text);
    }

    window.draw(reg_submit_btn);
    window.draw(reg_submit_text);
}