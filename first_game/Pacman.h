#pragma once
#include <SFML/Graphics.hpp> 
#include "Map.h"
#include <cmath>
class PacMan
{
private:
    float tile_size = 40.0f;
    float radius = 15.0f;

    float base_speed;
    float m_speed; //cur speed
    float tiles_per_second = 4.0f; //pacman speed
    
    float potion_timer = 0.0f;
    bool is_strong = false;

    const sf::Texture* m_normal_texture = nullptr;
    const sf::Texture* m_strong_texture = nullptr;

    sf::Sprite m_sprite; //PacMan
    sf::Vector2f m_direction; //its vector of direction (1, 0) - right, (-1, 0) - left and etc
 
public:
    explicit PacMan(const Map& map, const sf::Texture& normal_tex, const sf::Texture& strong_tex);

    void activate_potion(float duration = 5.0f);
    bool is_ghost_hunter() const;

    sf::FloatRect getBounds() const { return m_sprite.getGlobalBounds(); } //get hitbox
    void go_middle(bool mid_x, bool mid_y);
    void handleInput();
    void update(float dt, const Map& map);
    void render(sf::RenderWindow&);
};