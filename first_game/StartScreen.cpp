#include "StartScreen.h"

Start_screen::Start_screen(float window_w, float window_h)
{
    if (start_background_texture.loadFromFile("assets/start_screen_background.png"))
    {
        start_background_sprite.setTexture(start_background_texture);
        sf::Vector2u texture_size = start_background_texture.getSize();
        start_background_sprite.setScale(window_w / static_cast<float>(texture_size.x), window_h / static_cast<float>(texture_size.y));
    }
    

    start_font.loadFromFile("assets/minecraft.ttf");

    float center_x = window_w / 2.0f;
    float center_y = window_h / 2.0f;

    //main name
    start_title_text.setFont(start_font);
    start_title_text.setString("STROLLER: CHILDHOOD");
    start_title_text.setCharacterSize(42);
    start_title_text.setFillColor(sf::Color::Yellow);
    sf::FloatRect title_b = start_title_text.getLocalBounds();
    start_title_text.setOrigin(title_b.left + title_b.width / 2.0f, title_b.top + title_b.height / 2.0f);
    start_title_text.setPosition(center_x, center_y - 120.0f);

    //subname
    start_subtitle_text.setFont(start_font);
    start_subtitle_text.setString("Welcome to the internet maboi!!!");
    start_subtitle_text.setCharacterSize(20);
    start_subtitle_text.setFillColor(sf::Color::White);
    sf::FloatRect sub_b = start_subtitle_text.getLocalBounds();
    start_subtitle_text.setOrigin(sub_b.left + sub_b.width / 2.0f, sub_b.top + sub_b.height / 2.0f);
    start_subtitle_text.setPosition(center_x, center_y - 60.0f);

    //registration button
    start_btn.setSize(sf::Vector2f(280.0f, 50.0f));
    start_btn.setFillColor(sf::Color(40, 160, 60));
    start_btn.setOutlineThickness(3.0f);
    start_btn.setOutlineColor(sf::Color::White);
    start_btn.setOrigin(140.0f, 25.0f);
    start_btn.setPosition(center_x, center_y + 40.0f);

    //text on the registration button
    start_btn_text.setFont(start_font);
    start_btn_text.setString("REGISTER");
    start_btn_text.setCharacterSize(22);
    start_btn_text.setFillColor(sf::Color::White);
    sf::FloatRect btn_b = start_btn_text.getLocalBounds();
    start_btn_text.setOrigin(btn_b.left + btn_b.width / 2.0f, btn_b.top + btn_b.height / 2.0f);
    start_btn_text.setPosition(center_x, center_y + 40.0f);
}

bool Start_screen::is_start_clicked(sf::Vector2i mouse_pos)
{
    sf::Vector2f m_pos(static_cast<float>(mouse_pos.x), static_cast<float>(mouse_pos.y));
    return start_btn.getGlobalBounds().contains(m_pos);
}

void Start_screen::render(sf::RenderWindow& window)
{
    if (start_background_texture.getNativeHandle() != 0)
    {
        window.draw(start_background_sprite);
    }

    window.draw(start_title_text);
    window.draw(start_subtitle_text);
    window.draw(start_btn);
    window.draw(start_btn_text);
}