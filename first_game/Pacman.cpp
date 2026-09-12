#include "Pacman.h"


PacMan::PacMan(const Map& map, const sf::Texture& normal_tex, const sf::Texture& strong_tex)
    : tile_size(map.get_tile_size()), 
      radius(tile_size * 0.455f), 
      m_direction(0.0f, 0.0f),
      m_normal_texture(&normal_tex),
      m_strong_texture(&strong_tex) //rad was 0.35
{
    base_speed = tile_size * tiles_per_second;
    m_speed = base_speed;

    m_sprite.setTexture(*m_normal_texture);

    sf::Vector2u tex_size = m_normal_texture->getSize();
    m_sprite.setScale((radius * 2.0f) / static_cast<float>(tex_size.x), (radius * 2.0f) / static_cast<float>(tex_size.y));

    float center_x = ((map.get_cols() / 2) * tile_size);
    float center_y = (((map.get_rows() / 2) - 3) * tile_size);
    
    m_sprite.setPosition(center_x + (tile_size - radius * 2.0f) / 2.0f, center_y + (tile_size - radius * 2.0f) / 2.0f);
}

void PacMan::activate_potion(float duration)
{
   potion_timer = duration;
   is_strong = true;
   m_speed = base_speed * 1.5f;
   
   //turn into strong tex
   if (m_strong_texture)
   {
       m_sprite.setTexture(*m_strong_texture);
   }
}

bool PacMan::is_ghost_hunter() const
{
    return is_strong;
}

void PacMan::go_middle(bool mid_x, bool mid_y)
{
    sf::Vector2f pos = m_sprite.getPosition();

    if(mid_x)
    {
        float target_X = std::floor((pos.x + radius) / tile_size) * tile_size + (tile_size - radius*2.0f) / 2.0f;
        if (std::abs(pos.x - target_X) < tile_size * 0.4f)
        {
            m_sprite.setPosition(target_X, pos.y);
        }
    }
    if(mid_y)
    {
        float target_Y = std::floor((pos.y + radius) / tile_size) * tile_size + (tile_size - radius*2.0f) / 2.0f;
        if(std::abs(pos.y - target_Y) < tile_size * 0.4f)
        {
            m_sprite.setPosition(pos.x, target_Y);
        }
    }
}


void PacMan::handleInput()
{
    // up: X = 0, Y = -1
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        go_middle(true, false);
        m_direction = sf::Vector2f(0.0f, -1.0f);
    }
    // down: X = 0, Y = 1
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        go_middle(true, false);
        m_direction = sf::Vector2f(0.0f, 1.0f);
    }
    // left: X = -1, Y = 0
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        go_middle(false, true);
        m_direction = sf::Vector2f(-1.0f, 0.0f);
    }
    // rightm: X = 1, Y = 0
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        go_middle(false, true);
        m_direction = sf::Vector2f(1.0f, 0.0f);
    }
}

void PacMan::update(float dt, const Map& map)
{
    if (potion_timer > 0.0f)
    {
        potion_timer -= dt;
        if (potion_timer <= 0.0f)
        {
            potion_timer = 0.0f;
            is_strong = false;
            m_speed = base_speed;
            if (m_normal_texture)
            {
                m_sprite.setTexture(*m_normal_texture);
            }
        }
    }
    sf::Vector2f movement = m_direction * m_speed * dt; //if ur have a powerfull pc and 240 fps ur pacman will have higher speed than a computer with 60 fps
    
    //______________x_______________
    m_sprite.move(movement.x, 0.0f);
    if(map.check_collision(m_sprite.getGlobalBounds()))
    {
        m_sprite.move(-movement.x, 0.0f);
    }

    //_____________y_______________
    m_sprite.move(0.0f, movement.y);
    if(map.check_collision(m_sprite.getGlobalBounds()))
    {
        m_sprite.move(0.0f, -movement.y);
    }
}

void PacMan::render(sf::RenderWindow& window)
{
    window.draw(m_sprite);
}