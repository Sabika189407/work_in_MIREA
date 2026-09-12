#include "Ghost.h"

struct Point
{
    int r, c;
    bool operator<(const Point& other) const
    {
        if (r != other.r)
        {
            return r < other.r;
        }
        return c < other.c;
    }
    bool operator==(const Point& other) const
    {
        return r == other.r && c == other.c;
    }
};

Ghost::Ghost(const Map& map, Ghost_type type, sf::Color color, const sf::Texture& texture)
    : m_type(type), m_color(color),
      tile_size(map.get_tile_size()),
      radius(tile_size * 0.35f), //was 0.35f
      state(Ghost_state::IN_HOUSE),
      m_direction(0.0f, -1.0f)
{
    base_speed = tile_size * tiles_per_second;
    m_speed = base_speed;

    m_sprite.setTexture(texture);
    m_sprite.setColor(color); 

    sf::Vector2u tex_size = texture.getSize();
    m_sprite.setScale((radius * 2.0f) / static_cast<float>(tex_size.x), 
                      (radius * 2.0f) / static_cast<float>(tex_size.y));

    float center_x = ((map.get_cols() / 2) * tile_size);
    float center_y = ((map.get_rows() / 2) * tile_size);
    home_pos = sf::Vector2f(center_x + (tile_size - radius * 2.0f) / 2.0f, 
                            center_y + (tile_size - radius * 2.0f) / 2.0f);

    m_sprite.setPosition(home_pos);
}

void Ghost::align_to_grid()
{
    sf::Vector2f pos  = m_sprite.getPosition();
    if (m_direction.y != 0.0f)
    {
        float target_x = std::floor((pos.x + radius) / tile_size) * tile_size + (tile_size - radius * 2.0f) / 2.0f; m_sprite.setPosition(target_x, pos.y);
    }
    else if (m_direction.x != 0.0f)
    {
        float target_y = std::floor((pos.y + radius) / tile_size) * tile_size + (tile_size - radius * 2.0f) / 2.0f; m_sprite.setPosition(pos.x, target_y);
    }
}

void Ghost::release_from_house()
{
    if (state == Ghost_state::IN_HOUSE)
    {
        state = Ghost_state::ACTIVE;
    }
}

void Ghost::set_frightened(bool frightened)
{
    if (state == Ghost_state::IN_HOUSE)
    {
        return;
    }
    if (frightened)
    {
        state = Ghost_state::FRIGHTENED;
        m_sprite.setColor(sf::Color::Blue);
        m_speed = base_speed * 0.8f;
    }
    else
    {
        state = Ghost_state::ACTIVE;
        m_speed = base_speed;
        m_sprite.setColor(m_color);
    }
}

void Ghost::reset()
{
    state = Ghost_state::IN_HOUSE;
    m_sprite.setPosition(home_pos); //go home Wholter
    m_direction = sf::Vector2f(0.0f, -1.0f);
    m_sprite.setColor(m_color);
    house_timer = 3.0f;
}

Ghost_state Ghost::get_state() const
{
    return state;
}

sf::FloatRect Ghost::get_bounds() const
{
    return m_sprite.getGlobalBounds();
}

void Ghost::update(float dt, const Map& map, sf::Vector2f player_pos)
{
    if (state == Ghost_state::IN_HOUSE)
    {
        if (house_timer > 0.0f)
        {
            house_timer -= dt;
            if (house_timer <= 0.0f)
            {
                house_timer = 0.0f;
                release_from_house();
            }
        }
        return;
    }

    sf::Vector2f cur_pos = m_sprite.getPosition();
    int old_r = static_cast<int>((cur_pos.y + radius) / tile_size);
    int old_c = static_cast<int>((cur_pos.x + radius) / tile_size);

    sf::Vector2f movement = m_direction * m_speed * dt;

    //go in x

    m_sprite.move(movement.x, 0.0f);
    if (map.check_collision(m_sprite.getGlobalBounds()))
    {
        m_sprite.move(-movement.x, 0.0f); //bounce if hit a wall
        new_direction(map, player_pos);
        return;
    }

    //go in y
    m_sprite.move(0.0f, movement.y);
    if (map.check_collision(m_sprite.getGlobalBounds()))
    {
        m_sprite.move(0.0f, -movement.y); //bounce if hit a wall
        new_direction(map, player_pos);
        return;
    }
    
    //perekrestok

    sf::Vector2f new_pos = m_sprite.getPosition();
    int new_r = static_cast<int>((new_pos.y + radius) / tile_size);
    int new_c = static_cast<int>((new_pos.x + radius) / tile_size);
    
    if (new_r != old_r || new_c != old_c)
    {
        new_direction(map, player_pos);
    }
}

void Ghost::render(sf::RenderWindow& window)
{
    window.draw(m_sprite);
}

void Ghost::new_direction(const Map& map, sf::Vector2f target_pos)
{
    std::vector<sf::Vector2f> valid_dirs;
    sf::Vector2f dirs[4] = {{0, -1}, {0, 1}, {-1, 0}, {1, 0}};

    sf::Vector2f cur_pos = m_sprite.getPosition();
    int cur_r = static_cast<int>((cur_pos.y + radius) / tile_size);
    int cur_c = static_cast<int>((cur_pos.x + radius) / tile_size);
    
    //looking for next tiles
    for (const auto& d : dirs)
    {
        if (d == -m_direction) //not returning at 180 deg with no reason
        {
            continue;
        }
        if (!map.is_wall(cur_r + d.y, cur_c + d.x))
        {
            valid_dirs.push_back(d);
        }
    }
    if (valid_dirs.empty())
    {
        m_direction = -m_direction; //if there is no road turn back
        return;
    }

    if (m_type == Ghost_type::RANDOM || state == Ghost_state::FRIGHTENED)
    {
        m_direction = valid_dirs[std::rand() % valid_dirs.size()];
        return;
    }
    //BFS algorithm
    int target_r = static_cast<int>((target_pos.y + radius) / tile_size);
    int target_c = static_cast<int>((target_pos.x + radius) / tile_size);

    Point start = {cur_r, cur_c};
    Point target = {target_r, target_c};
    if(start == target)
    {
        return;
    }
    std::queue<Point> q;
    std::map<Point, Point> parent; //to return in beginning
    std::map<Point, bool> visited;
    q.push(start);
    visited[start] = true;
    bool found = false;
    while (!q.empty())
    {
        Point current = q.front();
        q.pop();
        if (current == target)
        {
            found = true;
            break;
        }
        for (const auto& d : dirs)
        {
            Point next = {current.r + static_cast<int>(d.y), current.c + static_cast<int>(d.x)};

            if (!map.is_wall(next.r, next.c) && !visited[next])
            {
                visited[next] = true;
                parent[next] = current;
                q.push(next);
            }
        }
    }

    //if found go back to first step to ghost
    if (found)
    {
        Point curr = target;
        while (!(parent[curr] == start))
        {
            curr = parent[curr];
        }

        //vector for the first step
        m_direction = sf::Vector2f(static_cast<float>(curr.c - start.c), 
                                   static_cast<float>(curr.r - start.r));
    }
    else
    {
        //if way is in walls go random dir
        m_direction = valid_dirs[std::rand() % valid_dirs.size()];
    }
    align_to_grid();
}