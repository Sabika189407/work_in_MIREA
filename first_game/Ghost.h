#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <queue>
#include <map>

#include "Map.h"

enum class Ghost_type
{
    RANDOM,
    CHASER
};

enum class Ghost_state
{
    IN_HOUSE,
    ACTIVE,
    FRIGHTENED
};

class Ghost
{
private:
    float tile_size;
    float radius; 
    float base_speed;
    float m_speed;
    float tiles_per_second = 2.0f;

    float house_timer = 0.0f;

    sf::Sprite m_sprite;
    sf::Vector2f m_direction;
    Ghost_type m_type;
    sf::Color m_color;
    Ghost_state state;
    sf::Vector2f home_pos;

    void new_direction(const Map&, sf::Vector2f);
    void align_to_grid();
public:
    Ghost(const Map& map, Ghost_type type, sf::Color color, const sf::Texture& texture);

    void release_from_house();
    void set_frightened(bool);
    void reset();

    Ghost_state get_state() const;
    sf::FloatRect get_bounds() const;

    void update(float, const Map&, sf::Vector2f);
    void render(sf::RenderWindow&);
};