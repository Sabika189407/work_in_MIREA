#include "EndScreen.h"
#include <iomanip>
#include <sstream>

End_screen::End_screen(float window_w, float window_h)
    : win_w(window_w), win_h(window_h)
{
    victory_texture.loadFromFile("assets/win_background.png");
    game_over_texture.loadFromFile("assets/lose_background.png");

    end_font.loadFromFile("assets/minecraft.ttf");

    float center_x = window_w / 2.0f;
    float center_y = window_h / 2.0f;

    //main header
    end_title_text.setFont(end_font);
    end_title_text.setCharacterSize(40);
    end_title_text.setPosition(center_x, center_y - 120.0f);

    //score
    end_score_text.setFont(end_font);
    end_score_text.setCharacterSize(22);
    end_score_text.setFillColor(sf::Color::White);
    end_score_text.setPosition(center_x, center_y - 40.0f);

    //time
    end_time_text.setFont(end_font);
    end_time_text.setCharacterSize(22);
    end_time_text.setFillColor(sf::Color::White);
    end_time_text.setPosition(center_x, center_y);

    //restart button
    end_restart_btn.setSize(sf::Vector2f(260.0f, 50.0f));
    end_restart_btn.setFillColor(sf::Color(40, 160, 60));
    end_restart_btn.setOutlineThickness(2.0f);
    end_restart_btn.setOutlineColor(sf::Color::White);
    end_restart_btn.setOrigin(130.0f, 25.0f);
    end_restart_btn.setPosition(center_x, center_y + 80.0f);

    end_restart_btn_text.setFont(end_font);
    end_restart_btn_text.setString("PLAY AGAIN");
    end_restart_btn_text.setCharacterSize(20);
    end_restart_btn_text.setFillColor(sf::Color::White);
    sf::FloatRect btn_b = end_restart_btn_text.getLocalBounds();
    end_restart_btn_text.setOrigin(btn_b.left + btn_b.width / 2.0f, btn_b.top + btn_b.height / 2.0f);
    end_restart_btn_text.setPosition(center_x, center_y + 80.0f);
}

void End_screen::setup(bool is_victory, int score, float play_time)
{
    sf::Texture* current_tex = is_victory ? &victory_texture : &game_over_texture;

    if (current_tex->getNativeHandle() != 0)
    {
        background_sprite.setTexture(*current_tex, true); //true сбрасывает rect
        
        //scaling for fullscreen mode
        sf::Vector2u tex_size = current_tex->getSize();

        // Чёткое масштабирование по реальным размерам окна
        background_sprite.setScale(
            win_w / static_cast<float>(tex_size.x),
            win_h / static_cast<float>(tex_size.y)
        );
        has_background = true;
    }

    if (is_victory)
    {
        end_title_text.setString("You saved ur child!");
        end_title_text.setFillColor(sf::Color::Green);
    }
    else
    {
        end_title_text.setString("You lost ur child!");
        end_title_text.setFillColor(sf::Color::Red);
    }

    sf::FloatRect title_b = end_title_text.getLocalBounds();
    end_title_text.setOrigin(title_b.left + title_b.width / 2.0f, title_b.top + title_b.height / 2.0f);

    end_score_text.setString("Final Score: " + std::to_string(score));
    sf::FloatRect score_b = end_score_text.getLocalBounds();
    end_score_text.setOrigin(score_b.left + score_b.width / 2.0f, score_b.top + score_b.height / 2.0f);

    //formatting time *.*s
    std::stringstream ss;
    ss << std::fixed << std::setprecision(1) << play_time;
    end_time_text.setString("Play Time: " + ss.str() + "s");
    sf::FloatRect time_b = end_time_text.getLocalBounds();
    end_time_text.setOrigin(time_b.left + time_b.width / 2.0f, time_b.top + time_b.height / 2.0f);
}

bool End_screen::is_restart_clicked(sf::Vector2i mouse_pos)
{
    sf::Vector2f m_pos(static_cast<float>(mouse_pos.x), static_cast<float>(mouse_pos.y));
    return end_restart_btn.getGlobalBounds().contains(m_pos);
}

void End_screen::render(sf::RenderWindow& window)
{
    if (has_background)
    {
        window.draw(background_sprite);
    }
    window.draw(end_title_text);
    window.draw(end_score_text);
    window.draw(end_time_text);
    window.draw(end_restart_btn);
    window.draw(end_restart_btn_text);
}